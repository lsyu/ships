#ifndef APPLICATION_H
#define APPLICATION_H

#include "singletonimpldel.h"

namespace Ogre {
class Root;
class RenderWindow;
class SceneManager;
class FrameListener;
} // namespace Ogre

class CApplication
{
public:

    friend class __CSingletonImplDel<CApplication>;
    static CApplication *getInstance();
    CApplication(const CApplication &) = delete;
    CApplication &operator =(const CApplication &) = delete;

    bool configure();
    void exec();

protected:
    // ctor
    CApplication();
    // dtor
    ~CApplication();
private:
    static CApplication *instance;

    Ogre::Root *m_root;
    Ogre::RenderWindow *m_renderWindow;
    Ogre::SceneManager *m_sceneMgr;
    Ogre::FrameListener *m_eventListener;
}; // class CApplication

#endif // APPLICATION_H
