#include "shipsfactory.h"

#include "renderableobject.h"
#include "rigidbodyfactory.h"
#include "physicsmanager.h"

#include <OGRE/Ogre.h>

CShipsFactory *CShipsFactory::instance = nullptr;

CShipsFactory *CShipsFactory::getInstance()
{
    if (!instance) {
        instance = new CShipsFactory;
        static __CSingletonImplDel<CShipsFactory> delHelper(instance);
    }
    return instance;
}

CShipsFactory::CShipsFactory()
{
}

CPhysicalObject *CShipsFactory::getBoat(Ogre::SceneManager *sceneMgr) const
{
    CRenderableObject *cube = new CRenderableObject(sceneMgr, CRenderableObject::PT_CUBE, "CubeNode");
    cube->setScale(Ogre::Vector3(0.1, 0.1, 0.1));
    cube->setPosition(Ogre::Vector3(0.0, 5.0, 0.0));
    btRigidBody *rigidBody = CRigidBodyFactory::getInstance()->getCube(cube->getSceneNode(), 10);
    CPhysicsManager::getInstance()->addRigidBody(rigidBody);
    CPhysicalObject *ship = new CPhysicalObject(cube, rigidBody);
    return ship;
}

CPhysicalObject *CShipsFactory::getAverageShip(Ogre::SceneManager *sceneMgr) const
{
    CRenderableObject *cube = new CRenderableObject(sceneMgr, CRenderableObject::PT_CUBE, "CubeNode");
    cube->setPosition(Ogre::Vector3(0.0, 50.0, 0.0));
    btRigidBody *rigidBody = CRigidBodyFactory::getInstance()->getCube(cube->getSceneNode(), 100);
    CPhysicsManager::getInstance()->addRigidBody(rigidBody);
    CPhysicalObject *ship = new CPhysicalObject(cube, rigidBody);
    ship->m_motor = 15000.0f;
    return ship;
}

CPhysicalObject *CShipsFactory::getBattleship(Ogre::SceneManager *sceneMgr) const
{
    CRenderableObject *cube = new CRenderableObject(sceneMgr, CRenderableObject::PT_CUBE, "CubeNode");
    cube->setScale(Ogre::Vector3(2, 2, 2));
    cube->setPosition(Ogre::Vector3(0.0, 100.0, 0.0));
    btRigidBody *rigidBody = CRigidBodyFactory::getInstance()->getCube(cube->getSceneNode(), 250);
    CPhysicsManager::getInstance()->addRigidBody(rigidBody);
    CPhysicalObject *ship = new CPhysicalObject(cube, rigidBody);
    ship->m_motor = 25000.0f;
    return ship;
}

CShipsFactory::~CShipsFactory()
{
}
