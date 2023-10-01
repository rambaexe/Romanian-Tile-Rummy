#ifndef classes
#define classes

#include <iostream>
#include <string.h>
#include <algorithm> 
#include <ctime>   
#include <random>
using namespace std;

const int stacksno = 15;
const int tilesinstackno = 7;
const int tilesno = 13;
const int nono = 2;
const int tilesingameno = 106;

class Tile
{
public:
	string type;
	int downpoints;
	int finalpoints;
	int no;
	bool atu;

	Tile(string type, int no) : type(type), no(no)
	{
		downpoints = 0;
		finalpoints = 0;
		atu = false;
	}

	void virtual displayInfo() const
	{
		/*cout << "Type: " << type << endl;
		cout << "No: " << no << endl;
		cout << "Down Points: " << downpoints << endl;
		cout << "Final Points: " << finalpoints << endl;*/
	}

	static vector<Tile*> CreateTiles();

	static void DisplayTiles(vector <Tile*>& tiles)
	{
		for (const auto& tile : tiles)
		{
			tile->displayInfo();
		}
	}

	static void DisplayStacks(vector <vector<Tile*>> stacks)
	{
		for (auto& stack : stacks)
		{
			Tile::DisplayTiles(stack);
			cout << endl;
			//cout << "--------------------------------------------------" << endl;
		}
	}

	static vector<Tile*> RandomiseTiles(vector<Tile*> tiles)
	{
		random_device rd;
		mt19937 engine(rd());
		shuffle(tiles.begin(), tiles.end(), engine);
		return tiles;
	}

	static vector<vector<Tile*>> CreateStacks(vector <Tile*> tiles)
	{
		tiles = Tile::RandomiseTiles(tiles);
		vector<vector<Tile*>> stacks;
		for (int j = 1; j <= stacksno; j++)
		{
			vector <Tile*> stack;
			for (int i = 0; i < tilesinstackno; i++)
			{
				stack.push_back(tiles[(j - 1) * tilesinstackno + i]);
			}
			stacks.push_back(stack);
		}
		vector <Tile*> stack;
		stack.push_back(tiles[tiles.size() - 1]);
		tiles[tiles.size() - 1]->atu = true;
		stacks.push_back(stack);
		return stacks;
	}

	int virtual getnumber()
	{
		return 0;
	}
};

class NormalTile : public Tile
{
public:
	string colour;
	int number;

	NormalTile(string colour, int number, int no) : Tile("normal", no), colour(colour), number(number)
	{
		if (number == 1)
		{
			finalpoints = 25;
		}
		else {
			if (number >= 2 && number <= 9)
			{
				finalpoints = 5;
			}
			else
			{
				if (number >= 10 && number <= 13)
				{
					finalpoints = 10;
				}
			}
		}
	}

	void displayInfo() const override
	{
		Tile::displayInfo();
		/*cout << "Colour: " << colour << endl;
		cout << "Number: " << number << endl;*/


		if (colour == "blue")
			Console::setConsoleColour(blue);
		else
			if (colour == "red")
				Console::setConsoleColour(red);
			else
				if (colour == "yellow")
					Console::setConsoleColour(yellow);
				else
					Console::setConsoleColour(white);

		cout << number;
		Console::setConsoleColour(white);
		cout << " | ";
		//cout << endl;
	}

	int getnumber() override
	{
		return number;
	}
};

class JokerTile : public Tile
{
public:

	JokerTile(int no) : Tile("joker", no)
	{
		finalpoints = 50;
	}

	void displayInfo() const override
	{
		cout << type;
		Tile::displayInfo();
		cout << " | ";
		//cout << endl;
	}
};


vector<Tile*> Tile::CreateTiles()
{
	vector<Tile*> tiles;
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new JokerTile(2));

	for (int i = 1; i <= nono; i++)
	{
		for (int j = 1; j <= tilesno; j++)
		{
			tiles.push_back(new NormalTile("blue", j, i));
			tiles.push_back(new NormalTile("red", j, i));
			tiles.push_back(new NormalTile("yellow", j, i));
			tiles.push_back(new NormalTile("black", j, i));
		}
	}
	return tiles;
}


class Board
{
public:
	vector <Tile*> board_tiles;
	int tilesnoboard;

	Board()
	{
		tilesnoboard = 0;
	}

	void addtoBoard(vector <Tile*> tstack)
	{
		tilesnoboard += int(tstack.size());
		for (int i = 0; i < tstack.size(); i++)
		{
			board_tiles.push_back(tstack[i]);
		}
	}

	void displayBoardinfo()
	{
		cout << tilesnoboard << endl;
		for (const auto& tile : board_tiles)
		{
			tile->displayInfo();
		}
	}
};

class Player
{
public:
	static int number_of_players;
	Board* playerboard;
	int points;
	int playerno;

	Player()
	{
		playerboard = new Board();
		number_of_players++;
		playerno = number_of_players;
		points = 0;
	}

	void displayPlayerinfo() const
	{
		cout << "PLAYER " << playerno << endl;
		// cout << "Points: " << points << endl;
		playerboard->displayBoardinfo();
		cout << endl;
	}

	static void DisplayPlayers(vector <Player*>& players)
	{
		for (int i = 0; i < Player::number_of_players; i++)
		{
			players[i]->displayPlayerinfo();
		}
	}

	static vector <Player*> InitialisePlayers()
	{
		int n;
		vector <Player*> players;
		while (true)
		{
			cout << "Enter number of players: ";
			cin >> n;
			if (n >= 1 && n <= 4)
			{
				break;
			}
			cout << "Invalid input, please try again" << endl;
		}
		for (int i = 1; i <= n; i++)
		{
			players.push_back(new Player());
		}
		return players;
	}

	static void DivideStacks(vector <vector<Tile*>>& stacks, vector <Tile*>& alltiles, vector <Player*>& players)
	{
		//stacks[stacks.size()-1][0] -> Atu

		cout << "ATU: ";
		stacks[stacks.size() - 1][0]->displayInfo(); cout << endl;

		int pos = 1;
		if (stacks[stacks.size() - 1][0]->type == "normal")
		{
			pos = stacks[stacks.size() - 1][0]->getnumber();
			//cout << pos << endl;
			/*cout << "REPLACED: " << endl;
			stacks[pos - 1][stacks[pos - 1].size() - 1]->displayInfo();*/
		}

		stacks[pos].push_back(stacks[pos - 1][stacks[pos - 1].size() - 1]);      // last tile moved to the next stack
		stacks[pos - 1][stacks[0].size() - 1] = stacks[stacks.size() - 1][0];  // atu to the new stack
		stacks.pop_back();

		Tile::DisplayStacks(stacks);
		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < Player::number_of_players; i++)
			{
				if (pos == stacks.size())
				{
					pos = 0;
				}
				players[i]->playerboard->addtoBoard(stacks[pos]);
				stacks.erase(stacks.begin() + pos);
			}
		}
		Player::DisplayPlayers(players);

		cout << endl << "Stacks: " << endl;
		Tile::DisplayStacks(stacks);
		cout << pos << endl;
		// Creating queue:
		vector <vector<Tile*>> queue;

		//while(stacks.size() != 0)
		//{
		//	if (stacks.size() == 0)
		//	{
		//		break;
		//	}
		//	if (pos == stacks.size())
		//	{
		//		pos = 0;
		//	}
		//	queue.push_back(stacks[pos]);
		//	stacks.erase(stacks.begin() + pos);
		//}
		////Tile::DisplayStacks(stacks);
		//Tile::DisplayStacks(queue);
	}
};


int Player::number_of_players = 0;

#endif
