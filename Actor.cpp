#include "Actor.h"


Actor::Actor(SceneManager * sceneMgr, hkpWorld* pWorld) 
	: OgreActor(sceneMgr), PhysicsActor(pWorld), isSet(false)
{
}


Actor::~Actor(void)
{
}

void Actor::update(void)
{
	hkVector4 p(0,0,0);
	p = mBody->getPosition();
	Vector3 pos = Vector3(p(0),p(1),p(2));
	m_node->setPosition(pos);

	hkQuaternion q; 
	q = hkQuaternion(mBody->getRotation());
	Radian angleRot;
	angleRot = q.getAngle();

	hkVector4 axis = hkVector4(0,0,0);
	if(q.hasValidAxis())
		q.getAxis(axis); 

	Vector3 axisRot = Vector3(axis(0),axis(1),axis(2));

	Quaternion newOgRot = Ogre::Quaternion(angleRot,axisRot);

	//sets the ogre objects position and rotation to that of the physics object
	trackPhysObj(pos, newOgRot);
}

void Actor::createSphere(float posX, float posY, float posZ, float size, bool isStatic, float mass)
{
	if (!isSet){
		Vector3 oPos(posX, posY, posZ);
		createOSphere(oPos, size);
		createPSphere( posX, posY, posZ, size, isStatic, mass); 
		isSet = true;
	}
}

void Actor::createCuboid(float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ, bool isStatic, float mass)
{
	if (!isSet){
		Vector3 oPos(posX, posY, posZ);
		Vector3 oHalfWidths(sizeX, sizeY, sizeZ);
		createOCuboid(oPos, oHalfWidths);
		createPCuboid(posX, posY, posZ, sizeX, sizeY, sizeZ, isStatic, mass);
		isSet = true;
	}
}
