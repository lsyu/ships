#ifndef RIGIDBODYFACTORY_H
#define RIGIDBODYFACTORY_H

#include "singletonimpldel.h"
#include <bullet/BulletDynamics/Dynamics/btRigidBody.h>

namespace Ogre {
class SceneNode;
}

class CRigidBodyFactory
{
public:

    friend class __CSingletonImplDel<CRigidBodyFactory>;
    static CRigidBodyFactory *getInstance();
    CRigidBodyFactory(const CRigidBodyFactory &) = delete;
    CRigidBodyFactory &operator =(const CRigidBodyFactory&) = delete;

    btRigidBody *getPlane() const;
    btRigidBody *getCube(Ogre::SceneNode *sceneNode, float mass) const;

protected:
    CRigidBodyFactory();
    ~CRigidBodyFactory();

private:
    static CRigidBodyFactory *instance;
}; // class CRigidBodyFactory

#endif // RIGIDBODYFACTORY_H
