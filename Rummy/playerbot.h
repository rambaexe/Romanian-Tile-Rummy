#ifndef playerbot
#define playerbot

# define counterlimit_meldbreak 8
#include <unordered_map>
#include <vector>
#include <algorithm>

struct dictionary_entry {
	int points;
	Tile* tile;
};

class MemoTableRow
{
public:
	vector <Formation*> formations_to_meld;
	vector <Tile*> tiles_to_add;
	vector <Tile*> tiles_replacing_joker;
	Tile* tile_to_break;
	vector <Tile*> other_tiles;

	int potential_points_down;
	int potential_points_final;

	MemoTableRow()
	{
		potential_points_down = 0;
		potential_points_final = 0;
	}

	void set_formations_to_meld(vector <Formation*> forms)
	{
		for (const auto& f : forms)
		{
			formations_to_meld.push_back(f);
		}
		set_and_calculate_potential_points();
	}

	/*void set_tiles_to_discard(vector <Tile*> tilev)
	{
		for (const auto& t : tilev)
		{
			tiles_to_discard.push_back(t);
		}
	}*/

	void set_other_tiles(vector <Tile*> tilev)
	{
		for (const auto& t : tilev)
		{
			other_tiles.push_back(t);
		}
	}

	void set_and_calculate_potential_points()
	{
		for (const auto& f : formations_to_meld)
		{
			for (const auto& t : f->formationtiles)
			{
				potential_points_down += t->downpoints;
				potential_points_final += t->finalpoints;
			}
		}
	}

	void static Display_MemoTable(vector<MemoTableRow*> memotable)
	{
		cout << "\nMEMOTABLE:";
		cout << "\n--------------------------------------------------------------------------------------------------------------------\n";
		for (const auto& row : memotable)
		{
			cout << "\n------------------------------------------------------------------\n";
			row->Display_MemoTableRow();
			cout << "\n------------------------------------------------------------------\n";
		}
		cout << "\n--------------------------------------------------------------------------------------------------------------------\n";
	}

	void Display_MemoTableRow()
	{
		cout << "Formations:\n"; Formation::DisplayFormations(formations_to_meld);
		cout << "Other Tiles: "; Tile::DisplayTiles(other_tiles);
		cout << "Tiles to add to other formations: "; Tile::DisplayTiles(tiles_to_add);
		cout << "Tiles to replace joker: "; Tile::DisplayTiles(tiles_replacing_joker);
		cout << "Broken Tile: "; cout << endl; // tile_to_break->displayInfo();
		cout << "Potential Points Down: " << potential_points_down; cout << endl;
		cout << "Potential Points Final: " << potential_points_final; cout << endl;
	}

	void Reset()
	{

	}
};
class PlayerBot : public Player
{
public:

	vector<MemoTableRow*> memotable_initial;
	vector<MemoTableRow*> memotable_firstmeld;
	vector<MemoTableRow*> memotable_firstmeld_withbreak;

	vector<Formation*> formations_firstmeld;
	Tile* tile_to_discard;
	Tile* tile_to_break;

	PlayerBot() :Player()
	{
		tile_to_discard = nullptr;
		tile_to_break = nullptr;
		playertype = "bot";
	}

	void Removetilefromboard(Tile* t)
	{
		for (int i = 0; i < playerboard->board_tiles.size(); i++)
		{
			if (Tile::CheckSameTile(playerboard->board_tiles[i], t))
			{
				playerboard->board_tiles.erase(playerboard->board_tiles.begin() + i);
				playerboard->tilesnoboard--;
				break;
			}
		}
	}

	void CopyofPlayerboard(vector <Tile*>& aux_playerboard)
	{
		for (const auto& tile : playerboard->board_tiles)
		{
			aux_playerboard.push_back(tile);
		}
	}

	int PartitionSet(vector<Tile*>& tilez, int low, int high)
	{
		int pivot = tilez[high]->getnumber();

		int i = low - 1;

		for (int j = low; j < high; j++)
		{
			if (tilez[j]->getnumber() < pivot)
			{
				i++;
				swap(tilez[i], tilez[j]);
			}
		}

		swap(tilez[i + 1], tilez[high]);
		return i + 1;
	}

	void QuicksortSet(vector<Tile*>& tilez, int low, int high)
	{
		if (low < high)
		{
			int pivot = PartitionSet(tilez, low, high);
			QuicksortSet(tilez, low, pivot - 1);
			QuicksortSet(tilez, pivot + 1, high);
		}
	}

	int PartitionRunColours(vector<Tile*>& tilez, int low, int high)
	{
		int pivot = tilez[high]->getcolourid();

		int i = low - 1;

		for (int j = low; j < high; j++)
		{
			if (tilez[j]->getcolourid() < pivot)
			{
				i++;
				swap(tilez[i], tilez[j]);
			}
		}

		swap(tilez[i + 1], tilez[high]);
		return i + 1;
	}

	void QuicksortRunColours(vector<Tile*>& tilez, int low, int high)
	{
		if (low < high)
		{
			int pivot = PartitionRunColours(tilez, low, high);
			QuicksortRunColours(tilez, low, pivot - 1);
			QuicksortRunColours(tilez, pivot + 1, high);
		}
	}

