#include <string>

#include "guiLifeBar.h"
#include "device.h"
#include "stateManager.h"
#include "player.h"
#include "logger.h"
#include "eventManager.h"
#include "eventPlayer.h"

namespace id {
namespace scene {

Player::Player(Device* dev, SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path)
:Entity(scn, parent, name, shader, path), dev(dev)
{
	LOG(L_DEBUG, "Creating Player...");

	setHp(9);
	setLife(3);
	setAttack(3);

	if (!static_cast<event::EventPlayer*>(this->dev->getEventManager()->getEventFromName("EventPlayer"))->getPlayer())
		static_cast<event::EventPlayer*>(this->dev->getEventManager()->getEventFromName("EventPlayer"))->setPlayer(this);

	LOG(L_DEBUG, "Player has been created.");

}

Player::~Player()
{
	LOG(L_DEBUG, "Deleting Player...");

	static_cast<event::EventPlayer*>(this->dev->getEventManager()->getEventFromName("EventPlayer"))->deletePlayer();
	this->dev = nullptr;

	LOG(L_DEBUG, "Player has been deleted.");
}

auto Player::createPlayer(Device* dev, SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path) -> Player*
{
	Player* player = new(std::nothrow)Player(dev, scn, parent, name, shader, path);

	if(!player)
		LOG(L_WARNING, "Failed at creating player in Player::createPlayer(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path)");

	return player;
}


}//namespace id 
}//namespace scene 
