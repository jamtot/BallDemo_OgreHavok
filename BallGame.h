/*
-----------------------------------------------------------------------------
Filename:    BallGame.h
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
#ifndef __BallGame_h_
#define __BallGame_h_

#include "BaseApplication.h"
#include "Actor.h"
#include "Physics.h"

//using namespace Ogre;

class BallGame : public BaseApplication
{
public:
    BallGame(void);
    virtual ~BallGame(void);

protected:
    virtual void createScene(void);
	virtual void destroyScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent&);

	Physics physics;
	SceneNode* cubeNode;

	Actor * sphereActor;
	Actor * cubeActor;
	Actor * platActor;
};


#endif // #ifndef __BallGame_h_