	void SortForSet(vector<Tile*>& tilez) // QUICKSORT
	{
		// sort by number
		int low = 0; int high = tilez.size() - 1;

		// set joker to last position and don't include it in sort
		int i = 0;
		while (i <= high)
		{
			if (tilez[i]->type == "joker")
			{
				tilez.push_back(tilez[i]);
				high--;
				tilez.erase(tilez.begin() + i);
			}
			else
			{
				i++;
			}
		}

		// sort by number
		QuicksortSet(tilez, low, high);
		cout << "\n\nSETS:\n";  Tile::DisplayTiles(tilez); // Console::pause_console();
	}

	void SortForRun(vector<Tile*>& tilez)
	{
		// sort by colour; then by number
		int low = 0; int high = tilez.size() - 1;

		// set joker to last position and don't include it in sort
		int i = 0;
		while (i <= high)
		{
			if (tilez[i]->type == "joker")
			{
				tilez.push_back(tilez[i]);
				high--;
				tilez.erase(tilez.begin() + i);
			}
			else
			{
				i++;
			}
		}

		// sort by colour
		QuicksortRunColours(tilez, low, high);

		// sort colour sections by number
		i = 1;
		low = 0;
		while (i < tilez.size())
		{
			if (tilez[i]->getcolour() != tilez[i - 1]->getcolour() || tilez[i]->type == "joker")
			{
				QuicksortSet(tilez, low, i - 1);
				low = i;
			}
			i++;
		}
		QuicksortSet(tilez, low, i - 1);
		cout << "\n\nRUNS:\n"; Tile::DisplayTiles(tilez); // Console::pause_console();
	}

	void SetGenerateCombinations(vector<Tile*> tiles, int k, int start, vector<Tile*> combination, vector<Formation*>& result)
	{
		if (k == 0)
		{
			vector<Tile*> combination_copy;
			Tile::DeepCopy(combination, combination_copy);
			Formation* f = new Formation(combination_copy);
			if (f->valid)
			{
				result.push_back(f);
			}
			else
			{
				delete f;
				Formation::formationno--;
			}
			return;
		}

		for (int j = start; j <= tiles.size() - k; ++j)
		{
			combination.push_back(tiles[j]);
			SetGenerateCombinations(tiles, k - 1, j + 1, combination, result);
			combination.pop_back();
		}
	}

	void SetForminTiles(vector<Formation*>& formations_found, vector<Tile*>& tilesforcombinations, int mini, int maxi)
	{
		vector<Tile*> combination;
		vector<Formation*> result;
		for (int k = mini; k <= maxi; k++)
		{
			SetGenerateCombinations(tilesforcombinations, k, 0, combination, result);
		}
		for (const auto& f : result)
		{
			if (f->valid)
			{
				formations_found.push_back(f);
			}
		}
	}

	void SetForminTilesSection(int i, int low, vector<Tile*>& tilez, vector<Tile*>& tilesforcombinations, vector<Formation*>& formations_found)
	{
		// SECTION: LOW -> i-1
		int diff = i - low;
		if (tilez[tilez.size() - 1]->type == "joker") // add joker if found
		{
			diff++;
			tilesforcombinations.push_back(new JokerTile(3));
		}

		// add all other tiles and delete duplicates
		for (int j = low; j <= i - 1; j++)
		{
			bool okut = true;
			if (j != i - 1)
			{
				for (int l = j + 1; l <= i - 1; l++)
				{
					if (Tile::CheckSameTile(tilez[j], tilez[l]) == true)
					{
						okut = false;
						diff--;
						break;
					}
				}
			}
			if (okut)
			{
				tilesforcombinations.push_back(tilez[j]);
			}

		}

		//cout << "SET DIFF: "<<diff << endl; Tile::DisplayTiles(tilesforcombinations); Console::pause_console();

		if (diff >= 3)
		{
			// generate combinations
			SetForminTiles(formations_found, tilesforcombinations, 3, diff);
		}
	}

	void CreateSetFormations(vector<Tile*>& tilez, vector<Formation*>& aux_setformations)
	{
		vector <Formation*> formations_found;
		int i = 1;
		int low = 0;
		vector <Tile*> tilesforcombinations;

		while (i < tilez.size())
		{
			if (tilez[i]->getnumber() != tilez[i - 1]->getnumber())
			{
				// SECTION: LOW -> i-1
				tilesforcombinations.clear();
				SetForminTilesSection(i, low, tilez, tilesforcombinations, formations_found);
				low = i;
			}
			i++;
		}
		tilesforcombinations.clear();
		SetForminTilesSection(i, low, tilez, tilesforcombinations, formations_found);
		low = i;

		for (const auto& f : formations_found)
		{
			aux_setformations.push_back(f);
		}

		//Formation::DisplayFormations(formations_found);
		//Console::pause_console();
	}

