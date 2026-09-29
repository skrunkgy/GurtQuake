// gqGame : Represents the state of the game

#ifndef GQ_GAME_H
#define GQ_GAME_H

class gqGame
{

private:
	
	gqCamera* mainCam;
	gqWorld* world;

public:
	gqGame();
	~gqGame();


};

extern gqGame* gameLocal; // dont forget to define this later

#endif
