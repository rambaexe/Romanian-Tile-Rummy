#ifndef classes
#define classes

#include <iostream>
#include <string.h>
#include <algorithm> 
#include <ctime>   
#include <random>
#include <map>

#include "console_h.h"

using namespace std;

const int stacksno = 15;
const int tilesinstackno = 7;

const int tilesno = 13;
const int nono = 2;

const int tilesingameno = 106;

const int maxtilesonboard = 15;

const int min_no_points_first_meld = 45;


class Tile
{
public:
	string type;
	int downpoints;
	int finalpoints;
	int no;				
	bool atu;
	bool move;

	Tile(string type, int no) : type(type), no(no)
	{
		downpoints = 0;
		finalpoints = 0;
		atu = false;
		move = true;
	} 

	void virtual displayInfo() const
	{
		/*cout << "Type: " << type << endl;
		cout << "No: " << no << endl;
		cout << "Down Points: " << downpoints << endl;
		cout << "Final Points: " << finalpoints << endl;*/
	}

	static vector<Tile*> CreateTiles();

	void ResetTile()
	{
		downpoints = 0;
		finalpoints = 0;
		atu = false;
		move = true;
	}

	static void SetMoveFalse(vector <Tile*>& tilesgiven)
	{
		for (const auto& tile : tilesgiven)
		{
			if(tile->type != "joker")
				tile->move = false;
		}
	}

	static void DisplayAtu(vector <Tile*>& alltiles)
	{
		for (const auto& tile : alltiles)
		{
			if (tile->atu == true)
			{
				cout << "ATU: ";
				tile->displayInfo();
				cout << endl;
			}
		}
	}

	static void DisplayMoveFalse(vector <Tile*> tiles)
	{
		cout << "Move False: "<<endl;
		for (const auto& tile : tiles)
		{
			if (tile->move == false)
			{
				tile->displayInfo();
			}
		}
		cout << endl;
	}

	static void DisplayTiles(vector <Tile*>& tiles)
	{
		for (const auto& tile : tiles)
		{
			tile->displayInfo();
		}
		cout << endl;
	}

	static void DisplayStacks(vector <vector<Tile*>> stacks)
	{
		for (auto& stack : stacks)
		{
			Tile::DisplayTiles(stack);
			//cout << endl;
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
	
	string virtual getcolour() 
	{
		return "";
	}

	void virtual addJokerreplacingTile(Tile* tiletoadd){}

	vector<string> virtual getcolourvector() 
	{ 
		vector<string> empty;
		return empty; 
	}

	void virtual deleteJokerreplacing() {}
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
		cout << " ";
		//cout << endl;
	}

	int getnumber() override
	{
		return number;
	}

	string getcolour() override
	{
		return colour;
	}
};

class JokerTile : public Tile
{
public:
	vector<Tile*> replacingtiles;
	bool replacable;

	JokerTile(int no) : Tile("joker", no)
	{
		finalpoints = 50;
		replacable = true;
	}

	void displayInfo() const override
	{
		cout << type;
		Tile::displayInfo();
		if (replacingtiles.size() != 0)
		{
			cout << "=";
			for (const auto& tile : replacingtiles)
			{
				tile->displayInfo();
			}
		}
		cout << " ";
		//cout << endl;
	}

	int getnumber() override
	{
		if (replacingtiles.size() == 0)
		{
			return 0;
		}
		else
		{
			return replacingtiles[0]->getnumber();
		}
	}

	string getcolour() override
	{
		if (replacingtiles.size() == 0)
		{
			return "";
		}
		else if (replacingtiles.size() == 1)
		{
			return replacingtiles[0]->getcolour();
		}
		return replacingtiles[0]->getcolour();
	}

	void addJokerreplacingTile(Tile* tiletoadd) override
	{
		bool ok = true;
		for (const auto& tile : replacingtiles)
		{
			if (tile->type == tiletoadd->type && tile->getcolour() == tiletoadd->getcolour() && tile->getnumber() == tiletoadd->getnumber())
			{
				ok = false;
			}
		}
		if (ok)
		{
			replacingtiles.push_back(tiletoadd);
		}
	}

	void deleteJokerreplacing() override
	{
		replacingtiles.clear();
	}

	vector<string> getcolourvector() override
	{
		vector<string> col;
		if (replacingtiles.size() > 0)
		{
			for (const auto& tile : replacingtiles)
			{
				col.push_back(tile->getcolour());
			}
		}
		return col;
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

	/*void Reset_Board()
	{
		board_tiles.clear();
		tilesnoboard = 0;
	}*/

	void displayBoardinfo()
	{
		cout << tilesnoboard << endl;
		for (const auto& tile : board_tiles)
		{
			tile->displayInfo();
		}
	}
};

class Formation
{
public:
	bool melded;
	bool valid;
	bool jokerinformation;
	string type;
	vector <Tile*> formationtiles;				
	int points;
	//Player* fplayer;
	static int formationno;
	int formationid;