	void RunGeneratePermutations(vector<Tile*> combination, vector<Formation*>& result)
	{
		sort(combination.begin(), combination.end());
		do
		{
			vector<Tile*> combination_copy;
			Tile::DeepCopy(combination, combination_copy);
			Formation* f = new Formation(combination_copy);
			// f->displayFormationinfo(); Console::pause_console();
			if (f->valid)
			{
				result.push_back(f);
			}
			else
			{
				delete f;
				Formation::formationno--;
			}

		} while (next_permutation(combination.begin(), combination.end()));
	}

	void RunGenerateCombinations(vector<Tile*> tiles, int k, int start, vector<Tile*> combination, vector<Formation*>& result)
	{
		if (k == 0)
		{
			// combination found here
			RunGeneratePermutations(combination, result);
			return;
		}

		for (int j = start; j <= tiles.size() - k; ++j)
		{
			combination.push_back(tiles[j]);
			RunGenerateCombinations(tiles, k - 1, j + 1, combination, result);
			combination.pop_back();
		}
	}

	void RunForminTiles(vector<Formation*>& formations_found, vector<Tile*>& tilesforcombinations, int mini, int maxi)
	{
		vector<Tile*> combination;
		vector<Formation*> result;
		for (int k = mini; k <= maxi; k++)
		{
			RunGenerateCombinations(tilesforcombinations, k, 0, combination, result);
		}
		for (const auto& f : result)
		{
			if (f->valid)
			{
				formations_found.push_back(f);
			}
		}
	}

	void RunForminTilesSection(int i, int low, vector<Tile*>& tilez, vector<Tile*>& tilesforcombinations, vector<Formation*>& formations_found)
	{
		// SECTION: LOW -> i-1
		int diff = i - low;
		if (tilez[tilez.size() - 1]->type == "joker") // add joker if found
		{
			diff++;
			tilesforcombinations.push_back(new JokerTile(3));
		}

		// add all other tiles and delete duplicates
		for (int j = low; j <= i - 1; j++)
		{
			bool okut = true;
			if (j != i - 1)
			{
				for (int l = j + 1; l <= i - 1; l++)
				{
					if (Tile::CheckSameTile(tilez[j], tilez[l]) == true)
					{
						okut = false;
						diff--;
						break;
					}
				}
			}
			if (okut)
			{
				tilesforcombinations.push_back(tilez[j]);
			}

		}

		// cout << "RUN DIFF: " << diff << endl; Tile::DisplayTiles(tilesforcombinations); Console::pause_console();

		if (diff >= 3)
		{
			// generate combinations
			RunForminTiles(formations_found, tilesforcombinations, 3, diff);
		}
		tilesforcombinations.clear();
	}

	void CreateRunFormations(vector<Tile*>& tilez, vector<Formation*>& aux_runformations)
	{
		vector <Formation*> formations_found;
		int i = 1;
		int low = 0;
		vector <Tile*> tilesforcombinations;

		while (i < tilez.size())
		{
			if (tilez[i]->getcolour() != tilez[i - 1]->getcolour())
			{
				// SECTION: LOW -> i-1
				tilesforcombinations.clear();
				RunForminTilesSection(i, low, tilez, tilesforcombinations, formations_found);
				low = i;
			}
			i++;
		}
		tilesforcombinations.clear();
		RunForminTilesSection(i, low, tilez, tilesforcombinations, formations_found);
		low = i;

		for (const auto& f : formations_found)
		{
			aux_runformations.push_back(f);
		}

		//Formation::DisplayFormations(formations_found);
		// Console::pause_console();
	}

	bool FilterFormations_JokerFormation(vector<Formation*> combination, int number_of_jokers)
	{
		int joker_in_formations = 0;
		for (const auto& f : combination)
		{
			for (const auto& t : f->formationtiles)
			{
				if (t->type == "joker")
				{
					joker_in_formations++;
					if (joker_in_formations > 2)
					{
						return false;
					}
				}
			}
		}
		if (joker_in_formations <= number_of_jokers)
		{
			return true;
		}
		return false;
	}

	bool FilterFormations_DuplicatesOnBoard_Combination(vector<Formation*> combination)
	{
		vector <Tile*> aux_playertiles; aux_playertiles.clear(); CopyofPlayerboard(aux_playertiles);
		// combination

		bool ok = true; // assume it's good

		for (const auto& f : combination) // loop through formations of results
		{
			ok = true;
			for (const auto& t : f->formationtiles) // tile in formation
			{
				bool ok2 = false; // assume tile not on board
				for (int j = 0; j < aux_playertiles.size(); j++)
				{
					if (Tile::CheckSameTile(aux_playertiles[j], t))
					{
						aux_playertiles.erase(aux_playertiles.begin() + j);
						ok2 = true;
						break;
					}
				}
				if (ok2 == false)
				{
					ok = false;
					break;
				}
			}
			if (ok == false)
			{
				break;
			}
		}

		cout << "";
		return ok;
	}

