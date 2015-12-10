#include <iostream>
#include <string>

#include "device.h"
#include "stateManager.h"
#include "player.h"
#include "txtLogger.h"
#include "eventManager.h"


namespace {

	id::TXTLogger * logger = id::TXTLogger::getInstance();

}//namespace 

namespace id {
namespace scene {

Player::Player(Device* dev, SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path)
:Entity(scn, parent, name, shader, path), dev(dev)
{
	logger->log("Creating Player...", LL_DEBUG);

	setHp(9);
	setLife(3);
	setAttack(3);

	logger->log("Player has been created.", LL_DEBUG);

}

Player::~Player()
{
	logger->log("Deleting Player...", LL_DEBUG);

	this->dev = nullptr;

	logger->log("Player has been deleted.", LL_DEBUG);
}

auto Player::createPlayer(Device* dev, SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path) -> Player*
{
	Player* player = new(std::nothrow)Player(dev, scn, parent, name, shader, path);

	if(!player)
		logger->log("Failed at creating player in Player::createPlayer(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path)", LL_WARNING);

	return player;
}


}//namespace id 
}//namespace scene 
