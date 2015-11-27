#include <string>
#include <iostream>
#include <vector>

#include "player.h"
#include "txtLogger.h"


namespace {

	id::TXTLogger* logger = id::TXTLogger::getInstance();

}


namespace id {

namespace scene {


auto    Player::createPlayer(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, int eLife, int eHp, int eAttack) -> Player*
{
//	SDL_assert(scn && parent);

	Player* player = new (std::nothrow)Player(scn, parent, name, shader, path, eLife, eHp, eAttack);
	if (!player)
		logger->log("failed at creating player in Player::createPlayer(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, int eLife, int eHp, int eAttack)", LL_WARNING);

	return player;
}


Player::Player(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, int eLife, int eHp, int eAttack)
:Entity(scn, parent, name, shader, path, eLife, eHp, eAttack)
{
	logger->log("Creating Player...", LL_DEBUG);

	setSpeed(0.5f);
	setSpeedRun(1.f);
	
	logger->log("Player has been created.", LL_INFO);
}	

Player::~Player()
{
	logger->log("Deleting Player...", LL_DEBUG);

	logger->log("Player has been deleted.", LL_INFO);
}


}//namespace scene 
}//namespace id 
