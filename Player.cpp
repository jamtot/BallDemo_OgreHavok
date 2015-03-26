#include "Player.h"


Player::Player(SceneManager * sceneMgr, hkpWorld* pWorld) : Actor(sceneMgr, pWorld)
{
}


Player::~Player(void)
{
}

void Player::update(void)
{
	Actor::update();
}