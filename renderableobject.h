#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

namespace Ogre {
class SceneManager;
class SceneNode;
class Entity;
class Vector3;
class Quaternion;
} // namespace Ogre

#include <string>

class CRenderableObject
{
public:
    enum EPrefabType {
        PT_PLANE,
        PT_CUBE,
        PT_SPHERE
    }; // enum EPrefabType
    CRenderableObject(Ogre::SceneManager *sceneMgr, EPrefabType type, const std::string &nameOfNode);
    ~CRenderableObject();

    Ogre::SceneNode *getSceneNode() const;
    void setPosition(const Ogre::Vector3 &position);
    void setOrientation(const Ogre::Quaternion &orientation);
    void setScale(const Ogre::Vector3 &scale);

private:
    Ogre::Entity *m_entity;
    Ogre::SceneNode *m_sceneNode;
    Ogre::SceneManager *m_sceneMgr;
}; // class CRenderableObject

#endif // RENDERABLEOBJECT_H
