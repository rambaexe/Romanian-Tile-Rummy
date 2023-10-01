#include <iostream>
#include <vector>

#include "console.h"
#include "classes.h"


using namespace std;

int main()
{
	Console rummy_console;

	vector <Tile*> alltiles = Tile::CreateTiles();
	vector <vector <Tile*>> stacks = Tile::CreateStacks(alltiles);
	//Tile::DisplayTiles(alltiles);
	Tile::DisplayStacks(stacks);

	vector <Player*> players = Player::InitialisePlayers();
	Player::DivideStacks(stacks, alltiles, players);

	// Player::DisplayPlayers(players);
	// Tile::DisplayStacks(stacks);
	rummy_console.pause_console();
	return 0;
}
