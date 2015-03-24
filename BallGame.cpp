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

void BallGame::createCamera(void){
	// Create the camera
  
  //  mCamera = mSceneMgr->createCamera("PlayerCam");

  //  // Position it at 500 in Z direction
  //  mCamera->setPosition(Ogre::Vector3(0,10,50));
  //  // Look back along -Z
  //  mCamera->lookAt(Ogre::Vector3(0,0,0));
  //  mCamera->setNearClipDistance(5);

  //  mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller


	mCamera = mSceneMgr->createCamera("PlayerCam");
	camType = FREE_VIEW;

	switch (camType)
	{
	case FREE_VIEW:
		//original cam settings
		// Position it at 500 in Z direction
		mCamera->setPosition(Ogre::Vector3(0,20,80));
		// Look back along -Z
		//mCamera->lookAt(Ogre::Vector3(0,0,-300));
		mCamera->setNearClipDistance(1);
		break;
	case TPS:
		break;
	case TOP_DOWN:
		// Create the camera facing downwards
		mCamera->setPosition(Ogre::Vector3(0,25,0));
		mCamera->setNearClipDistance(5);
		mCamera->pitch(Ogre::Degree(-90));
		break;
	}

	// Setup basic node structure to handle 3rd person cameras
    mMainTPSNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode ("TPSNODE");
    mTPSSightNode = mMainTPSNode->createChildSceneNode ("TPSNODE_sight", Vector3 (0, 0, 10));
    mTPSCameraNode = mMainTPSNode->createChildSceneNode ("TPSNODE_camera", Vector3 (0, 0.2, -3));
	mTPSCameraNode->setAutoTracking (true, mTPSSightNode); // The camera will always look at the camera target
    mTPSCameraNode->setFixedYawAxis (true); // Needed because of auto tracking
	mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller

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

	switch (camType)
	{
	case FREE_VIEW:
		break;
	case TPS:
		mMainTPSNode->setPosition(sphereActor->getOgreBodyPosition());
		//mCamera->setPosition(mTPSCameraNode->getPosition());
		break;
	case TOP_DOWN:
		mCamera->setPosition(Ogre::Vector3(sphereActor->getOgreBodyPosition().x,mCamera->getPosition().y, sphereActor->getOgreBodyPosition().z));
		break;
	}


	return BaseApplication::frameRenderingQueued(evt);
}

bool BallGame::keyPressed( const OIS::KeyEvent &arg )
{

	if (arg.key == OIS::KC_Z) 
	{
		Quaternion q = Quaternion();
		switch (camType)
		{
		case FREE_VIEW:
			camType = TPS;
			mMainTPSNode->setPosition(sphereActor->getOgreBodyPosition());
			mCamera->setPosition(mTPSCameraNode->getPosition());
			mCamera->setPosition(0.0,0.0,0.0);
			mCamera->setOrientation(q);
			mTPSCameraNode->attachObject(mCamera);
			break;
		case TPS:
			mTPSCameraNode->detachObject(mCamera);
			mCamera->setOrientation(q);
			mCamera->pitch(Ogre::Degree(-90));
			camType = TOP_DOWN;
			TDCamPos = Vector3(sphereActor->getOgreBodyPosition().x, sphereActor->getOgreBodyPosition().y + 10, sphereActor->getOgreBodyPosition().z);
			mCamera->setPosition(TDCamPos);
			break;
		case TOP_DOWN:
			camType = FREE_VIEW;
			break;
		}
		//mPlayer->setCamMode((int)camType);
	}

	switch (camType)
	{
	case FREE_VIEW:
		mCameraMan->injectKeyDown(arg);
			break;
	case TPS:
	case TOP_DOWN:
	/*	if (arg.key == OIS::KC_W){mPlayer->setForward(true);}
		if (arg.key == OIS::KC_S){mPlayer->setBackward(true);}
		if (arg.key == OIS::KC_A){mPlayer->setLeft(true);}
		if (arg.key == OIS::KC_D){mPlayer->setRight(true);}*/
		break;
	}

	return BaseApplication::keyPressed(arg);
}

bool BallGame::keyReleased( const OIS::KeyEvent &arg ){
	return BaseApplication::keyReleased(arg);
}
    // OIS::MouseListener
bool BallGame::mouseMoved( const OIS::MouseEvent &arg ){
	return BaseApplication::mouseMoved(arg);
}
bool BallGame::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
	return BaseApplication::mousePressed(arg, id);
}
bool BallGame::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
	return BaseApplication::mouseReleased(arg, id);
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
