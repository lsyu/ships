#include "renderableobject.h"

#include <OGRE/Ogre.h>

CRenderableObject::CRenderableObject(Ogre::SceneManager *sceneMgr, EPrefabType type,
                                     const std::string &nameOfNode)
    : m_entity(sceneMgr->createEntity(static_cast<Ogre::SceneManager::PrefabType>(type))),
      m_sceneNode(sceneMgr->getRootSceneNode()->createChildSceneNode(nameOfNode)),
      m_sceneMgr(sceneMgr)
{
    if (type == PT_PLANE) {
        m_sceneNode->scale(10, 10, 10);
        m_sceneNode->rotate(Ogre::Vector3::NEGATIVE_UNIT_X, Ogre::Radian(Ogre::Degree(90)), Ogre::Node::TS_WORLD);
    }
    m_sceneNode->attachObject(m_entity);

}

CRenderableObject::~CRenderableObject()
{
    m_sceneMgr->destroySceneNode(m_sceneNode);
    m_sceneMgr->destroyEntity(m_entity);
}

Ogre::SceneNode *CRenderableObject::getSceneNode() const
{
    return m_sceneNode;
}

void CRenderableObject::setPosition(const Ogre::Vector3 &position)
{
    m_sceneNode->setPosition(position);
}

void CRenderableObject::setOrientation(const Ogre::Quaternion &orientation)
{
    m_sceneNode->setOrientation(orientation);
}

void CRenderableObject::setScale(const Ogre::Vector3 &scale)
{
    m_sceneNode->setScale(scale);
}