	Formation(vector<Tile*> tilesforformation, string formationtype)
	{
		formationno++; formationid = formationno;
		melded = false;
		jokerinformation = false;
		valid = true;								// assume formation is valid
		//fplayer = NULL;

		//adding tiles to formation
		for (const auto& tile : tilesforformation)
		{
			formationtiles.push_back(tile);
			// check joker tile
			if (tile->type == "joker")
			{
				jokerinformation = true;
			}
		}

		// check one joker only
		if (jokerinformation)
		{
			int ct = 0;
			for (const auto& tile : tilesforformation)
			{
				if (tile->type == "joker")
				{
					ct++;
				}
			}
			if (ct != 1)
			{
				valid = false;
			}
		}

		// determine formation type
		type = formationtype;
		
		// handle joker
		handlejokerinformation(tilesforformation);

		// check if formation is valid 
		if (valid)
		{
			valid = checkFormationvalid(formationtiles);
		}

		// set downpoints
		if (valid)
		{
			setdownpointsFormation();
		}
	}

	Formation(vector<Tile*> tilesforformation)
	{
		formationno++; formationid = formationno;
		melded = false;
		jokerinformation = false;
		valid = true;								// assume formation is valid
		//fplayer = NULL;

		//adding tiles to formation
		for (const auto& tile : tilesforformation)
		{
			formationtiles.push_back(tile);
			// check joker tile
			if (tile->type == "joker")
			{
				jokerinformation = true;
			}
		}

		// check one joker only
		if (jokerinformation)
		{
			int ct = 0;
			for (const auto& tile : tilesforformation)
			{
				if (tile->type == "joker")
				{
					ct++;
				}
			}
			if (ct != 1)
			{
				valid = false;
			}
		}

		// determine formation type
		if (valid)
		{
			vector<Tile*> tilescopy (tilesforformation);
			bool isrun = checkRun(tilescopy);
			for (const auto& tile : tilesforformation)
			{
				if (tile->type == "joker")
				{
					tile->deleteJokerreplacing();
				}
			}
			bool isset = checkSet(tilescopy);
			for (const auto& tile : tilesforformation)
			{
				if (tile->type == "joker")
				{
					tile->deleteJokerreplacing();
				}
			}
			if (isrun && !isset)
			{
				type = "run";
			}
			else if (isset && !isrun)
			{
				type = "set";
			}
			else
			{
				type = "";
				valid = false;
			}
		}
		for (const auto& tile : tilesforformation)
		{
			if (tile->type == "joker")
			{
				tile->deleteJokerreplacing();
			}
		}
		// type = formationtype;

		// handle joker
		handlejokerinformation(tilesforformation);

		// check if formation is valid 
		if (valid)
		{
			valid = checkFormationvalid(formationtiles);
		}

		// set downpoints
		if (valid)
		{
			setdownpointsFormation();
		}
	}

	bool checkRun(vector<Tile*>& tilestocheck)
	{
		if (jokerinformation)
		{
			handlejokerinrun(tilestocheck);
		}

		//	check tiles to be between 1 and 13
		for (const auto& tile : tilestocheck)
		{
			if (tile->getnumber() < 1 || tile->getnumber() > 13)
			{
				return false;
			}
		}

		// check colour to be the same
		string auxcolour = tilestocheck[0]->getcolour();
		for (const auto& tile : tilestocheck)
		{
			if (tile->getcolour() != auxcolour)
			{
				return false;
			}
		}

		//first tile not allowed to be 13 => check one not in the middle
		if (tilestocheck[0]->getnumber() == 13)
		{
			return false;
		}

		//no replaced tile allowed to be 0
		for (int i = 0; i < tilestocheck.size(); i++)
		{
			if (tilestocheck[i]->getnumber() == 0)
			{
				return false;
			}
		}

		//check consecutive
		for (int i = 1; i < tilestocheck.size(); i++)
		{
			if (tilestocheck[i]->getnumber() - 1 != tilestocheck[i - 1]->getnumber())
			{
				// check for ... - 13 - 1
				if (i == tilestocheck.size() - 1 && tilestocheck[i]->getnumber() == 1 && tilestocheck[i - 1]->getnumber() == 13)
				{
					continue;
				}
				return false;
			}

		}
		return true;
	}

	bool checkSet(vector<Tile*>& tilestocheck)
	{
		if (jokerinformation)
		{
			handlejokerinset(tilestocheck);
		}
		// min 3 max 4
		if (tilestocheck.size() < 3 || tilestocheck.size() > 4)
		{
			return false;
		}

		// same number
		int firstno = tilestocheck[0]->getnumber();
		for (const auto& tile : tilestocheck)
		{
			if (tile->getnumber() != firstno)
			{
				return false;
			}
		}

		// check colours
		map<string, bool> colours = { {"black", false}, {"yellow", false}, {"red", false}, {"blue", false} };
		for (const auto& tile : tilestocheck)
		{
			if (tile->type == "joker")
			{
				vector<string> coljok = tile->getcolourvector();
				for (const auto& colj : coljok)
				{
					for (auto& col : colours)
					{
						if (col.first == colj)
						{
							if (col.second == false)
							{
								col.second = true;
							}
							else
							{
								return false;
							}
						}
					}
				}
			}
			else
			{
				string currentcol = tile->getcolour();
				for (auto& col : colours)
				{
					if (col.first == currentcol)
					{
						if (col.second == false)
						{
							col.second = true;
						}
						else
						{
							return false;
						}
					}
				}
			}
		}
		return true;
	}

