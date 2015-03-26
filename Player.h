#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"

class Player : public Actor
{
public:
	enum CAM_MODE { FREE_VIEW, TPS, TOP_DOWN };
	Player(SceneManager * sceneMgr, hkpWorld* pWorld);
	~Player(void);
	void setCamMode(CAM_MODE cMode){camMode = cMode;}
	void update(void);
protected:
	Ogre::Quaternion mOrientation;
	CAM_MODE camMode;
};

#endif