	bool FilterFormations_Break(vector<Formation*> comb)
	{
		vector <Tile*> aux_playertiles; aux_playertiles.clear(); CopyofPlayerboard(aux_playertiles);

		//check break in player board
		bool broken_in_player_tiles = false;
		if (checkOneTileonBoard(tile_to_break))
		{
			broken_in_player_tiles = true;
		}
		if (broken_in_player_tiles)
		{
			bool conti = false;
			bool used = false;
			for (auto& f : comb)
			{
				for (int i = 0; i < f->formationtiles.size(); i++)
				{
					if (Tile::CheckSameTile(tile_to_break, f->formationtiles[i]) && !used)
					{
						used = true;
					}
					else if (Tile::CheckSameTile(tile_to_break, f->formationtiles[i]) && used)
					{
						conti = true;
						f->formationtiles.erase(f->formationtiles.begin() + i);
						break;
					}
				}
			}
			if (conti)
			{
				return FilterFormations_DuplicatesOnBoard_Combination(comb);
			}
			else { return false; }
		}
		else
		{
			bool conti = false;
			for (auto& f : comb)
			{
				for (int i = 0; i < f->formationtiles.size(); i++)
				{
					if (Tile::CheckSameTile(tile_to_break, f->formationtiles[i]))
					{
						conti = true;
						f->formationtiles.erase(f->formationtiles.begin() + i);
						break;
					}
				}
				if (conti) { break; }
			}
			if (conti)
			{
				return FilterFormations_DuplicatesOnBoard_Combination(comb);
			}
			else { return false; }
		}
		return false;
	}

	void GenerateFormationsCombinations(vector<Formation*> aux_formations, int k, int start, vector<Formation*> combination, vector<vector<Formation*>>& result, int jokerno)
	{
		if (k == 0)
		{
			if (tile_to_break == nullptr)
			{
				result.push_back(combination);
				return;
			}
			else
			{
				vector<Formation*> aux; aux.clear();
				bool counter = 0;
				for (const auto& f : combination)
				{
					counter++;
					Formation* newFormation = new Formation(*f);
					aux.push_back(newFormation);
				}
				// Formation::formationno-=counter;
				if (FilterFormations_Break(aux))
				{
					result.push_back(combination);
				}
				for (const auto& f : aux)
				{
					delete f;
				}
				return;
			}
		}

		for (int j = start; j <= aux_formations.size() - k; ++j)
		{
			combination.push_back(aux_formations[j]);
			if (FilterFormations_JokerFormation(combination, jokerno))
			{
				if (tile_to_break == nullptr)
				{
					if (FilterFormations_DuplicatesOnBoard_Combination(combination))
					{
						GenerateFormationsCombinations(aux_formations, k - 1, j + 1, combination, result, jokerno);
					}
				}
				else
				{
					GenerateFormationsCombinations(aux_formations, k - 1, j + 1, combination, result, jokerno);
				}
			}
			combination.pop_back();
		}
	}

	void FilterFormations_DuplicatesOnBoard(vector<vector<Formation*>>& result)
	{
		int i = 0;
		while (i < result.size())
		{
			vector <Tile*> aux_playertiles; aux_playertiles.clear(); CopyofPlayerboard(aux_playertiles);

			// result[i]

			bool ok = true; // assume it's good

			for (const auto& f : result[i]) // loop through formations of results
			{
				ok = true;
				for (const auto& t : f->formationtiles) // tile in formation
				{
					bool ok2 = false; // assume tile not on board
					for (int j = 0; j < aux_playertiles.size(); j++)
					{
						if (Tile::CheckSameTile(aux_playertiles[j], t))
						{
							aux_playertiles.erase(aux_playertiles.begin() + j);
							ok2 = true;
							break;
						}
					}
					if (ok2 == false)
					{
						ok = false;
						break;
					}
				}
				if (ok == false)
				{
					break;
				}
			}
			if (ok == false)
			{
				result.erase(result.begin() + i);
			}
			else
			{
				i++;
			}
		}
	}

	vector<vector<Formation*>> PutFormationsTogether(vector <Formation*>& aux_formations)
	{
		vector<Formation*> combination;
		vector<vector<Formation*>> result;

		int kappa = 0;

		// calculate number of jokers in player tiles
		int jokerno = 0;
		for (const auto& t : playerboard->board_tiles)
		{
			if (t->type == "joker")
			{
				jokerno++;
			}
		}

		if (firstmeld) // firstmeld is true => completed firstmeld
		{
			kappa = 1;
		}
		else
		{
			kappa = 2;
		}

		for (int k = kappa; k <= aux_formations.size(); k++)
		{
			GenerateFormationsCombinations(aux_formations, k, 0, combination, result, jokerno);
		}

		if (firstmeld) // firstmeld is true => completed firstmeld
		{
			for (const auto& res : result)
			{
				cout << "\nNEW: \n\n";
				Formation::DisplayFormations(res);
			}
			Console::pause_console();
		}
		else
		{
			int i = 0;
			while (i < result.size())
			{
				if (checkfirstmeld(result[i]))
				{
					i++;
				}
				else
				{
					result.erase(result.begin() + i);
				}
			}

		}

		/*cout << "\n\nGenerated Formations FINAL: \n\n";
		for (const auto& res : result)
		{
			cout << "\nNEW: \n\n";
			Formation::DisplayFormations(res);
		}
		Console::pause_console();*/

		return result;
	}

