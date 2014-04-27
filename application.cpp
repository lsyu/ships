#include "application.h"

#include <OGRE/Ogre.h>
#include <OIS/OIS.h>

#include "framelistener.h"

CApplication *CApplication::instance = nullptr;

CApplication *CApplication::getInstance() {
    if (!instance) {
        instance = new CApplication;
        static __CSingletonImplDel<CApplication> implDel(instance);
    }
    return instance;
}

bool CApplication::configure()
{
    m_root = new Ogre::Root;
    if(!m_root->restoreConfig() && !m_root->showConfigDialog())
        return false;
    m_renderWindow = m_root->initialise(true, "WINDOW");
    m_sceneMgr = m_root->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
    Ogre::ConfigFile cf;
    cf.load("resources.cfg");
    Ogre::ConfigFile::SectionIterator it = cf.getSectionIterator();
    while(it.hasMoreElements()) {
        Ogre::String secName = it.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap* settings = it.getNext();
        for (Ogre::ConfigFile::SettingsMultiMap::iterator i = settings->begin(); i != settings->end(); ++i) {
            Ogre::String typeName = i->first;
            Ogre::String archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
        }
    }
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    CFrameListener *tmp = new CFrameListener(m_renderWindow, m_sceneMgr);
    m_eventListener = tmp;
    if (!tmp->configure())
        return false;
    m_root->addFrameListener(m_eventListener);
    return true;
}

void CApplication::exec()
{
    m_root->startRendering();
}

CApplication::CApplication()
    : m_root(nullptr), m_renderWindow(nullptr), m_sceneMgr(nullptr), m_eventListener(nullptr)
{
}

CApplication::~CApplication()
{
    delete m_eventListener;
    m_root->shutdown();
}
