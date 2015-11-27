#include "stateManager.h"
#include "txtLogger.h"

namespace {

	id::TXTLogger* logger = id::TXTLogger::getInstance();
}


namespace id {
namespace scene {

StateManager::StateManager()
{
	logger->log("Creating StateManager ...", LL_DEBUG);


	logger->log("StateManager has been created.", LL_INFO);
}

StateManager::~StateManager()
{
	logger->log("Deleting StateManager ...", LL_DEBUG);

	logger->log("StateManager has been deleted.", LL_INFO);
}


}//namespace scene
}//namespace id 
