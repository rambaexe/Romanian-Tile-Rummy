#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <functional>
#include <map>
#include <iomanip>
#include <fstream>

#include "console_h.h"
#include "classes.h"
#include "test.h"



using namespace std;

int main()
{
	/*ofstream fout;
	fout.open(".txt", ios::app);
	fout.close();*/


	Console rummy_console;

	// TESTING:
	// testpreset();
	//testpreset_multipleruns();
	//testfirstmeldbreakingame();
	//testpreset_multipleruns3();
	//rummy_console.pause_console();


	Game game;

	vector <Player*> players = Player::InitialiseNPlayerBots2(4,2,2);

	//vector <Player*> players = Player::InitialiseNPlayerBots(4); 
	//vector <Player*> players = Player::InitialisePlayers();


	// FIRST RUN ------------------------------------------------------------------------------
	
	// all tiles
	vector <Tile*> alltiles = Tile::CreateTiles(); 

	// stacksqueue and divide to players
	vector <vector <Tile*>> stacks = Tile::CreateStacks(alltiles); 
	Tile::DisplayStacks(stacks); cout << endl; 
	vector <Tile*> stackqueue = game.DivideStacks(stacks, alltiles, players); 
	cout << "Stacks queue:" << endl; 
	Tile::DisplayTiles(stackqueue); cout << endl; Console::pause_console();

	//queue
	vector <Tile*> queue;
	
	// excel 
	Game::OutputToExcel_beginning(players, stackqueue, queue);

	//match
	game.Match(players, stackqueue, alltiles, queue); 
	rummy_console.pause_console(); 

	// FIRST RUN ------------------------------------------------------------------------------

	for (int i = 1; i < 10; i++)
	{
		// MULTIPLE RUNS ------------------------------------------------------------------------------

		// alltiles
		alltiles = Tile::CreateTiles();

		// stacksqueue and divide to players
		stacks = Tile::CreateStacks(alltiles);
		Tile::DisplayStacks(stacks);
		stackqueue = game.DivideStacks(stacks, alltiles, players);
		cout << "Stacks queue:" << endl;
		Tile::DisplayTiles(stackqueue); cout << endl;

		//queue

		//match
		game.Match(players, stackqueue, alltiles, queue);
		rummy_console.pause_console();

		// MULTIPLE RUNS ------------------------------------------------------------------------------

	}
 	return 0;
}


