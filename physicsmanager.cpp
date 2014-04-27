#include "physicsmanager.h"
#include "rigidbodyfactory.h"

#include <bullet/btBulletDynamicsCommon.h>

#include <OGRE/OgreFrameListener.h>

CPhysicsManager *CPhysicsManager::instance = nullptr;

CPhysicsManager *CPhysicsManager::getInstance()
{
    if (!instance) {
        instance = new CPhysicsManager;
        static __CSingletonImplDel<CPhysicsManager> implDel(instance);
    }
    return instance;
}

CPhysicsManager::CPhysicsManager()
    : m_collisionConfig(new btDefaultCollisionConfiguration),
      m_dispatcher(new btCollisionDispatcher(m_collisionConfig)),
      m_broadphase(new btDbvtBroadphase),
      m_solver(new btSequentialImpulseConstraintSolver),
      m_world(new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfig)),
      m_debug(nullptr),
      m_plane(nullptr), m_ship(nullptr)
{
    m_world->setGravity(btVector3(0, -10, 0));
    m_plane = CRigidBodyFactory::getInstance()->getPlane();
    m_world->addRigidBody(m_plane);
}

CPhysicsManager::~CPhysicsManager()
{
    removeRigidBody(m_plane);
    removeRigidBody(m_ship);
    delete m_dispatcher;
    delete m_collisionConfig;
    delete m_solver;
    delete m_broadphase;
    delete m_debug;
    //    delete m_world; <-- segfault. Почему? Oo
}

void CPhysicsManager::removeRigidBody(btRigidBody *body)
{
    m_world->removeCollisionObject(body);
    btMotionState* motionState = body->getMotionState();
    btCollisionShape* shape = body->getCollisionShape();
    delete body;
    delete shape;
    delete motionState;
}

void CPhysicsManager::addRigidBody(btRigidBody *rigidBody)
{
    if (m_ship)
        removeRigidBody(m_ship);
    m_ship = rigidBody;
    m_world->addRigidBody(rigidBody);
}

void CPhysicsManager::setDebugDrawer(btIDebugDraw *debugDrawer)
{
    m_world->setDebugDrawer(debugDrawer);
}

void CPhysicsManager::debugDraw() const
{
    m_world->debugDrawWorld();
}

void CPhysicsManager::update(const Ogre::FrameEvent &e)
{
    m_world->stepSimulation(e.timeSinceLastFrame, 7);
}
