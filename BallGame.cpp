/*
-----------------------------------------------------------------------------
Filename:    BallGame.cpp
-----------------------------------------------------------------------------

This source file is part of the
___                 __    __ _ _    _ 
/___\__ _ _ __ ___  / / /\ \ (_) | _(_)
//  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
|___/                              
Tutorial Framework
http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "BallGame.h"

//-------------------------------------------------------------------------------------
BallGame::BallGame(void)
{
}
//-------------------------------------------------------------------------------------
BallGame::~BallGame(void)
{
	
}

//-------------------------------------------------------------------------------------
void BallGame::createScene(void)
{
	physics.SetUp();


	sphereActor = new Actor(mSceneMgr, physics.GetPhysicsWorld() );
	sphereActor->createSphere(0.f,10.f,0.f,5.f);

	cubeActor = new Actor(mSceneMgr, physics.GetPhysicsWorld() );
	cubeActor->createCuboid(0.5f,15.f,0.5f,5.f,4.f,3.f);

	platActor = new Actor(mSceneMgr, physics.GetPhysicsWorld() );
	platActor->createCuboid(0.f, 0.f, 0.f, 100.f,1.f,100.f, true);


	// Create a Light and set its position

	Ogre::Light* light = mSceneMgr->createLight("MainLight");

	light->setPosition(20.0f, 80.0f, 50.0f);


}

void BallGame::destroyScene(void){
	physics.TidyUp();
	BaseApplication::destroyScene();
}

bool BallGame::frameRenderingQueued(const Ogre::FrameEvent& evt){

	physics.Simulate(evt.timeSinceLastFrame);
	sphereActor->update();
	cubeActor->update();
	platActor->update();


	return BaseApplication::frameRenderingQueued(evt);
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
	int main(int argc, char *argv[])
#endif
	{
		// Create application object
		BallGame app;

		try {
			app.go();
		} catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occured: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif
