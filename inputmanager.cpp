#include "inputmanager.h"
#include "algorithm"

#include <OGRE/OgreRenderWindow.h>
#include <OIS/OIS.h>

CInputManager *CInputManager::instance = nullptr;

CInputManager *CInputManager::getInstance()
{
    if (!instance) {
        instance = new CInputManager;
        static __CSingletonImplDel<CInputManager> delHelper(instance);
    }
    return instance;
}

CInputManager::CInputManager() : OIS::KeyListener(), OIS::MouseListener(),
    m_inputMgr(nullptr), m_keyboard(nullptr), m_mouse(nullptr), m_listeners()
{
}

CInputManager::~CInputManager()
{
    if (m_inputMgr) {
        if (m_keyboard)
            m_inputMgr->destroyInputObject(m_keyboard);
        if (m_mouse)
            m_inputMgr->destroyInputObject(m_mouse);
        OIS::InputManager::destroyInputSystem(m_inputMgr);
    }
}

bool CInputManager::configure(Ogre::RenderWindow *renderWindow)
{
    size_t wHandler = 0;
    renderWindow->getCustomAttribute("WINDOW", &wHandler);
    OIS::ParamList pl;
    pl.insert(std::make_pair<std::string, std::string>("WINDOW", std::to_string(wHandler)));
#if defined OIS_WIN32_PLATFORM
    pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
    pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
    pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
    pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
    pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif
    m_inputMgr = OIS::InputManager::createInputSystem(pl);

    if (!m_inputMgr->getNumberOfDevices(OIS::OISKeyboard) ||
            !m_inputMgr->getNumberOfDevices(OIS::OISKeyboard))
        return false;
    m_keyboard = static_cast<OIS::Keyboard*>(m_inputMgr->createInputObject(OIS::OISKeyboard, true));
    m_keyboard->setEventCallback(this);
    m_mouse = static_cast<OIS::Mouse*>(m_inputMgr->createInputObject(OIS::OISMouse, true));
    m_mouse->setEventCallback(this);

    unsigned int width, height, depth;
    int top, left;
    renderWindow->getMetrics(width, height, depth, left, top);
    const OIS::MouseState &ms = m_mouse->getMouseState();
    ms.width = width;
    ms.height = height;

    return true;
}

void CInputManager::addListener(CAbstactEventListener *listener)
{
    m_listeners.push_back(listener);
}

void CInputManager::removeListener(CAbstactEventListener *listener)
{
    m_listeners.erase(std::remove(m_listeners.begin(), m_listeners.end(), listener), m_listeners.end());
}

void CInputManager::capture()
{
    m_mouse->capture();
    m_keyboard->capture();
}

bool CInputManager::keyPressed(const OIS::KeyEvent &arg)
{
    for (CAbstactEventListener *listener : m_listeners) {
        if (!listener->onKeyPressed(arg))
            return false;
    }
    return true;
}

bool CInputManager::keyReleased(const OIS::KeyEvent &arg)
{
    for (CAbstactEventListener *listener : m_listeners) {
        if (!listener->onKeyReleased(arg))
            return false;
    }
    return true;
}

bool CInputManager::mouseMoved(const OIS::MouseEvent &arg)
{
    for (CAbstactEventListener *listener : m_listeners)
        listener->onMouseMoved(arg);
    return true;
}

bool CInputManager::mousePressed(const OIS::MouseEvent &/*arg*/, OIS::MouseButtonID /*id*/)
{
    return true;
}

bool CInputManager::mouseReleased(const OIS::MouseEvent &/*arg*/, OIS::MouseButtonID /*id*/)
{
    return true;
}