	void handlejokerinset(vector<Tile*>& tilesforset)
	{
		vector<string> colours;
		colours.push_back("black");
		colours.push_back("red");
		colours.push_back("yellow");
		colours.push_back("blue");

		int currentnumber = 0;

		for (const auto& tile : tilesforset)
		{
			if (tile->type != "joker")
			{
				if (currentnumber == 0)
				{
					currentnumber = tile->getnumber();
				}
				string currentcolour = tile->getcolour();
				for (int i = 0; i < colours.size(); i++)
				{
					if (currentcolour == colours[i])
					{
						colours.erase(colours.begin() + i);
						break;
					}
				}
			}
		}
		for (const auto& tile : tilesforset)
		{
			if (tile->type == "joker")
			{
				for (const auto& colour : colours)
				{
					tile->addJokerreplacingTile(new NormalTile(colour, currentnumber, 0));
				}
			}
		}
	}

	void handlejokerinrun(vector<Tile*>& tilesforrun)
	{
		int jokerpos = 0;
		for (int i = 0; i < tilesforrun.size(); i++)
		{
			if (tilesforrun[i]->type == "joker")
			{
				jokerpos = i;
				break;
			}
		}
		if (jokerpos == 0) // beginning
		{
			string col = tilesforrun[1]->getcolour();
			int num = tilesforrun[1]->getnumber();
			tilesforrun[jokerpos]->addJokerreplacingTile(new NormalTile(col, num - 1, 0));
		}
		else if (jokerpos == tilesforrun.size() - 1) // end
		{
			string col = tilesforrun[tilesforrun.size() - 2]->getcolour();
			int num = tilesforrun[tilesforrun.size() - 2]->getnumber();
			if (tilesforrun[tilesforrun.size() - 2]->getnumber() == 13)
			{
				tilesforrun[jokerpos]->addJokerreplacingTile(new NormalTile(col, 1, 0));
			}
			else
			{
				tilesforrun[jokerpos]->addJokerreplacingTile(new NormalTile(col, num + 1, 0));
			}
		}
		else // middle
		{
			string col = tilesforrun[jokerpos - 1]->getcolour();
			int num = tilesforrun[jokerpos - 1]->getnumber();
			tilesforrun[jokerpos]->addJokerreplacingTile(new NormalTile(col, num + 1, 0));
		}
	}

	void handlejokerinformation(vector<Tile*>& tilesforformation)
	{
		// handle joker
		if (jokerinformation && valid)
		{
			if (type == "run")
			{
				// 12 - j - 1
				// j - 13 - 1
				// 12 - 13 - j
				// j - 2 - 3
				// 1 - 2 - j
				// 1 - j - 3
				int jokerpos = 0;
				for (int i = 0; i < tilesforformation.size(); i++)
				{
					if (tilesforformation[i]->type == "joker")
					{
						jokerpos = i;
						break;
					}
				}
				if (jokerpos == 0) // beginning
				{
					string col = tilesforformation[1]->getcolour();
					int num = tilesforformation[1]->getnumber();
					tilesforformation[jokerpos]->addJokerreplacingTile(new NormalTile(col, num - 1, 0));
				}
				else if (jokerpos == tilesforformation.size() - 1) // end
				{
					string col = tilesforformation[tilesforformation.size() - 2]->getcolour();
					int num = tilesforformation[tilesforformation.size() - 2]->getnumber();
					if (tilesforformation[tilesforformation.size() - 2]->getnumber() == 13)
					{
						tilesforformation[jokerpos]->addJokerreplacingTile(new NormalTile(col, 1, 0));
					}
					else
					{
						tilesforformation[jokerpos]->addJokerreplacingTile(new NormalTile(col, num + 1, 0));
					}
				}
				else // middle
				{
					string col = tilesforformation[jokerpos - 1]->getcolour();
					int num = tilesforformation[jokerpos - 1]->getnumber();
					tilesforformation[jokerpos]->addJokerreplacingTile(new NormalTile(col, num + 1, 0));
				}
			}
			else if (type == "set")
			{
				vector<string> colours;
				colours.push_back("black");
				colours.push_back("red");
				colours.push_back("yellow");
				colours.push_back("blue");

				int currentnumber = 0;

				for (const auto& tile : tilesforformation)
				{
					if (tile->type != "joker")
					{
						if (currentnumber == 0)
						{
							currentnumber = tile->getnumber();
						}
						string currentcolour = tile->getcolour();
						for (int i = 0; i < colours.size(); i++)
						{
							if (currentcolour == colours[i])
							{
								colours.erase(colours.begin() + i);
								break;
							}
						}
					}
				}
				for (const auto& tile : tilesforformation)
				{
					if (tile->type == "joker")
					{
						for (const auto& colour : colours)
						{
							tile->addJokerreplacingTile(new NormalTile(colour, currentnumber, 0));
						}
					}
				}
			}

		}
	}

	void displayFormationinfo()
	{
		int sum = 0;
		for (const auto& tile : formationtiles)
		{
			tile->displayInfo();
			if (valid)
			{
				cout << "(P:" << tile->downpoints << ") ";
				sum += tile->downpoints;
			}	
		}
		cout << endl;
		cout << "Type: "<< type << "\nPoints: "<< sum <<"\nValid: " << valid << "\nId: " << formationid << "\nMelded: " << melded << "\n";
	}
	
	void setdownpointsFormation()
	{
		for (const auto& tile : formationtiles)
		{
			if (tile->getnumber() == 1)
			{
				if (type == "set")
				{
					tile->downpoints = 25;
				}
				else if (type == "run")
				{
					// 1 - 2 - 3 - ...
					if (formationtiles[1]->getnumber() == 2)
					{
						tile->downpoints = 5;
					}
					// ... - 12 - 13 - 1 
					if (formationtiles[formationtiles.size() - 2]->getnumber() == 13)
					{
						tile->downpoints = 10;
					}
				}
			}
			else if (tile->getnumber() >= 2 && tile->getnumber() <= 9)
			{
				tile->downpoints = 5;
			}
			else if (tile->getnumber() >= 10 && tile->getnumber() <= 13)
			{
				tile->downpoints = 10;
			}
		}
	}