	vector<Tile*> FirstMeldNoBreak_tilestodiscard(vector<Formation*> forms)
	{
		vector <Tile*> aux_playertiles; aux_playertiles.clear(); CopyofPlayerboard(aux_playertiles);

		for (const auto& f : forms) // loop through formations of results
		{
			for (const auto& t : f->formationtiles) // tile in formation
			{
				for (int j = 0; j < aux_playertiles.size(); j++)
				{
					if (Tile::CheckSameTile(aux_playertiles[j], t))
					{
						aux_playertiles.erase(aux_playertiles.begin() + j);
						break;
					}
				}
			}
		}
		return aux_playertiles;
	}

	void Sort_Dictionary(vector<dictionary_entry>& aux_dictionary)
	{
		// sort dictionary by values (ascending) and then by keys final points (tile->finalpoints)
		for (int i = 0; i < aux_dictionary.size() - 1; i++)
		{
			for (int j = i + 1; j < aux_dictionary.size(); j++)
			{
				if (aux_dictionary[i].points == aux_dictionary[j].points)
				{
					if (aux_dictionary[i].tile->finalpoints > aux_dictionary[j].tile->finalpoints)
					{
						swap(aux_dictionary[i], aux_dictionary[j]);
					}
				}
				else
				{
					if (aux_dictionary[j].points < aux_dictionary[i].points)
					{
						swap(aux_dictionary[i], aux_dictionary[j]);
					}
				}
			}
		}
		for (int i = 0; i < aux_dictionary.size(); i++)
		{
			aux_dictionary[i].tile->displayInfo();
			cout << " " << aux_dictionary[i].points << " " << aux_dictionary[i].tile->finalpoints << endl;
		}
	}

	void Set_Potential_Formations_Initial(vector <Tile*> remainingt, vector<dictionary_entry>& aux_dictionary)
	{
		// get all permutations of 2 tiles and then add joker
		for (int i = 0; i < remainingt.size() - 1; i++)
		{
			for (int j = i + 1; j < remainingt.size(); j++)
			{
				vector<Tile*> aux;
				aux.clear();
				aux.push_back(remainingt[i]);
				aux.push_back(remainingt[j]);
				aux.push_back(new JokerTile(1));

				do
				{
					vector<Tile*> aux2;
					aux2.clear();
					Tile::DeepCopy(aux2, aux);
					Formation* f = new Formation(aux);
					if (f->valid)
					{
						for (int k = 0; k < aux_dictionary.size(); k++)
						{
							if (Tile::CheckSameTile(aux_dictionary[k].tile, remainingt[i]))
							{
								aux_dictionary[k].points += 2;
								break;
							}
						}
						for (int k = 0; k < aux_dictionary.size(); k++)
						{
							if (Tile::CheckSameTile(aux_dictionary[k].tile, remainingt[j]))
							{
								aux_dictionary[k].points += 2;
								break;
							}
						}
					}
					delete f;
					Formation::formationno--;
					break;
				} while (next_permutation(aux.begin(), aux.end()));
			}
		}
	}

	void Set_Dictionary_Values_Initial(vector <Tile*> aux_playerboard, vector<dictionary_entry>& aux_dictionary, vector <Formation*> aux_formations)
	{
		// set final points to tiles in dictionary: 5/10/25/50
		for (auto& entry : aux_dictionary)
		{
			entry.points += entry.tile->finalpoints;
		}

		// set points for possible formations: 100 in formation; 2 in potential formation
		vector<Tile*> remainingt; CopyofPlayerboard(remainingt);
		for (const auto& f : aux_formations)
		{
			for (const auto& t : f->formationtiles)
			{
				for (int i = 0; i < aux_dictionary.size(); i++)
				{
					if (Tile::CheckSameTile(aux_dictionary[i].tile, t))
					{
						aux_dictionary[i].points += 100;
					}
				}
				/*for (int i = 0; i < remainingt.size(); i++)
				{
					if (Tile::CheckSameTile(remainingt[i], t))
					{
						remainingt.erase(remainingt.begin() + i); break;
					}
				}*/
			}
		}

		Set_Potential_Formations_Initial(remainingt, aux_dictionary);
	}

	bool Check_Formation_for_Meldbreak(Formation* formation_to_check)
	{
		if (checkOneTileonBoard(tile_to_break))
		{
			return true;
		}
		return false;
	}

	bool Compare_Formations_Break(Formation* a, Formation* b)
	{
		return a->points > b->points;
	}

