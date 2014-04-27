#include "framelistener.h"
#include "inputmanager.h"
#include "camera.h"
#include "renderableobject.h"
#include "physicalobject.h"
#include "physicsmanager.h"
#include "rigidbodyfactory.h"
#include "ogredebugdrawer.h"
#include "shipsfactory.h"

#include <OGRE/Ogre.h>
#include <string>

using namespace Ogre;

CFrameListener::CFrameListener(Ogre::RenderWindow *renderWindow, Ogre::SceneManager *sceneMgr)
    : Ogre::FrameListener(), CAbstactEventListener(),
      m_renderWindow(renderWindow), m_sceneMgr(sceneMgr), m_viewport(nullptr),
      m_inputMgr(nullptr), m_camera(nullptr), m_plane(nullptr), m_ship(nullptr),
      m_exit(false)
{
}

CFrameListener::~CFrameListener()
{
    m_sceneMgr->destroyAllLights();
    delete m_viewport;
    delete m_camera;
    delete m_plane;
}

bool CFrameListener::configure()
{
    LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    m_inputMgr = CInputManager::getInstance();
    m_inputMgr->addListener(this);
    if (!m_inputMgr->configure(m_renderWindow))
        return false;

    LogManager::getSingletonPtr()->logMessage("*** Initializing objects and physics ***");
    m_plane = new CRenderableObject(m_sceneMgr, CRenderableObject::PT_PLANE, "PlaneNode");
    m_ship = CShipsFactory::getInstance()->getBoat(m_sceneMgr);

    CPhysicsManager::getInstance()->setDebugDrawer(new OgreDebugDrawer(m_sceneMgr));

    LogManager::getSingletonPtr()->logMessage("*** Initializing camera ***");
    m_camera = new CCamera(m_sceneMgr, m_ship->getRenderableObject()->getSceneNode());
    m_viewport = m_renderWindow->addViewport(m_camera->getOgreCamera());
    m_viewport->setBackgroundColour(Ogre::ColourValue(1.0f,0.0f,0.0f));
    if (m_viewport->getActualHeight())
        m_camera->getOgreCamera()->setAspectRatio(Ogre::Real(m_viewport->getActualWidth()) / Ogre::Real(m_viewport->getActualHeight()));
    else
        m_camera->getOgreCamera()->setAspectRatio(Ogre::Real(m_viewport->getActualWidth()));

    LogManager::getSingletonPtr()->logMessage("*** Initializing lights and shadows ***");
    m_sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    m_sceneMgr->setShadowTextureSelfShadow(true);
    m_sceneMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
    Ogre::Light* light = m_sceneMgr->createLight("Light");
    light->setPosition(Ogre::Vector3(-200.0f, 500.0f, -300.0f));
    light->setType(Ogre::Light::LT_POINT);
    light->setDiffuseColour(Ogre::ColourValue::White);

    return true;
}

bool CFrameListener::frameStarted(const Ogre::FrameEvent &evt)
{
    m_inputMgr->capture();
    CPhysicsManager::getInstance()->update(evt);
    m_ship->update();
    CPhysicsManager::getInstance()->debugDraw();
    return !m_exit && frameRenderingQueued(evt);
}

bool CFrameListener::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
    return true;
}

bool CFrameListener::frameEnded(const Ogre::FrameEvent &evt)
{
    if (m_renderWindow->isClosed())
        m_exit = true;
    return !m_exit;
}

void CFrameListener::onMouseMoved(const OIS::MouseEvent &/*e*/)
{
}

void CFrameListener::prepareShipChange(OIS::KeyCode code)
{
    delete m_ship;
    delete m_camera;
    switch (code) {
    case OIS::KC_1:
        m_ship = CShipsFactory::getInstance()->getBoat(m_sceneMgr);
        m_camera = new CCamera(m_sceneMgr, m_ship->getRenderableObject()->getSceneNode(), 100.0f);
        break;
    case OIS::KC_2:
        m_ship = CShipsFactory::getInstance()->getAverageShip(m_sceneMgr);
        m_camera = new CCamera(m_sceneMgr, m_ship->getRenderableObject()->getSceneNode(), 500.0f);
        break;
    case OIS::KC_3:
        m_ship = CShipsFactory::getInstance()->getBattleship(m_sceneMgr);
        m_camera = new CCamera(m_sceneMgr, m_ship->getRenderableObject()->getSceneNode(), 700.0f);
        break;
    default:
        break;
    }

    m_viewport->setCamera(m_camera->getOgreCamera());
    if (m_viewport->getActualHeight())
        m_camera->getOgreCamera()->setAspectRatio(Ogre::Real(m_viewport->getActualWidth()) / Ogre::Real(m_viewport->getActualHeight()));
    else
        m_camera->getOgreCamera()->setAspectRatio(Ogre::Real(m_viewport->getActualWidth()));
}

bool CFrameListener::onKeyPressed(const OIS::KeyEvent &e)
{
    if (e.key == OIS::KC_ESCAPE) {
        m_exit = true;
    } else {
        switch (e.key) {
        case OIS::KC_1:
        case OIS::KC_2:
        case OIS::KC_3:
            prepareShipChange(e.key);
            break;
        default:
            break;
        }
    }
    return !m_exit;
}

bool CFrameListener::onKeyReleased(const OIS::KeyEvent &/*e*/)
{
    return true;
}
