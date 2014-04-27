#ifndef CSIPSFACTORY_H
#define CSIPSFACTORY_H

#include "singletonimpldel.h"
#include "physicalobject.h"

namespace Ogre {
class SceneManager;
}

class CShipsFactory
{
public:

    friend class __CSingletonImplDel<CShipsFactory>;
    static CShipsFactory *getInstance();
    CShipsFactory(const CShipsFactory &) = delete;
    CShipsFactory &operator =(const CShipsFactory &) = delete;

    CPhysicalObject *getBoat(Ogre::SceneManager *sceneMgr) const;
    CPhysicalObject *getAverageShip(Ogre::SceneManager *sceneMgr) const;
    CPhysicalObject *getBattleship(Ogre::SceneManager *sceneMgr) const;
protected:
    CShipsFactory();
    ~CShipsFactory();

private:
    static CShipsFactory *instance;
}; // class CShipsFactory

#endif // CSHIPSFACTORY_H