	// check if formation is valid
	bool checkFormationvalid(vector <Tile*> tilesfor)
	{
		handlejokerinformation(tilesfor);

		if (tilesfor.size() < 3 && tilesfor.size() > 13)
		{
			return false;
		}
		
		// check run formations
		if (type == "run")
		{
			//	check tiles to be between 1 and 13
			for (const auto& tile : tilesfor)
			{
				if (tile->getnumber() < 1 || tile->getnumber() > 13)
				{
					return false;
				}
			}

			// check colour to be the same
			string auxcolour = tilesfor[0]->getcolour();
			for (const auto& tile : tilesfor)
			{
				if (tile->getcolour() != auxcolour)
				{
					return false;
				}
			}

			//first tile not allowed to be 13 => check one not in the middle
			if (tilesfor[0]->getnumber() == 13)
			{
				return false; 
			}

			//no replaced tile allowed to be 0
			for (int i = 0; i < tilesfor.size(); i++)
			{
				if (tilesfor[i]->getnumber() == 0)
				{
					return false;
				}
			}

			//check consecutive
			for (int i = 1; i< tilesfor.size(); i++)
			{
				if (tilesfor[i]->getnumber() - 1 != tilesfor[i - 1]->getnumber())
				{
					// check for ... - 13 - 1
					if (i == tilesfor.size() - 1 && tilesfor[i]->getnumber() == 1 && tilesfor[i - 1]->getnumber() == 13)
					{
						continue;
					}
					return false;
				}

			}
			setdownpointsFormation();
			return true;
		}
		else if (type == "set")
		{
			// min 3 max 4
			if (tilesfor.size() < 3 || tilesfor.size() > 4)
			{
				return false;
			}

			// same number
			int firstno = tilesfor[0]->getnumber();
			for (const auto& tile : tilesfor)
			{
				if (tile->getnumber() != firstno)
				{
					return false;
				}
			}

			// check colours
			map<string, bool> colours = { {"black", false}, {"yellow", false}, {"red", false}, {"blue", false} };
			for (const auto& tile : tilesfor)
			{
				if (tile->type == "joker")
				{
					vector<string> coljok = tile->getcolourvector();
					for (const auto& colj : coljok)
					{
						for (auto& col : colours)
						{
							if (col.first == colj)
							{
								if (col.second == false)
								{
									col.second = true;
								}
								else
								{
									return false;
								}
							}
						}
					}
				}
				else
				{
					string currentcol = tile->getcolour();
					for (auto& col : colours)
					{
						if (col.first == currentcol)
						{
							if (col.second == false)
							{
								col.second = true;
							}
							else
							{
								return false;
							}
						}
					}
				}
			}
			setdownpointsFormation();
			return true;
		}
		return false;
	}

	// not done
	void addTiletoFormation(vector <Tile*> tilestoadd)
	{
		vector <Tile*> copy = formationtiles;
		if (valid)
		{
			if (type == "run")
			{

			}
			else if (type == "set")
			{
				for (const auto& tile : tilestoadd)
				{
					copy.push_back(tile);
				}
				cout << "before";
				Tile::DisplayTiles(formationtiles);
				if (checkSet(copy))
				{
					for (const auto& tile : tilestoadd)
					{
						formationtiles.push_back(tile);
						handlejokerinformation(formationtiles);
					}
				}
				displayFormationinfo();
			}
		}
	}


};

int Formation::formationno = 0;

class Player
{
public:
	static int number_of_players;
	Board* playerboard;
	int match_points;
	int total_points;
	int playerno;
	bool firstmeld;
	vector<Formation*> formations;

	Player()
	{
		playerboard = new Board();
		number_of_players++;
		playerno = number_of_players;
		match_points = 0;
		total_points = 0;
		firstmeld = false;
	}

	void displayPlayerinfo() const
	{
		cout << "PLAYER " << playerno;
		cout << "     (Points: " << match_points << ")" << endl;
		playerboard->displayBoardinfo();
		cout << endl;
	}

	void displayPlayername() const
	{
		cout << "PLAYER " << playerno << endl;
	}

	void ResetPlayer()
	{
		playerboard = new Board();
		match_points = 0;
		firstmeld = false;
	}

	static void DisplayPlayers(vector <Player*>& players)
	{
		for (int i = 0; i < Player::number_of_players; i++)
		{
			cout << endl;
			players[i]->displayPlayerinfo();
		}
	}

	static vector <Player*> InitialisePlayers()
	{
		int n;
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
		vector <Player*> players = InitialiseNPlayers(n);
		return players;
	}

	static vector <Player*> InitialiseNPlayers(int n)
	{
		vector <Player*> players;
		for (int i = 1; i <= n; i++)
		{
			players.push_back(new Player());
		}
		return players;
	}

	static Player* get_Player(int no, vector<Player*> players)
	{
		for (const auto& player : players)
		{
			if (no == player->playerno)
			{
				return player;
			}
		}

	}

	int getPlayerNumber()
	{
		int pnumber = 0;
		string numberstring;
		cout << "Number: ";
		
		cin >> numberstring;

		try
		{
			pnumber = stoi(numberstring);
		}
		catch (exception& err)
		{
			cout << "Error occured. You must insert a number."<<endl;
		}
		
		return pnumber;
	}

