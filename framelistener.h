#ifndef FRAMELISTENER_H
#define FRAMELISTENER_H

#include <OGRE/OgreFrameListener.h>
#include <OIS/OISKeyboard.h>
#include "abstracteventlistener.h"

namespace Ogre {
class RenderWindow;
class SceneManager;
class Viewport;
} // namespace Ogre

class CInputManager;
class CCamera;
class CRenderableObject;
class CPhysicalObject;

class CFrameListener : public Ogre::FrameListener, public CAbstactEventListener
{
public:
    CFrameListener(Ogre::RenderWindow *renderWindow, Ogre::SceneManager *sceneMgr);
    virtual ~CFrameListener();

    bool configure();

    // FrameListener interface
public:
    virtual bool frameStarted(const Ogre::FrameEvent &evt) override;
    virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt) override;
    virtual bool frameEnded(const Ogre::FrameEvent &evt) override;

    // CAbstactEventListener interface
public:
    virtual void onMouseMoved(const OIS::MouseEvent &e) override;
    virtual bool onKeyPressed(const OIS::KeyEvent &e) override;
    virtual bool onKeyReleased(const OIS::KeyEvent &e) override;

protected:
    void prepareShipChange(OIS::KeyCode code);

private:
    Ogre::RenderWindow *m_renderWindow;
    Ogre::SceneManager *m_sceneMgr;
    Ogre::Viewport *m_viewport;
    CInputManager *m_inputMgr;
    CCamera *m_camera;
    CRenderableObject *m_plane;
    CPhysicalObject *m_ship;
    bool m_exit;
}; // class CEventListener

#endif // FRAMELISTENER_H
