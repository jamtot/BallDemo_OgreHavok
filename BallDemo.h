/*
-----------------------------------------------------------------------------
Filename:    BallDemo.h
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
#ifndef __BallDemo_h_
#define __BallDemo_h_

#include "BaseApplication.h"
#include "Actor.h"
#include "Physics.h"
#include "Player.h"
#include "enums.h"

//using namespace Ogre;
using namespace my_enums;

class BallDemo : public BaseApplication
{
public:
    BallDemo(void);
    virtual ~BallDemo(void);

protected:
	//trying out some cam stuff

	my_enums::cameraType camType;
	Vector3 TDCamPos;
	Vector3 TPSCamPos;
	Vector3 TPSCamDir;
	SceneNode * mMainTPSNode;
	SceneNode * mTPSSightNode;
	SceneNode * mTPSCameraNode;

    virtual void createScene(void);
	virtual void createCamera(void);
	virtual void destroyScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent&);

	// OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );


	Physics physics;
	SceneNode* cubeNode;

	Actor * sphereActor;
	Actor * cubeActor;
	Actor * platActor;

	Player * mPlayer;

	bool mIsPaused;
};


#endif // #ifndef __BallDemo_h_