	string getPlayerColour()
	{
		string pcolour;
		cout << "Colour: ";
		cin >> pcolour;
		return pcolour;
	}

	int getPlayerOption1()
	{
		int pnumber = 0;
		string numberstring;
		cout << "Choose from taking a tile from the stacks (1) or taking a tile from the queue (2): ";

		cin >> numberstring;

		try
		{
			pnumber = stoi(numberstring);
		}
		catch (exception& err)
		{
			cout << "Error occured. You must insert a number." << endl;
		}

		return pnumber;
	}

	tuple<string, int, string> getPlayerInputTile()			// type, number, colour
	{
		// get Type:
		string stringp;
		cout << "Insert Tile Details:\n";
		cout << "Type [n - normal; j - joker, e - exit]: ";
		cin >> stringp;

		if (stringp == "e")
		{
			return make_tuple("exit", 0, "exit");
		}
		if (stringp == "j")
		{
			return make_tuple("joker", 0, "");
		}
		else if (stringp == "n")
		{
			int pnumber = getPlayerNumber();
			string pcolour = getPlayerColour();

			return make_tuple("normal", pnumber, pcolour);
		}
		
		return make_tuple("notvalid", 0, "notvalid");
	}

	static void removeTilefromBoard(string currenttype, int currentnumber, string currentcolour, Player*& player)
	{
		int i = 0;
		for (int i = 0; i < player->playerboard->board_tiles.size(); i++)
		{
			if ((currenttype == "joker" && currenttype == player->playerboard->board_tiles[i]->type) ||
				(player->playerboard->board_tiles[i]->getnumber() == currentnumber
				&& player->playerboard->board_tiles[i]->getcolour() == currentcolour))
			{
				player->playerboard->board_tiles.erase(player->playerboard->board_tiles.begin() + i);
				player->playerboard->tilesnoboard--;
				break;
			}
		}
	}

	void removetileboard(Tile* tiletoremove)
	{
		for (int i = 0; i < playerboard->board_tiles.size(); i++)
		{
			if ((tiletoremove->type == "joker" && tiletoremove->type == playerboard->board_tiles[i]->type) ||
				(playerboard->board_tiles[i]->getnumber() == tiletoremove->getnumber()
					&& playerboard->board_tiles[i]->getcolour() == tiletoremove->getcolour()))
			{
				playerboard->board_tiles.erase(playerboard->board_tiles.begin() + i);
				playerboard->tilesnoboard--;
				break;
			}
		}
	}
	static bool checkfirstmeld(vector <Formation*> formations)
	{
		bool run = false; bool set = false; int points = 0;
		// check formations
		for (const auto& f : formations)
		{
			if (f->valid == false)
			{
				return false;
			}
			if (f->type == "run")
			{
				run = true;
			}
			else if (f->type == "set")
			{
				set = true;
			}
			for (const auto& tile : f->formationtiles)
			{
				points += tile->downpoints;
			}
		}
		if (run && set && points >= min_no_points_first_meld)
		{
			return true;
		}
		return false;
	}

	bool checkTilesonBoard(vector<Tile*> tiles)
	{
		for (const auto& t: tiles)
		{
			bool ok = false;
			for (const auto& tile : playerboard->board_tiles)
			{
				if (t->type == tile->type && t->getcolour() == tile->getcolour() && t->getnumber() == tile->getnumber())
				{
					ok = true;
				}
			}
			if (!ok)
			{
				return false;
			}
		}
		return true;
	}

	void FirstMeld(vector<Formation*> formationstomeld)
	{
		if (!firstmeld)
		{
			if(checkfirstmeld(formationstomeld))
			{
				// check if tiles are on board (or if broken from queue)
				bool cont = true;
				for (const auto& form : formationstomeld)
				{
					if (checkTilesonBoard(form->formationtiles) == false)
					{
						cont = false;
					}
				}
				if (cont)
				{
					firstmeld = true;
					// add final points to player and remove tiles from board
					for (const auto& f : formationstomeld)
					{
						// change move of tiles besides joker
						for (const auto& tile : f->formationtiles)
						{
							tile->move = false;
						}
						// add formation to player
						formations.push_back(f);
						formations[formations.size() - 1]->melded = true;
						for (const auto& tile : f->formationtiles)
						{
							match_points += tile->finalpoints;
							removetileboard(tile);
						}
					}
				}
			}
		}
	}

