#ifndef ABSTRACTEVENTLISTENER_H
#define ABSTRACTEVENTLISTENER_H

namespace OIS {
class MouseEvent;
class KeyEvent;
} // namespace OIS

class CAbstactEventListener
{
public:
    virtual void onMouseMoved(const OIS::MouseEvent &e) = 0;
    virtual bool onKeyPressed(const OIS::KeyEvent &e) = 0;
    virtual bool onKeyReleased(const OIS::KeyEvent &e) = 0;
}; // class CAbstactEventListener

#endif // ABSTRACTEVENTLISTENER_H
