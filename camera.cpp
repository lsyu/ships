#include "camera.h"
#include "inputmanager.h"

#include <OGRE/Ogre.h>
#include <OIS/OIS.h>

CCamera::CCamera(Ogre::SceneManager *sceneMgr, Ogre::SceneNode *parent, float distance)
    : m_camera(sceneMgr->createCamera("Camera")),
      m_cameraNode(
          parent
          ? parent->createChildSceneNode("Cameranode")
          : sceneMgr->getRootSceneNode()->createChildSceneNode("CameraNode")),
      m_sceneMgr(sceneMgr),
      minCos(-0.95f), maxCos(-0.2f)
{
    CInputManager::getInstance()->addListener(this);

    m_camera->setNearClipDistance(0.01f);
    m_camera->setFarClipDistance(500.0f);

    m_camera->setPosition(Ogre::Vector3(distance, 0.0, 0.0));
    m_camera->lookAt(Ogre::Vector3(0.0, 0.0, 0.0));
    m_camera->setFixedYawAxis(true);

    m_cameraNode->attachObject(m_camera);
    m_cameraNode->rotate(Ogre::Vector3::UNIT_Z, Ogre::Radian(Ogre::Degree(45.0)));

}

CCamera::~CCamera()
{
    CInputManager::getInstance()->removeListener(this);
    m_sceneMgr->destroySceneNode(m_cameraNode);
    m_sceneMgr->destroyCamera(m_camera);
}

Ogre::Camera *CCamera::getOgreCamera() const
{
    return m_camera;
}

void CCamera::onMouseMoved(const OIS::MouseEvent &e)
{
    m_cameraNode->rotate(Ogre::Vector3::NEGATIVE_UNIT_Y, Ogre::Radian(Ogre::Degree(e.state.X.rel)), Ogre::Node::TS_WORLD);

    float dotProduct = m_cameraNode->getLocalAxes().GetColumn(1).dotProduct(Ogre::Vector3::NEGATIVE_UNIT_Y);
    if (
            (dotProduct < maxCos && dotProduct > minCos) ||
            (dotProduct < maxCos && e.state.Y.rel > 0)   ||
            (dotProduct > minCos && e.state.Y.rel < 0)
    ) m_cameraNode->rotate(Ogre::Vector3::UNIT_Z, Ogre::Radian(Ogre::Degree(e.state.Y.rel)));
}

bool CCamera::onKeyPressed(const OIS::KeyEvent &e)
{
    return true;
}

bool CCamera::onKeyReleased(const OIS::KeyEvent &e)
{
    return true;
}
