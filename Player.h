#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "enums.h"
using namespace my_enums;
class Player : public Actor
{
public:
	Player(SceneManager * sceneMgr, hkpWorld* pWorld);
	~Player(void);
	void setCamMode(my_enums::cameraType cMode){camMode = cMode;}
	void update(Ogre::Quaternion orientation);

	void setMoveForward(bool b){moveForward = b;}
	void setMoveBackward(bool b){moveBackward = b;}
	void setMoveLeft(bool b){moveLeft = b;}
	void setMoveRight(bool b){moveRight = b;}
protected:
	Ogre::Quaternion mOrientation;
	my_enums::cameraType camMode;
	bool moveForward;
	bool moveBackward;
	bool moveLeft;
	bool moveRight;

	void movement();

};

#endif

