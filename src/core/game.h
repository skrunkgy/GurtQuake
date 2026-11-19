// gqGame : Represents the state of the game

#ifndef GQ_GAME_H
#define GQ_GAME_H

#include "actor.h"

class gqGame
{

private:
	
	gqWorld*		world;
	gqResource*		resourcePool; // FIXME: I am not sure who should be responsible for the resource pool

public:

	gqActor*		actors;

	gqGame();
	~gqGame();

};

extern gqGame*		gameLocal; // dont forget to define this later

#endif