	void FirstMeldwithBreak(vector<Formation*> formationstomeld, Tile* tilefromqueue, vector<Tile*>& givenqueue)
	{
		if (!firstmeld)
		{
			if (checkfirstmeld(formationstomeld))
			{
				vector<vector<Tile*>> tilestocheckonboard;

				// check if broken from queue correct
				if (tilefromqueue->move == true &&
					tilefromqueue->type == givenqueue[givenqueue.size() - 1]->type &&
					tilefromqueue->getcolour() == givenqueue[givenqueue.size() - 1]->getcolour() &&
					tilefromqueue->getnumber() == givenqueue[givenqueue.size() - 1]->getnumber()
					)
				{
					for (const auto& form : formationstomeld)
					{
						vector<Tile*> tilesin;
						for (const auto& tile : form->formationtiles)
						{
							tilesin.push_back(tile);
						}
						for (int i=0; i<tilesin.size(); i++)
						{
							if (tilefromqueue->type == tilesin[i]->type &&
								tilefromqueue->getcolour() == tilesin[i]->getcolour() &&
								tilefromqueue->getnumber() == tilesin[i]->getnumber())
							{
								tilesin.erase(tilesin.begin() + i);
								break;
							}
						}
						tilestocheckonboard.push_back(tilesin);
					}
				}

				bool cont2 = true;
				for (const auto& t : tilestocheckonboard)
				{
					if (checkTilesonBoard(t) == false)
					{
						cont2 = false;
					}
				}
				if (cont2)
				{
					firstmeld = true;

					// remove last from queue
					givenqueue.pop_back();

					// add final points to player and remove tiles from board
					for (const auto& f : formationstomeld)
					{
						// change move of tiles besides joker
						for (const auto& tile : f->formationtiles)
						{
							tile->move = false;
						}
						// add formation to player
						formations.push_back(f);
						for (const auto& tile : f->formationtiles)
						{
							match_points += tile->finalpoints;

							removetileboard(tile);
						}
					}
				}
			}
		}
	}
};

int Player::number_of_players = 0;

class Game
{
public:
	int matchmultiplier;
	int roundpointer;
	int matchpointer;

	Game()
	{
		roundpointer = 0;
		matchpointer = 0;
		matchmultiplier = 1;
	}
	static bool checkfirstmeld(vector <Formation*> formations)
	{
		bool run = false; bool set = false; int points = 0;
		// check formations
		for (const auto& f : formations)
		{
			if (f->valid == false)
			{
				return false;
			}
			if (f->type == "run")
			{
				run = true;
			}
			else if (f->type == "set")
			{
				set = true;
			}
			for (const auto& tile : f->formationtiles)
			{
				points += tile->downpoints;
			}
		}
		if (run && set && points >= min_no_points_first_meld)
		{
			return true;
		}
		return false;
	}

	vector <Tile*> DivideStacks(vector <vector<Tile*>> stacks, vector <Tile*>& alltiles, vector <Player*>& players)
	{
		//stacks[stacks.size()-1][0] -> Atu

		cout << "ATU: ";
		stacks[stacks.size() - 1][0]->displayInfo(); cout << endl;
		stacks[stacks.size() - 1][0]->move = false;							//do not allow atu to be moved

		int pos = 1;
		if (stacks[stacks.size() - 1][0]->type == "normal")
		{
			pos = stacks[stacks.size() - 1][0]->getnumber();
		}

		stacks[pos].push_back(stacks[pos - 1][stacks[pos - 1].size() - 1]);      // last tile moved to the next stack
		stacks[pos - 1][stacks[0].size() - 1] = stacks[stacks.size() - 1][0];  // atu to the new stack
		stacks.pop_back();

		Tile::DisplayStacks(stacks);

		// divide stacks to players
		if (matchpointer == Player::number_of_players)
		{
			matchpointer = 1;
		}
		else 
		{
			matchpointer++;
		}
		int auxmatchpointer = matchpointer-1;
		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < Player::number_of_players; i++)
			{
				if (pos == stacks.size())
				{
					pos = 0;
				}
				Tile::SetMoveFalse(stacks[pos]);
				players[auxmatchpointer]->playerboard->addtoBoard(stacks[pos]);
				stacks.erase(stacks.begin() + pos);

				if (auxmatchpointer == Player::number_of_players - 1)
				{
					auxmatchpointer = 0;
				}
				else
				{
					auxmatchpointer++;
				}
			}
		}
		cout << endl << endl;
		Player::DisplayPlayers(players); cout << endl;

		// Creating queue:
		vector <Tile*> queue;

		while (stacks.size() != 0)
		{
			if (pos == stacks.size())
			{
				pos = 0;
			}
			if (stacks.size() == 1)        // last stack with atu
			{
				for (int j = stacks[pos].size() - 2; j >= 0; j--)
				{
					queue.push_back(stacks[pos][j]);
				}
				queue.push_back(stacks[pos][stacks[pos].size() - 1]);
			}
			else
			{
				for (int j = stacks[pos].size() - 1; j >= 0; j--)
				{
					queue.push_back(stacks[pos][j]);
				}
			}
			stacks.erase(stacks.begin() + pos);
		}

		return queue;
	}

	static void Reset_Match(vector <Tile*>& alltiles, vector <Player*>& players)
	{
		for (const auto& tile : alltiles)
		{
			tile->ResetTile();
		}
		for (const auto& player : players)
		{
			player->ResetPlayer();
		}
	}
	
	static Tile* CheckTile(string ptype, int pnumber, string pcolour, vector<Tile*> playertiles)
	{
		for (const auto& tile : playertiles)
		{
			if (ptype == "joker")
			{
				if (tile->type == ptype)
				{
					return tile;
				}
			}
			else
			{
				if (tile->type == ptype && tile->getnumber() == pnumber && tile->getcolour() == pcolour)
				{
					return tile;
				}
			}
		}
		Tile* notonboardtile = new Tile("notvalid", 0);
		return notonboardtile;
	}

	void displayPlayerInformationinRound(vector <Player*>& players, vector <Tile*>& stackqueue, vector <Tile*>& queue)
	{
		cout << "Queue:" << endl;  Tile::DisplayTiles(queue); cout << endl;
		cout << "Stacks Queue:" << endl; Tile::DisplayTiles(stackqueue); cout << endl;
		cout << endl;

		if (players[roundpointer]->firstmeld == true)
		{
			cout << "Melded Formations:\n";
			for (const auto& f : players[roundpointer]->formations)
			{
				f->displayFormationinfo(); cout << endl;
			}
			cout << endl;
		}

		players[roundpointer]->displayPlayerinfo(); cout << endl;
	}

