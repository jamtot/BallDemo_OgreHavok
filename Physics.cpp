#include "Physics.h"

Physics::Physics(void)
{
}


Physics::~Physics(void)
{
}

void Physics::SetUp(void)
{
	// Perfrom platform specific initialization for this demo - you should already have something similar in your own code.
	//PlatformInit();

	// Need to have memory allocated for the solver. Allocate 1mb for it.
	hkMemoryRouter* memoryRouter = hkMemoryInitUtil::initDefault( hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo(1024 * 1024) );
	hkBaseSystem::init( memoryRouter, errorReport );

	{
		world = new hkpWorld( hkpWorldCinfo() );

		// Register all collision agents
		// It's important to register collision agents before adding any entities to the world.
		hkpAgentRegisterUtil::registerAllAgents( world->getCollisionDispatcher() );
	}

}

void Physics::Simulate(float secTime){
	//if(secTime>0.00001)// time of zero causes an exception 
	if(secTime>0.00001)// time of zero causes an exception 
		world->stepDeltaTime(secTime);
}

void Physics::TidyUp(void){

	// Release the reference on the world
	world->removeReference();

	hkBaseSystem::quit();
	hkMemoryInitUtil::quit();
}

void Physics::addPlane(void){
	//hkpRigidBody* rigidBody;
	
	// Create a box 1 by 2 by 3
	hkVector4 halfExtents; halfExtents.set(10.f, 1.f, 10.f);
	hkpBoxShape* boxShape = new hkpBoxShape(halfExtents);
		
	hkpRigidBodyCinfo bodyCinfo;
		
	bodyCinfo.m_motionType = hkpMotion::MOTION_FIXED;
	bodyCinfo.m_qualityType = HK_COLLIDABLE_QUALITY_FIXED;// default collision quality

	bodyCinfo.m_shape = boxShape;
	bodyCinfo.m_position = hkVector4(0.0f, -1.0f, 0.0f);

	// Create the rigid body
	platformShape = new hkpRigidBody(bodyCinfo);

	// No longer need the reference on the boxShape, as the rigidBody now owns it
	boxShape->removeReference();
	

	// Add the rigidBody to the world
	world->addEntity(platformShape);

	// No longer need the ref of rigidBody - as the world now owns it
	//rigidBody->removeReference();
}

void Physics::addCuboid(float posX, float posY, float posZ, float halfX, float halfY, float halfZ){
	
	hkVector4 pos; pos.set(posX, posY, posZ);
	//hkpRigidBody* rigidBody;

	// Create a box 1 by 2 by 3
	hkVector4 halfExtents; halfExtents.set(halfX, halfY, halfZ);
	hkpBoxShape* boxShape = new hkpBoxShape(halfExtents);

	hkpRigidBodyCinfo bodyCinfo;
	bodyCinfo.m_shape = boxShape;
	bodyCinfo.m_position = pos;

	//  Calculate the mass properties for the shape
	const hkReal boxMass = 1.0f;
	hkMassProperties massProperties;
	hkpInertiaTensorComputer::computeShapeVolumeMassProperties(boxShape, boxMass, massProperties);

	bodyCinfo.setMassProperties(massProperties);

	// Create the rigid body
	cubeShape = new hkpRigidBody(bodyCinfo);

	// No longer need the reference on the boxShape, as the rigidBody now owns it
	boxShape->removeReference();
	
		
	// Add the rigidBody to the world
	world->addEntity(cubeShape);

	// No longer need the ref of rigidBody - as the world now owns it
	//rigidBody->removeReference();
}

/*hkVector4 Physics::getCubePosition()
{
	return cubeShape->getPosition();
}

hkVector4 Physics::getPlatPosition()
{
	return platformShape->getPosition();
}*/