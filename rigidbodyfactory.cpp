#include "rigidbodyfactory.h"

#include <bullet/btBulletDynamicsCommon.h>
#include <OGRE/OgreSceneNode.h>

CRigidBodyFactory *CRigidBodyFactory::instance = nullptr;

CRigidBodyFactory *CRigidBodyFactory::getInstance()
{
    if (!instance) {
        instance = new CRigidBodyFactory;
        static __CSingletonImplDel<CRigidBodyFactory> delHelper(instance);
    }
    return instance;
}

CRigidBodyFactory::CRigidBodyFactory()
{
}

btRigidBody *CRigidBodyFactory::getPlane() const
{
    btStaticPlaneShape *planeShape = new btStaticPlaneShape(btVector3(0.0, 1.0, 0.0), 0.0);
    btRigidBody *rigidBody = new btRigidBody(0.0, new btDefaultMotionState, planeShape);
    rigidBody->setFriction(0); // без трения
    return rigidBody;
}

btRigidBody *CRigidBodyFactory::getCube(Ogre::SceneNode *sceneNode, float mass) const
{
    const Ogre::AxisAlignedBox &aabb = sceneNode->_getWorldAABB();
    Ogre::Vector3 halfSize = aabb.getMaximum() * 10;

    btBoxShape *boxShape = new btBoxShape(btVector3(halfSize.x, halfSize.y, halfSize.z));
    btVector3 inertia(0,0,0);
    if(mass > 0.0f)
        boxShape->calculateLocalInertia(mass, inertia);

    const Ogre::Vector3 &pos = sceneNode->getPosition();
    const Ogre::Quaternion &rot = sceneNode->getOrientation();
    btTransform t;
    t.setOrigin(btVector3(pos.x, pos.y, pos.z));
    t.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));
    btMotionState* motion = new btDefaultMotionState(t);

    btRigidBody *rigidBody = new btRigidBody(mass, motion, boxShape, inertia);
    rigidBody->setFriction(0); // без трения
    rigidBody->setDamping(0, 0.2); // без затухания линейной скорости, с затуханием угловой скорости.
    // т.к можно проигнорировать силу Архимеда, а вода гладкая,
    // будем считать, что лодка скользит по идеально гладкой поверхности(без трения),
    // не уходя под воду (т.е. считаем, что вода - это обычное твердое тело)
    return rigidBody;
}

CRigidBodyFactory::~CRigidBodyFactory()
{
}