	void DisplayOnTopScreen(vector <Player*>& players, vector <Tile*>& stackqueue, vector <Tile*>& queue, int ct)
	{
		Console::clean_screen();
		Player::DisplayPlayers(players);
		cout << "\n\nROUND " << (ct-1)/Player::number_of_players + 1<< endl;
		cout << "-------------------------------------------------------------- " << endl;
		Game::displayPlayerInformationinRound(players, stackqueue, queue);
	}

	void FirstMeldGame(vector <Player*>& players, vector <Tile*>& stackqueue, vector <Tile*>& queue, int& ct)
	{
		string currenttype, currentcolour;
		int currentnumber;
		Tile* currentTile = new Tile("", 0);

		if (ct > players[roundpointer]->number_of_players)		// not allowed to first meld first round
		{
			if (players[roundpointer]->firstmeld == false)
			{
				cout << "Do you want to perform your first meld? (y/n): ";
				string ans;
				cin >> ans;
				if (ans == "y")
				{
					Console::clean_screen();
					Player::DisplayPlayers(players); cout << endl;
					cout << "\n\n -------------------------------------------------------------- " << endl;
					cout << "PERFORMING FIRST MELD" << endl << endl;

					Game::DisplayOnTopScreen(players, stackqueue, queue, ct);

					// first meld loop
					while (true)
					{
						bool exit = false;
						// create copy of player's tiles
						vector<Tile*> tilesonboard;
						for (const auto& tile : players[roundpointer]->playerboard->board_tiles)
						{
							tilesonboard.push_back(tile);
						}

						Game::DisplayOnTopScreen(players, stackqueue, queue, ct);

						vector<Formation*> formationsinput;
						int formationcounter = 1;

						// get formations from user
						while (true)
						{
							if (exit)
							{
								break;
							}
							Game::DisplayOnTopScreen(players, stackqueue, queue, ct);
							if (formationsinput.size() != 0)
							{
								cout << "\n Current Formations:\n";
								for (const auto& f : formationsinput)
								{
									f->displayFormationinfo();
								}
								cout << endl;
							}
							cout << "\nFormation " << formationcounter << endl;

							int tilescounter = 0;
							vector<Tile*> tilesforformation;

							// get player tile
							while (true)
							{
								if (exit)
								{
									break;
								}
								Game::DisplayOnTopScreen(players, stackqueue, queue, ct);
								if (formationsinput.size() != 0)
								{
									cout << "\nCurrent Formations:\n";
									for (const auto& f : formationsinput)
									{
										f->displayFormationinfo();
									}
									cout << endl;
								}
								cout << endl;
								if (tilesforformation.size() != 0)
								{
									cout << "\nCurrent Tiles for formation:\n";
									Tile::DisplayTiles(tilesforformation);
								}
								cout << "\nRemaining Tiles:\n";
								Tile::DisplayTiles(tilesonboard); cout << endl;

								cout << "\nFormation " << formationcounter;
								cout << "\nTile " << tilescounter + 1 << endl << endl;
								tie(currenttype, currentnumber, currentcolour) = players[roundpointer]->getPlayerInputTile();
								currentTile = CheckTile(currenttype, currentnumber, currentcolour, tilesonboard);

								if (currenttype == "exit")
								{
									exit = true;
									break;
								}
								else if (currentTile->no == 0 && currentTile->type == "notvalid")
								{
									cout << "Not a valid tile. Try again.\n" << endl;
									Console::pause_console();
								}
								else // VALID TILE
								{
									// delete currentTile from aux player board
									for (int i = 0; i < tilesonboard.size(); i++)
									{
										if (tilesonboard[i]->type == currentTile->type &&
											tilesonboard[i]->getnumber() == currentTile->getnumber() &&
											tilesonboard[i]->getcolour() == currentTile->getcolour())
										{
											tilesonboard.erase(tilesonboard.begin() + i);
											break;
										}
									}

									cout << endl << endl;

									tilesforformation.push_back(currentTile);
									tilescounter++;

									if (tilesforformation.size() != 0)
									{
										cout << "\nInserted Tiles for Formation " << formationcounter << ":\n";
										Tile::DisplayTiles(tilesforformation);

									}

									if (tilescounter >= 3)
									{
										string answ;
										cout << "\nWould you like to insert any other tiles? (y/n): ";
										cin >> answ;
										if (answ == "n")
										{
											break;
										}
									}
									else
									{
										Console::pause_console();
									}
								}
							}
							if (exit)
							{
								break;
							}

							formationsinput.push_back(new Formation(tilesforformation));
							
							cout << "\nInserted Formation:\n";
							formationsinput[formationcounter - 1]->displayFormationinfo(); cout << endl << endl;
							if (formationsinput[formationcounter - 1]->valid == false)
							{
								cout << "Not a valid formation. Please try again.\n\n";
								Console::pause_console();
								formationsinput.pop_back();
								for (const auto& tile : tilesforformation)
								{
									if (CheckTile(tile->type, tile->getnumber(), tile->getcolour(), players[roundpointer]->playerboard->board_tiles))
									{
										tilesonboard.push_back(tile);
									}
								}
								tilesforformation.clear();
							}
							else  // VALID FORMATION
							{
								formationcounter++;
								tilesforformation.clear();
							}

							if (formationcounter > 2)
							{
								string answe;
								cout << "\nWould you like to meld any other formations? (y/n): ";
								cin >> answe;
								if (answe == "n")
								{
									break;
								}
							}
							else
							{
								Console::pause_console();
							}

						}

						// check formations
						players[roundpointer]->FirstMeld(formationsinput);
						if (players[roundpointer]->firstmeld == true)
						{
							cout << "Successfully melded the formations!\n";
							Console::pause_console();
							break;
						}
						else
						{
							cout << "\n\nWould you like to try the first meld again? (y/n): ";
							string answer;
							cin >> answer;
							if (answer == "n")
							{
								break;
							}
						}
					}
				}

			}

		}

	}

