#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <functional>

#include "console_h.h"
#include "classes.h"


using namespace std;

int main()
{
	Console rummy_console;
	Game game;
	//vector <Player*> players = Player::InitialisePlayers();
	vector <Player*> players = Player::InitialiseNPlayers(4);
	vector <Tile*> alltiles = Tile::CreateTiles();


	vector <vector <Tile*>> stacks = Tile::CreateStacks(alltiles);
	//Tile::DisplayTiles(alltiles);
	Tile::DisplayStacks(stacks);

	vector <Tile*> stackqueue = Game::DivideStacks(stacks, alltiles, players);

	// Player::DisplayPlayers(players);
	cout << endl;
	cout << "Stacks queue:" << endl;
	Tile::DisplayTiles(stackqueue); cout << endl;

	vector <Tile*> queue;

	Game::Match(players, stackqueue, alltiles, queue);

	// MULTIPLE RUNS: 
	//for (int i = 1; i <= 4; i++)
	//{
	//	vector <vector <Tile*>> stacks = Tile::CreateStacks(alltiles);
	//	//Tile::DisplayTiles(alltiles);
	//	Tile::DisplayStacks(stacks);

	//	vector <Tile*> stackqueue = Game::DivideStacks(stacks, alltiles, players);

	//	// Player::DisplayPlayers(players);
	//	cout << endl;
	//	cout << "Stacks queue:" << endl;
	//	Tile::DisplayTiles(stackqueue);

	//	game.Reset_Match(alltiles, players);
	//}
	
	rummy_console.pause_console();
	return 0;
}
