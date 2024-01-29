#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <functional>
#include <map>

#include "console_h.h"
#include "classes.h"
#include "test.h"


using namespace std;

int main()
{
	
	Console rummy_console;

	// FOR TESTING:
	// testformations();
	// testfirstmeld();
	// testpreset();
	
	//testfirstmeldbreakingame();
	//rummy_console.pause_console();



	Game game;
	vector <Tile*> alltiles = Tile::CreateTiles();
	//vector <Player*> players = Player::InitialisePlayers();
	vector <Player*> players = Player::InitialiseNPlayers(2);
	
	
	// ONE RUN: 
	vector <vector <Tile*>> stacks = Tile::CreateStacks(alltiles);
	//Tile::DisplayTiles(alltiles);
	Tile::DisplayStacks(stacks);
	vector <Tile*> stackqueue = game.DivideStacks(stacks, alltiles, players);
	vector <Tile*> queue;

	// Player::DisplayPlayers(players);
	cout << endl;
	cout << "Stacks queue:" << endl;
	Tile::DisplayTiles(stackqueue); cout << endl;
	
	game.Match(players, stackqueue, alltiles, queue);
	rummy_console.pause_console();
	//game.Reset_Match(players, stackqueue, alltiles, queue);

	
	
	// MULTIPLE RUNS: 
	//for (int i = 1; i <= 6; i++)
	//{
	//	vector <vector <Tile*>> stacks = Tile::CreateStacks(alltiles);
	//	//Tile::DisplayTiles(alltiles);
	//	Tile::DisplayStacks(stacks);
	//	vector <Tile*> stackqueue = game.DivideStacks(stacks, alltiles, players);

	//	// Player::DisplayPlayers(players);
	//	cout << endl;
	//	cout << "Stacks queue:" << endl;
	//	Tile::DisplayTiles(stackqueue); cout << endl;

	//	game.Reset_Match(alltiles, players);
	//}

	//for (int i = 1; i <= 6; i++)
	//{
	//	vector <vector <Tile*>> stacks = Tile::CreateStacks(alltiles);
	//	//Tile::DisplayTiles(alltiles);
	//	Tile::DisplayStacks(stacks);
	//	vector <Tile*> stackqueue = game.DivideStacks(stacks, alltiles, players);

	//	// Player::DisplayPlayers(players);
	//	cout << endl;
	//	cout << "Stacks queue:" << endl;
	//	Tile::DisplayTiles(stackqueue); cout << endl;

	//	vector <Tile*> queue;

	//	game.Match(players, stackqueue, alltiles, queue);

	//	game.Reset_Match(alltiles, players);
	//}
	
	// rummy_console.pause_console();
	return 0;
}


