#include "Player.h"


Player::Player(SceneManager * sceneMgr, hkpWorld* pWorld) : Actor(sceneMgr, pWorld)
{
	moveForward = moveBackward = moveLeft = moveRight = false;
}


Player::~Player(void)
{
}

void Player::update(Ogre::Quaternion orientation)
{
	mOrientation = orientation;
	movement();
	Actor::update();
}

void Player::movement(){
	if (moveForward)
	{//move the player forward
		Vector3 v(0.0,0.0,0.1);
		Vector3 result = mOrientation * v;
		switch (camMode)
		{
		case FREE_VIEW:
			break;
		case TPS:
			
			mBody->applyLinearImpulse(hkVector4(result.x,0,result.z));
			break;
		case TOP_DOWN:
			mBody->applyLinearImpulse(hkVector4(0.0,0.0,-0.1));
			break;
		}
	}
	else if (moveBackward)
	{//move the player backward
		Vector3 v(0.0,0.0,-0.1);
		Vector3 result = mOrientation * v;
			switch (camMode)
		{
		case FREE_VIEW:
			break;
		case TPS:
			
			mBody->applyLinearImpulse(hkVector4(result.x,0,result.z));
			break;
		case TOP_DOWN:
			mBody->applyLinearImpulse(hkVector4(0.0,0.0,0.1));
			break;
		}
	}

	if (moveLeft)
	{//move the player left
		Vector3 v(0.1,0.0,0.0);
		Vector3 result = mOrientation * v;
			switch (camMode)
		{
		case FREE_VIEW:
			break;
		case TPS:
			
			mBody->applyLinearImpulse(hkVector4(result.x,0,result.z));
			break;
		case TOP_DOWN:
			mBody->applyLinearImpulse(hkVector4(-0.1,0.0,0.0));
			break;
		}
	}
	else if (moveRight)
	{//move the player right
		Vector3 v(-0.1,0.0,0.0);
		Vector3 result = mOrientation * v;
			switch (camMode)
		{
		case FREE_VIEW:
			break;
		case TPS:
			mBody->applyLinearImpulse(hkVector4(result.x,0,result.z));
			break;
		case TOP_DOWN:
			//mBody->applyForce(mDeltaTime,hkVector4(-10.0,0.0,0.0));
			mBody->applyLinearImpulse(hkVector4(0.1,0.0,0.0));
			break;
		}
	}
}