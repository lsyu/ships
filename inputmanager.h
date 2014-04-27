#ifndef CINPUTMANAGER_H
#define CINPUTMANAGER_H

#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

#include <vector>

#include "abstracteventlistener.h"
#include "singletonimpldel.h"

namespace Ogre {
class RenderWindow;
} // namespace Ogre

class CInputManager : public OIS::KeyListener, public OIS::MouseListener
{
public:
    friend class __CSingletonImplDel<CInputManager>;
    static CInputManager *getInstance();
    CInputManager(const CInputManager &) = delete;
    CInputManager &operator =(const CInputManager &) = delete;

    bool configure(Ogre::RenderWindow *renderWindow);
    void addListener(CAbstactEventListener *listener);
    void removeListener(CAbstactEventListener *listener);
    void capture();

    // KeyListener interface
public:
    virtual bool keyPressed(const OIS::KeyEvent &arg) override;
    virtual bool keyReleased(const OIS::KeyEvent &arg) override;

    // MouseListener interface
public:
    virtual bool mouseMoved(const OIS::MouseEvent &arg) override;
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) override;
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) override;

protected:
    CInputManager();
    virtual ~CInputManager();

private:
    static CInputManager *instance;
    OIS::InputManager *m_inputMgr;
    OIS::Keyboard *m_keyboard;
    OIS::Mouse *m_mouse;
    std::vector<CAbstactEventListener*> m_listeners;
}; // class CSceneManager

#endif // CINPUTMANAGER_H