	void Memo_Table_Initial(vector <Player*> players)
	{
		memotable_initial.clear();

		// create aux playerboard
		vector <Tile*> aux_playerboard;
		vector <Formation*> aux_formations;
		CopyofPlayerboard(aux_playerboard);

		// set dictionary to choose tile to discard
		vector<dictionary_entry> aux_dictionary;
		aux_dictionary.clear();
		for (int i = 0; i < aux_playerboard.size(); i++)
		{
			dictionary_entry aux;
			aux.tile = aux_playerboard[i];
			aux.points = 0;
			aux_dictionary.push_back(aux);
		}

		// create possible sets and runs
		// runs: sort by colour then number; sets: sort by number

		SortForSet(aux_playerboard);
		CreateSetFormations(aux_playerboard, aux_formations);
		aux_playerboard.clear(); CopyofPlayerboard(aux_playerboard);

		SortForRun(aux_playerboard);
		CreateRunFormations(aux_playerboard, aux_formations);
		aux_playerboard.clear(); CopyofPlayerboard(aux_playerboard);

		Formation::DisplayFormations(aux_formations);
		Console::pause_console();

		CopyofPlayerboard(aux_playerboard);
		Set_Dictionary_Values_Initial(aux_playerboard, aux_dictionary, aux_formations);

		// create formations combinations
		// vector<vector<Formation*>> aux_result = PutFormationsTogether(aux_formations); // NOT WORKING FOR BREAK -> DUPLICATES/TILES NOT ON BOARD

		memotable_initial.push_back(new MemoTableRow());
		aux_playerboard.clear();
		CopyofPlayerboard(aux_playerboard);
		memotable_initial[memotable_initial.size() - 1]->set_other_tiles(aux_playerboard);


		MemoTableRow::Display_MemoTable(memotable_initial);

		// sort dictionary
		Sort_Dictionary(aux_dictionary);

		// set tile to discard
		tile_to_discard = aux_dictionary[0].tile;
		cout << "Tile to discard: "; tile_to_discard->displayInfo(); cout << endl;

		Console::pause_console();
	}

	bool Memotable_firstmeld_compare(MemoTableRow* a, MemoTableRow* b)
	{
		if (a->potential_points_down == b->potential_points_down)
		{
			return a->potential_points_final > b->potential_points_final;
		}
		return a->potential_points_down < b->potential_points_down;
	}

	bool Memo_Table_FirstMeld(vector <Player*> players)
	{
		memotable_firstmeld.clear();

		// create aux playerboard
		vector <Tile*> aux_playerboard;
		vector <Formation*> aux_formations;
		CopyofPlayerboard(aux_playerboard);

		// set dictionary to choose tile to discard
		vector<dictionary_entry> aux_dictionary;
		aux_dictionary.clear();
		for (int i = 0; i < aux_playerboard.size(); i++)
		{
			dictionary_entry aux;
			aux.tile = aux_playerboard[i];
			aux.points = 0;
			aux_dictionary.push_back(aux);
		}

		// create possible sets and runs
		// runs: sort by colour then number; sets: sort by number

		SortForSet(aux_playerboard);
		CreateSetFormations(aux_playerboard, aux_formations);
		aux_playerboard.clear(); CopyofPlayerboard(aux_playerboard);

		SortForRun(aux_playerboard);
		CreateRunFormations(aux_playerboard, aux_formations);
		aux_playerboard.clear(); CopyofPlayerboard(aux_playerboard);

		Formation::DisplayFormations(aux_formations);
		Console::pause_console();

		// create formations combinations
		vector<vector<Formation*>> aux_result = PutFormationsTogether(aux_formations); // NOT WORKING FOR BREAK -> DUPLICATES/TILES NOT ON BOARD

		// update memotable
		if (aux_result.size() == 0)
		{
			memotable_firstmeld.push_back(new MemoTableRow());
			aux_playerboard.clear();
			CopyofPlayerboard(aux_playerboard);
			memotable_firstmeld[memotable_firstmeld.size() - 1]->set_other_tiles(aux_playerboard);
		}
		else
		{
			for (const auto& res : aux_result)
			{
				memotable_firstmeld.push_back(new MemoTableRow());
				memotable_firstmeld[memotable_firstmeld.size() - 1]->set_formations_to_meld(res);
				memotable_firstmeld[memotable_firstmeld.size() - 1]->set_other_tiles(FirstMeldNoBreak_tilestodiscard(res));
			}
		}


		// Sort MemoTable entries: ascending by points; if same most points 
		sort(memotable_firstmeld.begin(), memotable_firstmeld.end(), [this](const auto& a, const auto& b) {return Memotable_firstmeld_compare(a, b); });

		MemoTableRow::Display_MemoTable(memotable_firstmeld);

		// Choose which formation
		bool firstmeld_forgame = false;
		formations_firstmeld.clear();
		if (aux_result.size() != 0)
		{
			if (memotable_firstmeld[0]->formations_to_meld.size() != 0)
			{
				firstmeld_forgame = true;
				for (const auto& f : memotable_firstmeld[0]->formations_to_meld)
				{
					formations_firstmeld.push_back(f);
				}
				FirstMeld(formations_firstmeld);
			}
		}

		// set dictionary values for tile to discard
		CopyofPlayerboard(aux_playerboard);
		Set_Dictionary_Values_Initial(aux_playerboard, aux_dictionary, aux_formations);

		// sort dictionary
		Sort_Dictionary(aux_dictionary);

		// set tile to discard
		tile_to_discard = aux_dictionary[0].tile;
		cout << "Tile to discard: "; tile_to_discard->displayInfo(); cout << endl;

		Console::pause_console();


		return firstmeld_forgame;
	}

