#include "physicalobject.h"
#include "renderableobject.h"
#include "inputmanager.h"

#include <OGRE/OgreVector3.h>
#include <OGRE/OgreQuaternion.h>
#include <OGRE/OgreSceneNode.h>
#include <bullet/BulletDynamics/Dynamics/btRigidBody.h>
#include <OIS/OIS.h>

CPhysicalObject::CPhysicalObject(CRenderableObject *renderableObject, btRigidBody *rigidBody)
    : m_renderable(renderableObject), m_rigidBody(rigidBody), m_motor(500.0f)
{
    CInputManager::getInstance()->addListener(this);
}

CPhysicalObject::~CPhysicalObject()
{
    CInputManager::getInstance()->removeListener(this);
    delete m_renderable;
}

void CPhysicalObject::update()
{
    btTransform t;
    m_rigidBody->getMotionState()->getWorldTransform(t);
    Ogre::Vector3 pos(t.getOrigin().getX(), t.getOrigin().getY(), t.getOrigin().getZ());
    m_renderable->setPosition(pos);
    Ogre::Quaternion q(t.getRotation().getW(), t.getRotation().getX(), t.getRotation().getY(), t.getRotation().getZ());
    m_renderable->setOrientation(q);
    updateLinearVelocity();
}

CRenderableObject *CPhysicalObject::getRenderableObject() const
{
    return m_renderable;
}

void CPhysicalObject::onMouseMoved(const OIS::MouseEvent &/*e*/)
{
}

bool CPhysicalObject::onKeyPressed(const OIS::KeyEvent &e)
{
    switch (e.key) {
    case OIS::KC_W:
    case OIS::KC_S: {
        m_rigidBody->clearForces();
        m_rigidBody->activate(true);
        bool sign = e.key == OIS::KC_W;
        Ogre::Vector3 force = m_renderable->getSceneNode()->getLocalAxes().GetColumn(0) *
                (sign ? -m_motor : m_motor);
        m_rigidBody->applyCentralForce(btVector3(force.x, force.y, force.z));
        break;
    }
    case OIS::KC_A:
    case OIS::KC_D: {
        m_rigidBody->clearForces();
        m_rigidBody->activate(true);
        bool signAngular = e.key == OIS::KC_A; // вращаемся влево или вправо
        m_rigidBody->setAngularVelocity(btVector3(0, signAngular ? 0.1 : -0.1, 0)); // по правилу буравчика
        updateLinearVelocity();
        break;
    }
    default:
        break;
    }

    return true;
}

bool CPhysicalObject::onKeyReleased(const OIS::KeyEvent &/*e*/)
{
    return true;
}

void CPhysicalObject::updateLinearVelocity()
{
    float linearDamping = 0.99f; // Будем считать, что скорость незначительно линейно затихает
    btVector3 oldLinearVelocity = m_rigidBody->getLinearVelocity(); // старое направление линейной скорости
    float speed = oldLinearVelocity.length();
    if (speed > 0.1) {
        m_rigidBody->activate(true);
        Ogre::Vector3 ogreDir = m_renderable->getSceneNode()->getLocalAxes().GetColumn(0);
        btVector3 dir(ogreDir.x, ogreDir.y, ogreDir.z); // новое направление линейной скорости
        bool codirected =
                    (oldLinearVelocity.x() * dir.x() >= 0) &&
                    (oldLinearVelocity.y() * dir.y() >= 0) &&
                    (oldLinearVelocity.z() * dir.z() >= 0); // имеет ли вектор линейной скорости и направления объекта одно и то же направление?
        speed = linearDamping * (codirected ? oldLinearVelocity.length() : -oldLinearVelocity.length());
        m_rigidBody->setLinearVelocity(dir * speed); // корректируем линейную скорость с учетом поворота
    }
}
