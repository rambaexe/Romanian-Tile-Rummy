#ifndef playerbot
#define playerbot


class MemoTableRow
{
public:
	vector <Formation*> formations_to_meld;
	vector <Tile*> tiles_to_discard;
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

	void set_tiles_to_discard(vector <Tile*> tilev)
	{
		for (const auto& t : tilev)
		{
			tiles_to_discard.push_back(t);
		}
	}

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
		cout << "Tiles to discard: "; Tile::DisplayTiles(tiles_to_discard);
		cout << "Tiles to add to other formations: "; Tile::DisplayTiles(tiles_to_add);
		cout << "Tiles to replace joker: "; Tile::DisplayTiles(tiles_replacing_joker);
		cout << "Broken Tile: "; // tile_to_break->displayInfo();
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

	vector<MemoTableRow*> memotable_firstmeld;

	PlayerBot() :Player()
	{
		playertype = "bot";
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
		int low = 0; int high = tilez.size()-1;

		// set joker to last position and don't include it in sort
		int i = 0;
		while(i <= high)
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
			if(tilez[i]->getnumber() != tilez[i - 1]->getnumber())
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

	bool FilterFormations_DuplicatesOnBoard_Combination(vector<Formation*>& combination)
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
		
		return ok;
	}

	void GenerateFormationsCombinations(vector<Formation*> aux_formations, int k, int start, vector<Formation*> combination, vector<vector<Formation*>>& result, int jokerno)
	{
		if (k == 0)
		{
			// combination found here
			result.push_back(combination);
			return;
		}

		for (int j = start; j <= aux_formations.size() - k; ++j)
		{
			combination.push_back(aux_formations[j]);
			if (FilterFormations_JokerFormation(combination, jokerno))
			{
				if (FilterFormations_DuplicatesOnBoard_Combination(combination))
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
					if (ok2==false)
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

	void Memo_Table_FirstMeld(vector <Player*> players, vector <Tile*> queue) 
	{
		
	}

	void Memo_Table_FirstMeld_NoBreak(vector <Player*> players) 
	{
		// create aux playerboard
		vector <Tile*> aux_playerboard;
		vector <Formation*> aux_formations;
		CopyofPlayerboard(aux_playerboard);
		
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

		// update formations table
		for (const auto& res : aux_result)
		{
			memotable_firstmeld.push_back(new MemoTableRow());
			memotable_firstmeld[memotable_firstmeld.size() - 1]->set_formations_to_meld(res);
			// decide which tiles to discard
			memotable_firstmeld[memotable_firstmeld.size() - 1]->set_other_tiles(FirstMeldNoBreak_tilestodiscard(res));
		}

		MemoTableRow::Display_MemoTable(memotable_firstmeld);
		Console::pause_console();
		
	}

};

#endif