	bool Memo_Table_FirstMeld_withBreak(vector <Player*> players, vector <Tile*>& queue)
	{
		memotable_firstmeld_withbreak.clear();
		tile_to_break = queue[queue.size() - 1];
		cout << "\nTile broken from queue  : "; tile_to_break->displayInfo();  cout << endl << endl;

		// create aux playerboard
		vector <Tile*> aux_playerboard;
		vector <Formation*> aux_formations;
		CopyofPlayerboard(aux_playerboard);

		// set dictionary to choose tile to discard
		vector<dictionary_entry> aux_dictionary;
		aux_dictionary.clear();
		for (int i = 0; i < aux_playerboard.size(); i++)
		{
			dictionary_entry aux;
			aux.tile = aux_playerboard[i];
			aux.points = 0;
			aux_dictionary.push_back(aux);
		}

		// create possible sets and runs
		// runs: sort by colour then number; sets: sort by number

		aux_playerboard.clear();  CopyofPlayerboard(aux_playerboard); aux_playerboard.push_back(tile_to_break);

		SortForSet(aux_playerboard);
		CreateSetFormations(aux_playerboard, aux_formations);
		aux_playerboard.clear(); CopyofPlayerboard(aux_playerboard); aux_playerboard.push_back(tile_to_break);

		SortForRun(aux_playerboard);
		CreateRunFormations(aux_playerboard, aux_formations);
		aux_playerboard.clear(); CopyofPlayerboard(aux_playerboard); aux_playerboard.push_back(tile_to_break);

		Formation::DisplayFormations(aux_formations);
		Console::pause_console();

		// create formations combinations
		vector<vector<Formation*>> aux_result = PutFormationsTogether(aux_formations);

		// update memotable
		if (aux_result.size() == 0)
		{
			memotable_firstmeld_withbreak.push_back(new MemoTableRow());
			aux_playerboard.clear();
			CopyofPlayerboard(aux_playerboard);
			memotable_firstmeld_withbreak[memotable_firstmeld_withbreak.size() - 1]->set_other_tiles(aux_playerboard);
		}
		else
		{
			for (const auto& res : aux_result)
			{
				memotable_firstmeld_withbreak.push_back(new MemoTableRow());
				memotable_firstmeld_withbreak[memotable_firstmeld_withbreak.size() - 1]->set_formations_to_meld(res);
				memotable_firstmeld_withbreak[memotable_firstmeld_withbreak.size() - 1]->set_other_tiles(FirstMeldNoBreak_tilestodiscard(res));
			}
		}


		// Sort MemoTable entries: ascending by points; if same most points 
		sort(memotable_firstmeld_withbreak.begin(), memotable_firstmeld_withbreak.end(), [this](const auto& a, const auto& b) {return Memotable_firstmeld_compare(a, b); });

		MemoTableRow::Display_MemoTable(memotable_firstmeld_withbreak);

		// Perform First Meld

		bool firstmeld_forgame = false;
		formations_firstmeld.clear();
		if (aux_result.size() != 0)
		{
			if (memotable_firstmeld_withbreak[0]->formations_to_meld.size() != 0)
			{
				for (int i = 0; i < memotable_firstmeld_withbreak.size(); i++)
				{
					formations_firstmeld.clear();
					for (const auto& f : memotable_firstmeld_withbreak[i]->formations_to_meld)
					{
						formations_firstmeld.push_back(f);
					}
					FirstMeldwithBreak(formations_firstmeld, tile_to_break, queue);
					if (firstmeld)
					{
						firstmeld_forgame = true;
						cout << "\nTile broken from queue  : "; tile_to_break->displayInfo();  cout << endl << endl;
						break;
					}
				}

			}
		}

		// set dictionary values for tile to discard
		CopyofPlayerboard(aux_playerboard);
		Set_Dictionary_Values_Initial(aux_playerboard, aux_dictionary, aux_formations);

		// sort dictionary
		Sort_Dictionary(aux_dictionary);

		// set tile to discard
		tile_to_discard = aux_dictionary[0].tile;
		cout << "Tile to discard: "; tile_to_discard->displayInfo(); cout << endl;

		Console::pause_console();


		tile_to_break = nullptr;
		return firstmeld_forgame;
	}

