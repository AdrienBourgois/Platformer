#include "stateMachine.h"
#include "txtLogger.h"

namespace {

	id::TXTLogger* logger = id::TXTLogger::getInstance();
}


namespace id {
namespace scene {

StateMachine::StateMachine()
{
	logger->log("Creating StateMachine ...", LL_DEBUG);


	logger->log("StateMachine has been created.", LL_INFO);
}

StateMachine::~StateMachine()
{
	logger->log("Deleting StateMachine ...", LL_DEBUG);

	logger->log("StateMachine has been deleted.", LL_INFO);
}


}//namespace scene
}//namespace id 
