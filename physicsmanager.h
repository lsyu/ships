#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "singletonimpldel.h"

#include <vector>

namespace Ogre {
class FrameEvent;
} // namespace Ogre
class btDynamicsWorld;
class btDispatcher;
class btCollisionConfiguration;
class btBroadphaseInterface;
class btConstraintSolver;
class btRigidBody;
class btIDebugDraw;

class CPhysicsManager
{
public:
    friend class __CSingletonImplDel<CPhysicsManager>;
    static CPhysicsManager *getInstance();
    CPhysicsManager(const CPhysicsManager &) = delete;
    CPhysicsManager &operator =(const CPhysicsManager &) = delete;

    void addRigidBody(btRigidBody *rigidBody);
    void setDebugDrawer(btIDebugDraw *debugDrawer);
    void debugDraw() const;
    void update(const Ogre::FrameEvent &e);
protected:
    CPhysicsManager();
    ~CPhysicsManager();

    void removeRigidBody(btRigidBody *body);
private:
    static CPhysicsManager *instance;

    btCollisionConfiguration *m_collisionConfig;
    btDispatcher *m_dispatcher;
    btBroadphaseInterface *m_broadphase;
    btConstraintSolver *m_solver;
    btDynamicsWorld *m_world;
    btIDebugDraw *m_debug;

    btRigidBody *m_plane;
    btRigidBody *m_ship;
}; // class CPhysicsManager

#endif // PHYSICSMANAGER_H