	bool Memo_Table_Meld_withBreak(vector <Player*> players, vector <Tile*>& queue)
	{
		// create aux playerboard
		vector <Tile*> aux_playerboard;
		vector <Formation*> aux_formations;
		CopyofPlayerboard(aux_playerboard);

		// set dictionary to choose tile to discard
		vector<dictionary_entry> aux_dictionary;
		aux_dictionary.clear();
		for (int i = 0; i < aux_playerboard.size(); i++)
		{
			dictionary_entry aux;
			aux.tile = aux_playerboard[i];
			aux.points = 0;
			aux_dictionary.push_back(aux);
		}

		memotable_firstmeld_withbreak.clear();

		// choose tile to break

		int counter = 0;
		for (int i = queue.size() - 1; i >= 1 && counter <= counterlimit_meldbreak; i--)
		{
			tile_to_break = queue[i];
			cout << "\nTile broken from queue  : "; tile_to_break->displayInfo();  cout << endl << endl;
			aux_formations.clear();

			// create possible sets and runs
			// runs: sort by colour then number; sets: sort by number

			aux_playerboard.clear();  CopyofPlayerboard(aux_playerboard); aux_playerboard.push_back(tile_to_break);

			SortForSet(aux_playerboard);
			CreateSetFormations(aux_playerboard, aux_formations);
			aux_playerboard.clear(); CopyofPlayerboard(aux_playerboard); aux_playerboard.push_back(tile_to_break);

			SortForRun(aux_playerboard);
			CreateRunFormations(aux_playerboard, aux_formations);
			aux_playerboard.clear(); CopyofPlayerboard(aux_playerboard); aux_playerboard.push_back(tile_to_break);

			Formation::DisplayFormations(aux_formations);
			Console::pause_console();

			for (int k = 0; k < aux_formations.size(); k++)
			{
				// check aux_formations[k]
				if (!Check_Formation_for_Meldbreak(aux_formations[k]))
				{
					aux_formations.erase(aux_formations.begin() + k);
				}
			}

			// sort aux_formations
			sort(aux_formations.begin(), aux_formations.end(), [this](const auto& a, const auto& b) {return Compare_Formations_Break(a, b); });

			for (const auto& form : aux_formations)
			{
				bool ok = MeldwithBreak(vector<Formation*> {form}, tile_to_break, queue, i);
				if (ok == true)
				{
					form->displayFormationinfo();
					cout << "\nTile broken from queue  : "; tile_to_break->displayInfo();  cout << endl << endl;
					tile_to_break = nullptr;
					return true;
				}
			}

			// try meld
			counter++;
		}
		Console::pause_console();
		tile_to_break = nullptr;

		return false;
	}

	bool Memo_Table_Meld(vector <Player*> players)
	{
		memotable_firstmeld.clear();

		// create aux playerboard
		vector <Tile*> aux_playerboard;
		vector <Formation*> aux_formations;
		CopyofPlayerboard(aux_playerboard);

		// set dictionary to choose tile to discard
		vector<dictionary_entry> aux_dictionary;
		aux_dictionary.clear();
		for (int i = 0; i < aux_playerboard.size(); i++)
		{
			dictionary_entry aux;
			aux.tile = aux_playerboard[i];
			aux.points = 0;
			aux_dictionary.push_back(aux);
		}

		// create possible sets and runs
		// runs: sort by colour then number; sets: sort by number

		SortForSet(aux_playerboard);
		CreateSetFormations(aux_playerboard, aux_formations);
		aux_playerboard.clear(); CopyofPlayerboard(aux_playerboard);

		SortForRun(aux_playerboard);
		CreateRunFormations(aux_playerboard, aux_formations);
		aux_playerboard.clear(); CopyofPlayerboard(aux_playerboard);

		Formation::DisplayFormations(aux_formations);
		Console::pause_console();

		// create formations combinations
		vector<vector<Formation*>> aux_result = PutFormationsTogether(aux_formations); // NOT WORKING FOR BREAK -> DUPLICATES/TILES NOT ON BOARD

		// update memotable
		if (aux_result.size() == 0)
		{
			memotable_firstmeld.push_back(new MemoTableRow());
			aux_playerboard.clear();
			CopyofPlayerboard(aux_playerboard);
			memotable_firstmeld[memotable_firstmeld.size() - 1]->set_other_tiles(aux_playerboard);
		}
		else
		{
			for (const auto& res : aux_result)
			{
				memotable_firstmeld.push_back(new MemoTableRow());
				memotable_firstmeld[memotable_firstmeld.size() - 1]->set_formations_to_meld(res);
				memotable_firstmeld[memotable_firstmeld.size() - 1]->set_other_tiles(FirstMeldNoBreak_tilestodiscard(res));
			}
		}


		// Sort MemoTable entries: ascending by points; if same most points 
		sort(memotable_firstmeld.begin(), memotable_firstmeld.end(), [this](const auto& a, const auto& b) {return Memotable_firstmeld_compare(a, b); });

		MemoTableRow::Display_MemoTable(memotable_firstmeld);

		// Choose which formation
		bool firstmeld_forgame = false;
		formations_firstmeld.clear();
		if (aux_result.size() != 0)
		{
			if (memotable_firstmeld[0]->formations_to_meld.size() != 0)
			{
				firstmeld_forgame = true;
				for (const auto& f : memotable_firstmeld[0]->formations_to_meld)
				{
					formations_firstmeld.push_back(f);
				}
				FirstMeld(formations_firstmeld);
			}
		}

		// set dictionary values for tile to discard
		CopyofPlayerboard(aux_playerboard);
		Set_Dictionary_Values_Initial(aux_playerboard, aux_dictionary, aux_formations);

		// sort dictionary
		Sort_Dictionary(aux_dictionary);

		// set tile to discard
		tile_to_discard = aux_dictionary[0].tile;
		cout << "Tile to discard: "; tile_to_discard->displayInfo(); cout << endl;

		Console::pause_console();


		return firstmeld_forgame;
	}

};

#endif