	void Match(vector <Player*>& players, vector <Tile*>& stackqueue, vector <Tile*>& alltiles, vector <Tile*>& queue)
	{
		// choose player to start (with 15 tiles):
		for (const auto& player : players)
		{
			if (player->playerboard->tilesnoboard == maxtilesonboard)
			{
				Game::roundpointer = player->playerno - 1;
			}
		}

		Console::pause_console();
		Console::clean_screen();
		
		// START GAME
		//
		//
		string currenttype, currentcolour;
		int currentnumber;
		Tile* currentTile = new Tile("", 0);
			

		int ct = 1; // round counter 
		for (int i = 0; i <= 100; i++)
		{
			Tile* currentTile = new Tile("", 0);
			bool breakfromqueue = false;

			// DRAW TILE OR BREAK FROM QUEUE
			Game::DisplayOnTopScreen(players, stackqueue, queue, ct);

			if (ct != 1) // FIRST ROUND; FIRST PLAYER DOES NOT DRAW TILE
			{
				if (ct <= players[roundpointer]->number_of_players)  // FIRST ROUND; EVERYONE DRAWS BESIDES FIRST PLAYER
				{
					// get tile from stack and add to player
					cout << "First Round: Automatically drawing a tile from the stacks.\n\n";
					cout << "Tile drawn from stack: "; stackqueue[0]->displayInfo();  cout << endl << endl;
					players[roundpointer]->playerboard->board_tiles.push_back(stackqueue[0]);
					players[roundpointer]->playerboard->tilesnoboard++;
					stackqueue.erase(stackqueue.begin());
					Console::pause_console();
				}
				else		// OTHER ROUNDS
				{
					//choice: break / get tile from stacks
					while (true)
					{
						Game::DisplayOnTopScreen(players, stackqueue, queue, ct);
						cout << "\nWould you like to draw a tile from the stack [Option 1] or break the last tile from the queue [Option 2] ? \n[1/2]: ";
						int ans = 0;
						string ansstring;
						cin >> ansstring;
						try
						{
							ans = stoi(ansstring);
						}
						catch (exception& err)
						{
							cout << "\nError occured. You must insert a number." << endl;
							Console::pause_console();
						}
						if (ans != 0)
						{
							if (ans == 1)
							{
								cout << "\nOption 1: Tile drawn from stack: "; stackqueue[0]->displayInfo();  cout << endl << endl;

								players[roundpointer]->playerboard->board_tiles.push_back(stackqueue[0]);
								players[roundpointer]->playerboard->tilesnoboard++;
								stackqueue.erase(stackqueue.begin());
								breakfromqueue = false;
								Console::pause_console();
								break;
							}
							else if (ans == 2)
							{
								cout << "\nOption 2: Tile broken from stack: "; queue[queue.size()-1]->displayInfo();  cout << endl << endl;
								breakfromqueue = true;
								Console::pause_console();
								break;
							}
							else
							{
								continue;
							}
							break;
						}
					}
					
				}
			}

			Game::DisplayOnTopScreen(players, stackqueue, queue, ct);
			
			if (breakfromqueue)
			{

			}
			else // FIRST MELD
			{
				FirstMeldGame(players, stackqueue, queue, ct);
			}

			// PLAYER PUTS TILE IN QUEUE -> END OF ROUND
			// 
			// 
			// get player input for tile to discard
			
			while (true)
			{
				Game::DisplayOnTopScreen(players, stackqueue, queue, ct);
				cout << "\nChoose tile to put in queue." << endl<<endl;

				tie(currenttype, currentnumber, currentcolour) = players[roundpointer]->getPlayerInputTile();
				currentTile = CheckTile(currenttype, currentnumber, currentcolour, players[roundpointer]->playerboard->board_tiles);
				if (currenttype == "exit")
				{
					cout << "Not a valid option. You have to insert a tile.\n" << endl;
					Console::pause_console();

				}
				else if (currentTile->no == 0 && currentTile->type == "notvalid")
				{
					cout << "Not a valid tile. Try again.\n" << endl;
					Console::pause_console();
				}
				else
				{
					break;
				}
			}
			cout << "\nChosen tile: ";  currentTile->displayInfo(); cout << endl<<endl;
			Console::pause_console();
			// remove tile from player and put in queue
			Player::removeTilefromBoard(currenttype, currentnumber, currentcolour, players[roundpointer]);
			queue.push_back(currentTile);
			queue[queue.size() - 1]->move = true;
			

			queue[0]->move = false;			// cannot pick the first tile

			// GO TO NEXT PLAYER
			if (roundpointer == Player::number_of_players - 1)
			{
				roundpointer = 0;
			}
			else
			{
				roundpointer++;
			}
			ct++;
		}
	}
};

#endif
