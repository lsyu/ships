#ifndef PHYSICALOBJECT_H
#define PHYSICALOBJECT_H

#include "abstracteventlistener.h"

class CRenderableObject;
class btRigidBody;

class CPhysicalObject : CAbstactEventListener
{
    friend class CShipsFactory;
public:
    CPhysicalObject(CRenderableObject *renderableObject, btRigidBody *rigidBody);
    virtual ~CPhysicalObject();

    virtual void update();

    CRenderableObject *getRenderableObject() const;

    // CAbstactEventListener interface
public:
    virtual void onMouseMoved(const OIS::MouseEvent &e) override;
    virtual bool onKeyPressed(const OIS::KeyEvent &e) override;
    virtual bool onKeyReleased(const OIS::KeyEvent &e) override;
protected:
    void updateLinearVelocity();
private:
    CRenderableObject *m_renderable;
    btRigidBody *m_rigidBody;
    float m_motor;
}; // class CPhysicalObject

#endif // PHYSICALOBJECT_H
