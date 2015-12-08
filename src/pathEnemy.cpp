#include <iostream>
#include <string>

#include "pathEnemy.h"
#include "txtLogger.h"

namespace {

	id::TXTLogger * logger = id::TXTLogger::getInstance();
}//namespace 

namespace id {
namespace scene {


PathEnemy::PathEnemy()
{
	logger->log("Initializing PathEnemy...", LL_DEBUG);

	logger->log("PathEnemy hsa been initialized.", LL_DEBUG);
}

PathEnemy::~PathEnemy()
{
	logger->log("Deleting PathEnemy...", LL_DEBUG);

	logger->log("PathEnemy has been deleting.", LL_DEBUG);
}


auto PathEnemy::enemyPatrol(bool enemyReachPos) -> void
{
	(void)enemyReachPos;
}

}//namespace scene 
}//namespace id
