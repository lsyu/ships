#ifndef CAMERA_H
#define CAMERA_H

#include "abstracteventlistener.h"

namespace Ogre {
class RenderWindow;
class SceneManager;
class Viewport;
class SceneNode;
class Camera;
} // namespace Ogre

class CCamera : public CAbstactEventListener
{
public:
    CCamera(Ogre::SceneManager *sceneMgr, Ogre::SceneNode *parent = nullptr, float distance = 100.0f);
    virtual ~CCamera();

    Ogre::Camera *getOgreCamera() const;

    // CAbstactEventListener interface
public:
    virtual void onMouseMoved(const OIS::MouseEvent &e) override;
    virtual bool onKeyPressed(const OIS::KeyEvent &e) override;
    virtual bool onKeyReleased(const OIS::KeyEvent &e) override;

private:
    Ogre::Camera *m_camera;
    Ogre::SceneNode *m_cameraNode;
    Ogre::SceneManager *m_sceneMgr;
    float minCos;
    float maxCos;
}; // class CCamera

#endif // CAMERA_H
