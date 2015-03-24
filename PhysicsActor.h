#ifndef PHYSICSACTOR_H
#define PHYSICSACTOR_H

#include "Physics.h"

class PhysicsActor{
public:
	enum BODY_TYPE { CUBOID, SPHERE, STATIC_CUBOID, STATIC_SPHERE };

	PhysicsActor(hkpWorld* pWorld);
	~PhysicsActor();
	hkpRigidBody* getBody(){return mBody;}
	void createPCuboid(float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ, bool isStatic = false, float mass = 1.f);
	void createPSphere(float posX, float posY, float posZ, float size, bool isStatic = false, float mass = 1.f);
protected:
	hkpWorld* physicsWorld;
	hkpRigidBody* mBody;
};

#endif