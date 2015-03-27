/*
-----------------------------------------------------------------------------
Filename:    BallDemo.cpp
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
#include "BallDemo.h"

//-------------------------------------------------------------------------------------
BallDemo::BallDemo(void)
{
}
//-------------------------------------------------------------------------------------
BallDemo::~BallDemo(void)
{
	
}

//-------------------------------------------------------------------------------------
void BallDemo::createScene(void)
{
	physics.SetUp();


	sphereActor = new Actor(mSceneMgr, physics.GetPhysicsWorld() );
	sphereActor->createSphere(2.f,10.f,0.f,.9f);

	cubeActor = new Actor(mSceneMgr, physics.GetPhysicsWorld() );
	cubeActor->createCuboid(-3.5f,15.f,-5.5f,.6f,2.f,.9f);

	platActor = new Actor(mSceneMgr, physics.GetPhysicsWorld() );
	platActor->createCuboid(0.f, 0.f, 0.f, 100.f,1.f,100.f, true);

	mPlayer = new Player(mSceneMgr, physics.GetPhysicsWorld() );
	mPlayer->createSphere(0.f,15.f,0.f,1.f);
	// Create a Light and set its position

	Ogre::Light* light = mSceneMgr->createLight("MainLight");

	light->setPosition(20.0f, 80.0f, 50.0f);


}

void BallDemo::createCamera(void){
	// Create the camera
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

void BallDemo::destroyScene(void){
	physics.TidyUp();
	BaseApplication::destroyScene();
}

bool BallDemo::frameRenderingQueued(const Ogre::FrameEvent& evt){

	physics.Simulate(evt.timeSinceLastFrame);
	sphereActor->update();
	cubeActor->update();
	platActor->update();
	mPlayer->update(mMainTPSNode->getOrientation());

	switch (camType)
	{
	case FREE_VIEW:
		break;
	case TPS:
		mMainTPSNode->setPosition(mPlayer->getOgreBodyPosition());
		//mCamera->setPosition(mTPSCameraNode->getPosition());
		break;
	case TOP_DOWN:
		mCamera->setPosition(Ogre::Vector3(mPlayer->getOgreBodyPosition().x,mCamera->getPosition().y, mPlayer->getOgreBodyPosition().z));
		break;
	}


	return BaseApplication::frameRenderingQueued(evt);
}

bool BallDemo::keyPressed( const OIS::KeyEvent &arg )
{

	if (arg.key == OIS::KC_Z) 
	{
		Quaternion q = Quaternion();
		switch (camType)
		{
		case FREE_VIEW:
			camType = TPS;
			mMainTPSNode->setPosition(mPlayer->getOgreBodyPosition());
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
			TDCamPos = Vector3(mPlayer->getOgreBodyPosition().x, mPlayer->getOgreBodyPosition().y + 15, mPlayer->getOgreBodyPosition().z);
			mCamera->setPosition(TDCamPos);
			break;
		case TOP_DOWN:
			camType = FREE_VIEW;
			break;
		}
		mPlayer->setCamMode(camType);
	}

	switch (camType)
	{
	case FREE_VIEW:
		mCameraMan->injectKeyDown(arg);
			break;
	case TPS:
	case TOP_DOWN:
		if (arg.key == OIS::KC_W){mPlayer->setMoveForward(true);}
		if (arg.key == OIS::KC_S){mPlayer->setMoveBackward(true);}
		if (arg.key == OIS::KC_A){mPlayer->setMoveLeft(true);}
		if (arg.key == OIS::KC_D){mPlayer->setMoveRight(true);}
		break;
	}

	return BaseApplication::keyPressed(arg);
}

bool BallDemo::keyReleased( const OIS::KeyEvent &arg ){
	
	switch (camType)
	{
	case FREE_VIEW:
		mCameraMan->injectKeyUp(arg);
		break;
	case TPS:
	case TOP_DOWN:
		if (arg.key == OIS::KC_W){mPlayer->setMoveForward(false);}
		if (arg.key == OIS::KC_S){mPlayer->setMoveBackward(false);}
		if (arg.key == OIS::KC_A){mPlayer->setMoveLeft(false);}
		if (arg.key == OIS::KC_D){mPlayer->setMoveRight(false);}
		break;
	}

	return BaseApplication::keyReleased(arg);
}

bool BallDemo::mouseMoved( const OIS::MouseEvent &arg )
{

	switch (camType)
	{
	case FREE_VIEW:
		if (mTrayMgr->injectMouseMove(arg)) return true;
		mCameraMan->injectMouseMove(arg);
		break;
	case TPS:
		mMainTPSNode->yaw(Ogre::Degree(-arg.state.X.rel * 0.25f));
		//mMainTPSNode->pitch(Ogre::Degree(-arg.state.Y.rel * 0.25f));
		break;
	case TOP_DOWN:
		TDCamPos.y = TDCamPos.y + arg.state.Y.rel * 0.025f;
		if (TDCamPos.y < 8) TDCamPos.y = 8;
		mCamera->setPosition(TDCamPos);
		break;
	}

    return BaseApplication::mouseMoved(arg);
}

bool BallDemo::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
	return BaseApplication::mousePressed(arg, id);
}
bool BallDemo::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
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
		BallDemo app;

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
