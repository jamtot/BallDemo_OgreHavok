#pragma once
#include "OgreActor.h"
#include "PhysicsActor.h"
using namespace Ogre;
class Actor :
	public OgreActor,
	public PhysicsActor
{
public:
	Actor(SceneManager * sceneMgr, hkpWorld* pWorld);
	~Actor(void);

	virtual void update(void);

	//maybe pass hkVector4 by reference?
	void createSphere(float posX, float posY, float posZ, float size, bool isStatic = false, float mass = 1.0f);
	void createCuboid(float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ, bool isStatic = false, float mass = 1.0f);
	

	Vector3 getOgreBodyPosition(){
			hkVector4 p(0,0,0);
			p = mBody->getPosition();
			Vector3 pos = Vector3(p(0),p(1),p(2));
			return pos;
	}
protected:
	SceneManager * mSceneMgr;
	hkpWorld * mPWorld;
	bool isSet; //will track whether the actor has been initialised or not
};

