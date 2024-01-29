#ifndef test
#define test

#include <iostream>
#include "console_h.h"
#include "classes.h"
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <functional>

using namespace std;

void testformations()
{
	vector<Formation*> form;
	vector<Tile*> tiles;

	cout << "-------------------------------------- RUN ------------------------------" << endl;

	tiles.clear();
	tiles.push_back(new NormalTile("red", 3, 0));
	tiles.push_back(new NormalTile("red", 4, 0));
	tiles.push_back(new NormalTile("red", 5, 0));
	form.push_back(new Formation(tiles, "run"));
	
	tiles.clear();
	tiles.push_back(new NormalTile("red", 12, 0));
	tiles.push_back(new NormalTile("red", 13, 0));
	tiles.push_back(new NormalTile("red", 1, 0));	
	form.push_back(new Formation(tiles, "run"));

	tiles.clear();
	tiles.push_back(new NormalTile("yellow", 12, 0));
	tiles.push_back(new NormalTile("red", 13, 0));
	tiles.push_back(new NormalTile("red", 1, 0));
	form.push_back(new Formation(tiles, "run"));

	tiles.clear();
	tiles.push_back(new NormalTile("black", 1, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("black", 1, 0));
	form.push_back(new Formation(tiles, "run"));

	tiles.clear();
	tiles.push_back(new NormalTile("black", 1, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("black", 3, 0));
	tiles.push_back(new NormalTile("black", 4, 0));
	form.push_back(new Formation(tiles, "run"));

	tiles.clear();
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("black", 3, 0));
	tiles.push_back(new NormalTile("black", 4, 0));
	form.push_back(new Formation(tiles, "run"));

	tiles.clear();
	tiles.push_back(new NormalTile("black", 1, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("black", 3, 0));
	tiles.push_back(new NormalTile("black", 4, 0));
	form.push_back(new Formation(tiles, "run"));

	tiles.clear();
	tiles.push_back(new NormalTile("black", 1, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("black", 4, 0));
	form.push_back(new Formation(tiles, "run"));

	// 12 - j - 1
	// j - 13 - 1
	// 12 - 13 - j
	// j - 2 - 3
	// 1 - 2 - j
	// 1 - j - 3

	tiles.clear();
	tiles.push_back(new NormalTile("red", 12, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("red", 1, 0));
	form.push_back(new Formation(tiles, "run"));

	tiles.clear();
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("red", 13, 0));
	tiles.push_back(new NormalTile("red", 1, 0));
	form.push_back(new Formation(tiles, "run"));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 12, 0));
	tiles.push_back(new NormalTile("red", 13, 0));
	tiles.push_back(new JokerTile(1));
	form.push_back(new Formation(tiles, "run"));

	tiles.clear();
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("red", 3, 0));
	form.push_back(new Formation(tiles, "run"));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 1, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("red", 3, 0));
	form.push_back(new Formation(tiles, "run"));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 1, 0));
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new JokerTile(1));
	form.push_back(new Formation(tiles, "run"));

	tiles.clear();
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("red", 3, 0));
	form.push_back(new Formation(tiles, "run"));

	tiles.clear();
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("red", 3, 0));
	form.push_back(new Formation(tiles, "run"));

	tiles.clear();
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("red", 3, 0));
	form.push_back(new Formation(tiles, "run"));

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}

	form.clear();

	cout << "-------------------------------------- SET ------------------------------" << endl;

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	form.push_back(new Formation(tiles, "set"));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	form.push_back(new Formation(tiles, "set"));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	form.push_back(new Formation(tiles, "set"));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new JokerTile(1));
	form.push_back(new Formation(tiles, "set"));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new JokerTile(1));
	form.push_back(new Formation(tiles, "set"));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	form.push_back(new Formation(tiles, "set"));
	
	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	form.push_back(new Formation(tiles, "set"));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	form.push_back(new Formation(tiles, "set"));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	form.push_back(new Formation(tiles, "set"));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	tiles.push_back(new JokerTile(1));
	form.push_back(new Formation(tiles, "set"));


	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}

	form.clear();

	cout << "-------------------------------------- RUN ------------------------------" << endl;

	tiles.clear();
	tiles.push_back(new NormalTile("red", 3, 0));
	tiles.push_back(new NormalTile("red", 4, 0));
	tiles.push_back(new NormalTile("red", 5, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 12, 0));
	tiles.push_back(new NormalTile("red", 13, 0));
	tiles.push_back(new NormalTile("red", 1, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("yellow", 12, 0));
	tiles.push_back(new NormalTile("red", 13, 0));
	tiles.push_back(new NormalTile("red", 1, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("black", 1, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("black", 1, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("black", 1, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("black", 3, 0));
	tiles.push_back(new NormalTile("black", 4, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("black", 3, 0));
	tiles.push_back(new NormalTile("black", 4, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("black", 1, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("black", 3, 0));
	tiles.push_back(new NormalTile("black", 4, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("black", 1, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("black", 4, 0));
	form.push_back(new Formation(tiles));

	// 12 - j - 1
	// j - 13 - 1
	// 12 - 13 - j
	// j - 2 - 3
	// 1 - 2 - j
	// 1 - j - 3

	tiles.clear();
	tiles.push_back(new NormalTile("red", 12, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("red", 1, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("red", 13, 0));
	tiles.push_back(new NormalTile("red", 1, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 12, 0));
	tiles.push_back(new NormalTile("red", 13, 0));
	tiles.push_back(new JokerTile(1));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("red", 3, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 1, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("red", 3, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 1, 0));
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new JokerTile(1));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("red", 3, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("red", 3, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("red", 3, 0));
	form.push_back(new Formation(tiles));

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}

	form.clear();

	cout << "-------------------------------------- SET ------------------------------" << endl;

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new JokerTile(1));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new JokerTile(1));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	tiles.push_back(new JokerTile(1));
	form.push_back(new Formation(tiles));

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}
	form.clear();

	cout << "------------------------------------------------------------------------------\n";
	tiles.push_back(new JokerTile(1));

	tiles.clear();
	tiles.push_back(new NormalTile("blue", 9, 0));
	tiles.push_back(new NormalTile("blue", 10, 0));
	tiles.push_back(new NormalTile("blue", 11, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("yellow", 9, 0));
	tiles.push_back(new NormalTile("blue", 10, 0));
	tiles.push_back(new NormalTile("blue", 11, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("blue", 9, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("blue", 11, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("black", 12, 0));
	tiles.push_back(new NormalTile("red", 12, 0));
	tiles.push_back(new NormalTile("blue", 12, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 12, 0));
	tiles.push_back(new NormalTile("red", 12, 0));
	tiles.push_back(new NormalTile("blue", 12, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("black", 12, 0));
	tiles.push_back(new NormalTile("red", 12, 0));
	tiles.push_back(new JokerTile(1));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("blue", 8, 0));
	tiles.push_back(new NormalTile("blue", 9, 0));
	tiles.push_back(new NormalTile("blue", 10, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("blue", 1, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new NormalTile("blue", 3, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("blue", 12, 0));
	tiles.push_back(new NormalTile("blue", 13, 0));
	tiles.push_back(new NormalTile("blue", 1, 0));
	form.push_back(new Formation(tiles));


	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}
	
	form.clear();

	cout << "-------------------------------------- SET ------------------------------" << endl;

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	form.push_back(new Formation(tiles));
	//vector<Tile*> e;
	//e.push_back(new NormalTile("black", 2, 0));
	//form[0]->addtoFormation(e);

	tiles.clear();
	tiles.push_back(new NormalTile("red", 1, 0));
	tiles.push_back(new NormalTile("yellow", 1, 0));
	tiles.push_back(new NormalTile("blue", 1, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 1, 0));
	tiles.push_back(new NormalTile("yellow", 1, 0));
	tiles.push_back(new NormalTile("blue", 1, 0));
	tiles.push_back(new JokerTile(1));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 12, 0));
	tiles.push_back(new NormalTile("yellow", 12, 0));
	tiles.push_back(new NormalTile("blue", 12, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new JokerTile(1));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new JokerTile(1));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 2, 0));
	tiles.push_back(new NormalTile("black", 2, 0));
	tiles.push_back(new NormalTile("blue", 2, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	tiles.push_back(new JokerTile(1));
	form.push_back(new Formation(tiles));

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}
	form.clear();

	cout << "----------------------- First Meld ------------------------------\n";

	tiles.clear();
	tiles.push_back(new NormalTile("black", 9, 0));
	tiles.push_back(new NormalTile("red", 9, 0));
	tiles.push_back(new NormalTile("yellow", 9, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 7, 0));
	tiles.push_back(new NormalTile("red", 8, 0));
	tiles.push_back(new NormalTile("red", 9, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("yellow", 2, 0));
	tiles.push_back(new NormalTile("yellow", 3, 0));
	tiles.push_back(new NormalTile("yellow", 4, 0));
	form.push_back(new Formation(tiles));

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}

	if (Game::checkfirstmeld(form))
	{
		cout << "valid first meld\n";
	}
	else
	{
		cout << "not a valid first meld\n";
	}
	cout << endl << " --------------------------------" << endl;
	form.clear();

	tiles.clear();
	tiles.push_back(new NormalTile("red", 7, 0));
	tiles.push_back(new NormalTile("red", 8, 0));
	tiles.push_back(new NormalTile("red", 9, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 12, 0));
	tiles.push_back(new NormalTile("black", 12, 0));
	tiles.push_back(new NormalTile("blue", 12, 0));
	form.push_back(new Formation(tiles));

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}

	if (Game::checkfirstmeld(form))
	{
		cout << "valid first meld\n";
	}
	else
	{
		cout << "not a valid first meld\n";
	}
	cout << endl << " --------------------------------" << endl;
	form.clear();

	tiles.clear();
	tiles.push_back(new NormalTile("yellow", 9, 0));
	tiles.push_back(new NormalTile("yellow", 10, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("yellow", 12, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 9, 0));
	tiles.push_back(new NormalTile("black", 9, 0));
	tiles.push_back(new NormalTile("blue", 9, 0));
	form.push_back(new Formation(tiles));

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}

	if (Game::checkfirstmeld(form))
	{
		cout << "valid first meld\n";
	}
	else
	{
		cout << "not a valid first meld\n";
	}
	cout << endl << " --------------------------------" << endl;
	form.clear();

	tiles.clear();
	tiles.push_back(new NormalTile("yellow", 2, 0));
	tiles.push_back(new NormalTile("yellow", 3, 0));
	tiles.push_back(new NormalTile("yellow", 4, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 9, 0));
	tiles.push_back(new NormalTile("black", 9, 0));
	tiles.push_back(new NormalTile("blue", 9, 0));
	tiles.push_back(new NormalTile("yellow", 9, 0));
	form.push_back(new Formation(tiles));

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}

	if (Game::checkfirstmeld(form))
	{
		cout << "valid first meld\n";
	}
	else
	{
		cout << "not a valid first meld\n";
	}
	cout << endl << " --------------------------------" << endl;
	form.clear();

	tiles.clear();
	tiles.push_back(new NormalTile("yellow", 1, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	tiles.push_back(new NormalTile("yellow", 3, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 9, 0));
	tiles.push_back(new NormalTile("black", 9, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("yellow", 9, 0));
	form.push_back(new Formation(tiles));

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}

	if (Game::checkfirstmeld(form))
	{
		cout << "valid first meld\n";
	}
	else
	{
		cout << "not a valid first meld\n";
	}
	cout << endl << " --------------------------------" << endl;
	form.clear();

	tiles.clear();
	tiles.push_back(new NormalTile("yellow", 2, 0));
	tiles.push_back(new NormalTile("yellow", 3, 0));
	tiles.push_back(new NormalTile("yellow", 4, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("blue", 11, 0));
	tiles.push_back(new NormalTile("blue", 12, 0));
	tiles.push_back(new NormalTile("blue", 13, 0));
	form.push_back(new Formation(tiles));

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}

	if (Game::checkfirstmeld(form))
	{
		cout << "valid first meld\n";
	}
	else
	{
		cout << "not a valid first meld\n";
	}
	cout << endl << " --------------------------------" << endl;
	form.clear();

	tiles.clear();
	tiles.push_back(new NormalTile("red", 9, 0));
	tiles.push_back(new NormalTile("black", 9, 0));
	tiles.push_back(new NormalTile("yellow", 9, 0));
	form.push_back(new Formation(tiles));

	tiles.clear();
	tiles.push_back(new NormalTile("red", 12, 0));
	tiles.push_back(new NormalTile("black", 12, 0));
	tiles.push_back(new NormalTile("blue", 12, 0));
	form.push_back(new Formation(tiles));

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}

	if (Game::checkfirstmeld(form))
	{
		cout << "valid first meld\n";
	}
	else
	{
		cout << "not a valid first meld\n";
	}
	cout << endl << " --------------------------------" << endl;
	form.clear();
}

void testfirstmeld()
{
	vector<Formation*> form;
	vector<Tile*> tiles;
	Player* player1 = new Player();

	cout << "----------------------- First Meld ------------------------------\n";

	tiles.clear();
	tiles.push_back(new NormalTile("black", 9, 0));
	tiles.push_back(new NormalTile("red", 9, 0));
	tiles.push_back(new NormalTile("yellow", 9, 0));
	form.push_back(new Formation(tiles));
	player1->playerboard->addtoBoard(tiles);

	tiles.clear();
	tiles.push_back(new NormalTile("red", 7, 0));
	tiles.push_back(new NormalTile("red", 8, 0));
	tiles.push_back(new NormalTile("red", 9, 0));
	form.push_back(new Formation(tiles));
	player1->playerboard->addtoBoard(tiles);

	tiles.clear();
	tiles.push_back(new NormalTile("yellow", 2, 0));
	tiles.push_back(new NormalTile("yellow", 3, 0));
	tiles.push_back(new NormalTile("yellow", 4, 0));
	form.push_back(new Formation(tiles));
	player1->playerboard->addtoBoard(tiles);

	for (const auto& f : form)
	{

		f->displayFormationinfo();
		cout << endl;
	}

	if (Game::checkfirstmeld(form))
	{
		cout << "valid first meld\n";
	}
	else
	{
		cout << "not a valid first meld\n";
	}
	player1->playerboard->displayBoardinfo();
	player1->FirstMeld(form);
	player1->playerboard->displayBoardinfo();
	player1->displayPlayerinfo();

	cout << endl << " --------------------------------" << endl;
	form.clear();
	player1->ResetPlayer();
	

	tiles.clear();
	tiles.push_back(new NormalTile("red", 7, 0));
	tiles.push_back(new NormalTile("red", 8, 0));
	tiles.push_back(new NormalTile("red", 9, 0));
	form.push_back(new Formation(tiles));
	player1->playerboard->addtoBoard(tiles);

	tiles.clear();
	tiles.push_back(new NormalTile("red", 12, 0));
	tiles.push_back(new NormalTile("black", 12, 0));
	tiles.push_back(new NormalTile("blue", 12, 0));
	form.push_back(new Formation(tiles));
	player1->playerboard->addtoBoard(tiles);

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}

	if (Game::checkfirstmeld(form))
	{
		cout << "valid first meld\n";
	}
	else
	{
		cout << "not a valid first meld\n";
	}
	player1->playerboard->displayBoardinfo();
	player1->FirstMeld(form);
	player1->playerboard->displayBoardinfo();
	player1->displayPlayerinfo();

	cout << endl << " --------------------------------" << endl;
	form.clear();
	player1->ResetPlayer();

	tiles.clear();
	tiles.push_back(new NormalTile("yellow", 9, 0));
	tiles.push_back(new NormalTile("yellow", 10, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("yellow", 12, 0));
	form.push_back(new Formation(tiles));
	player1->playerboard->addtoBoard(tiles);

	tiles.clear();
	tiles.push_back(new NormalTile("red", 9, 0));
	tiles.push_back(new NormalTile("black", 9, 0));
	tiles.push_back(new NormalTile("blue", 9, 0));
	form.push_back(new Formation(tiles));
	player1->playerboard->addtoBoard(tiles);

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}

	if (Game::checkfirstmeld(form))
	{
		cout << "valid first meld\n";
	}
	else
	{
		cout << "not a valid first meld\n";
	}

	player1->playerboard->displayBoardinfo();
	player1->FirstMeld(form);
	player1->playerboard->displayBoardinfo();
	player1->displayPlayerinfo();
	cout << endl << " --------------------------------" << endl;
	form.clear();
	player1->ResetPlayer();

	tiles.clear();
	tiles.push_back(new NormalTile("yellow", 2, 0));
	tiles.push_back(new NormalTile("yellow", 3, 0));
	tiles.push_back(new NormalTile("yellow", 4, 0));
	form.push_back(new Formation(tiles));
	player1->playerboard->addtoBoard(tiles);

	tiles.clear();
	tiles.push_back(new NormalTile("red", 9, 0));
	tiles.push_back(new NormalTile("black", 9, 0));
	tiles.push_back(new NormalTile("blue", 9, 0));
	tiles.push_back(new NormalTile("yellow", 9, 0));
	form.push_back(new Formation(tiles));
	player1->playerboard->addtoBoard(tiles);

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}

	if (Game::checkfirstmeld(form))
	{
		cout << "valid first meld\n";
	}
	else
	{
		cout << "not a valid first meld\n";
	}

	player1->playerboard->displayBoardinfo();
	player1->FirstMeld(form);
	player1->playerboard->displayBoardinfo();
	player1->displayPlayerinfo();
	cout << endl << " --------------------------------" << endl;
	form.clear();
	player1->ResetPlayer();

	tiles.clear();
	tiles.push_back(new NormalTile("yellow", 1, 0));
	tiles.push_back(new NormalTile("yellow", 2, 0));
	tiles.push_back(new NormalTile("yellow", 3, 0));
	form.push_back(new Formation(tiles));
	player1->playerboard->addtoBoard(tiles);

	tiles.clear();
	tiles.push_back(new NormalTile("red", 9, 0));
	tiles.push_back(new NormalTile("black", 9, 0));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new NormalTile("yellow", 9, 0));
	form.push_back(new Formation(tiles));
	player1->playerboard->addtoBoard(tiles);

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}

	if (Game::checkfirstmeld(form))
	{
		cout << "valid first meld\n";
	}
	else
	{
		cout << "not a valid first meld\n";
	}
	player1->playerboard->displayBoardinfo();
	player1->FirstMeld(form);
	player1->playerboard->displayBoardinfo();
	player1->displayPlayerinfo();
	cout << endl << " --------------------------------" << endl;
	form.clear();
	player1->ResetPlayer();

	tiles.clear();
	tiles.push_back(new NormalTile("yellow", 2, 0));
	tiles.push_back(new NormalTile("yellow", 3, 0));
	tiles.push_back(new NormalTile("yellow", 4, 0));
	form.push_back(new Formation(tiles));
	player1->playerboard->addtoBoard(tiles);

	tiles.clear();
	tiles.push_back(new NormalTile("blue", 11, 0));
	tiles.push_back(new NormalTile("blue", 12, 0));
	tiles.push_back(new NormalTile("blue", 13, 0));
	form.push_back(new Formation(tiles));
	player1->playerboard->addtoBoard(tiles);

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}

	if (Game::checkfirstmeld(form))
	{
		cout << "valid first meld\n";
	}
	else
	{
		cout << "not a valid first meld\n";
	}
	player1->playerboard->displayBoardinfo();
	player1->FirstMeld(form);
	player1->playerboard->displayBoardinfo();
	player1->displayPlayerinfo();
	cout << endl << " --------------------------------" << endl;
	form.clear();
	player1->ResetPlayer();

	tiles.clear();
	tiles.push_back(new NormalTile("red", 9, 0));
	tiles.push_back(new NormalTile("black", 9, 0));
	tiles.push_back(new NormalTile("yellow", 9, 0));
	form.push_back(new Formation(tiles));
	player1->playerboard->addtoBoard(tiles);

	tiles.clear();
	tiles.push_back(new NormalTile("red", 12, 0));
	tiles.push_back(new NormalTile("black", 12, 0));
	tiles.push_back(new NormalTile("blue", 12, 0));
	form.push_back(new Formation(tiles));
	player1->playerboard->addtoBoard(tiles);

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}

	if (Game::checkfirstmeld(form))
	{
		cout << "valid first meld\n";
	}
	else
	{
		cout << "not a valid first meld\n";
	}
	player1->playerboard->displayBoardinfo();
	player1->FirstMeld(form);
	player1->playerboard->displayBoardinfo();
	player1->displayPlayerinfo();
	cout << endl << " --------------------------------" << endl;
	form.clear();
	player1->ResetPlayer();
}

void testfirstmeldbreakingame()
{
	Game game;
	vector <Tile*> alltiles = Tile::CreateTiles();
	vector <Player*> players = Player::InitialiseNPlayers(2);


	// ONE RUN: 
	vector <vector <Tile*>> stacks = Tile::CreateStacks(alltiles);
	Tile::DisplayStacks(stacks);
	vector <Tile*> stackqueue;

	vector<Tile*> tiles;

	tiles.clear();
	tiles.push_back(new NormalTile("black", 10,	1));
	tiles.push_back(new NormalTile("yellow", 10, 1));
	tiles.push_back(new NormalTile("red", 10, 1));
	tiles.push_back(new NormalTile("blue", 10, 1));
	tiles.push_back(new NormalTile("black", 11, 2));
	tiles.push_back(new NormalTile("black", 12, 2));
	tiles.push_back(new NormalTile("yellow", 13, 1));
	tiles.push_back(new NormalTile("black", 13, 1));
	tiles.push_back(new NormalTile("blue", 13, 1));
	tiles.push_back(new NormalTile("red", 13, 1));
	tiles.push_back(new NormalTile("blue", 5, 1));
	tiles.push_back(new NormalTile("red", 7, 1));
	tiles.push_back(new NormalTile("yellow", 2, 1));
	tiles.push_back(new NormalTile("red", 4, 1));
	tiles.push_back(new NormalTile("blue", 11, 1));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new JokerTile(1));


	players[0]->playerboard->addtoBoard(tiles);

	players[0]->firstmeld = true;
	

	vector<Tile*> tilez;
	tilez.push_back(new NormalTile("black", 11, 2));
	tilez.push_back(new NormalTile("black", 12, 2));
	tilez.push_back(new NormalTile("black", 13, 1));

	players[0]->formations.push_back(new Formation(tilez));
	tilez.clear();

	tilez.push_back(new NormalTile("red", 13, 2));
	tilez.push_back(new NormalTile("blue", 13, 2));
	tilez.push_back(new NormalTile("yellow", 13, 1));
	
	players[0]->formations.push_back(new Formation(tilez));
	tilez.clear();

	players[0]->formations[0]->melded = true;
	players[0]->formations[1]->melded = true;

	tilez.push_back(new JokerTile(2));
	tilez.push_back(new NormalTile("black", 12, 2));
	tilez.push_back(new NormalTile("black", 13, 1));

	players[0]->formations.push_back(new Formation(tilez));
	tilez.clear();

	tilez.push_back(new JokerTile(2));
	tilez.push_back(new NormalTile("black", 13, 2));
	tilez.push_back(new NormalTile("yellow", 13, 1));

	players[0]->formations.push_back(new Formation(tilez));
	tilez.clear();


	players[0]->formations[2]->melded = true;
	players[0]->formations[3]->melded = true;



	tiles.clear();
	tiles.push_back(new NormalTile("red", 9, 1));
	tiles.push_back(new NormalTile("blue", 9, 2));
	tiles.push_back(new NormalTile("yellow", 6, 1));
	tiles.push_back(new NormalTile("black", 10, 2));
	tiles.push_back(new NormalTile("black", 13, 2));
	tiles.push_back(new NormalTile("red", 5, 2));
	tiles.push_back(new NormalTile("black", 12, 2));
	
	

	players[1]->playerboard->addtoBoard(tiles);

	tilez.push_back(new JokerTile(2));
	tilez.push_back(new NormalTile("black", 13, 2));
	tilez.push_back(new NormalTile("yellow", 13, 1));

	players[1]->formations.push_back(new Formation(tilez));
	tilez.clear();
	players[1]->formations[0]->melded = true;
	players[1]->firstmeld = true;

	tiles.clear();
	tiles.push_back(new NormalTile("red", 9, 1));
	tiles.push_back(new NormalTile("blue", 9, 2));
	tiles.push_back(new NormalTile("yellow", 6, 1));
	tiles.push_back(new NormalTile("yellow", 10, 1));
	tiles.push_back(new NormalTile("black", 10, 1));
	tiles.push_back(new NormalTile("black", 10, 2));
	tiles.push_back(new NormalTile("red", 10, 1));
	tiles.push_back(new NormalTile("blue", 10, 1));
	tiles.push_back(new NormalTile("black", 9, 1));
	tiles.push_back(new NormalTile("black", 11, 2));
	tiles.push_back(new NormalTile("black", 12, 2));
	tiles.push_back(new NormalTile("yellow", 13, 1));
	tiles.push_back(new NormalTile("blue", 13, 1));
	tiles.push_back(new NormalTile("red", 13, 1));


	for (const auto& t : tiles)
	{
		stackqueue.push_back(t);
	}


	// vector <Tile*> stackqueue = game.DivideStacks(stacks, alltiles, players);
	vector <Tile*> queue;

	// Player::DisplayPlayers(players);
	cout << endl;
	cout << "Stacks queue:" << endl;
	Tile::DisplayTiles(stackqueue); cout << endl;
	game.Match(players, stackqueue, alltiles, queue);
}

void testpreset() 
{
	Game game;
	vector <Tile*> alltiles = Tile::CreateTiles();
	vector <Player*> players = Player::InitialiseNPlayers(2);


	// ONE RUN: 
	vector <vector <Tile*>> stacks = Tile::CreateStacks(alltiles);
	Tile::DisplayStacks(stacks);
	vector <Tile*> stackqueue;

	vector<Tile*> tiles;

	tiles.clear();
	tiles.push_back(new NormalTile("black", 10, 1));
	tiles.push_back(new NormalTile("yellow", 10, 1));
	tiles.push_back(new NormalTile("red", 10, 1));
	tiles.push_back(new NormalTile("blue", 10, 1));
	tiles.push_back(new NormalTile("black", 11, 2));
	tiles.push_back(new NormalTile("black", 12, 2));
	tiles.push_back(new NormalTile("yellow", 13, 1));
	tiles.push_back(new NormalTile("black", 13, 1));
	tiles.push_back(new NormalTile("blue", 13, 1));
	tiles.push_back(new NormalTile("red", 13, 1));
	tiles.push_back(new NormalTile("blue", 5, 1));
	tiles.push_back(new NormalTile("red", 7, 1));
	tiles.push_back(new NormalTile("yellow", 2, 1));
	tiles.push_back(new NormalTile("red", 4, 1));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new JokerTile(1));


	players[0]->playerboard->addtoBoard(tiles);

	players[0]->firstmeld = true;

	vector<Tile*> tilez;
	tilez.push_back(new NormalTile("black", 11, 2));
	tilez.push_back(new NormalTile("black", 12, 2));
	tilez.push_back(new NormalTile("black", 13, 1));

	players[0]->formations.push_back(new Formation(tilez));
	tilez.clear();

	tilez.push_back(new NormalTile("red", 13, 2));
	tilez.push_back(new NormalTile("blue", 13, 2));
	tilez.push_back(new NormalTile("yellow", 13, 1));

	players[0]->formations.push_back(new Formation(tilez));
	tilez.clear();

	players[0]->formations[0]->melded = true;
	players[0]->formations[1]->melded = true;

	tilez.push_back(new JokerTile(2));
	tilez.push_back(new NormalTile("black", 12, 2));
	tilez.push_back(new NormalTile("black", 13, 1));

	players[0]->formations.push_back(new Formation(tilez));
	tilez.clear();

	tilez.push_back(new JokerTile(2));
	tilez.push_back(new NormalTile("blue", 13, 2));
	tilez.push_back(new NormalTile("yellow", 13, 1));

	players[0]->formations.push_back(new Formation(tilez));

	players[0]->formations[2]->melded = true;
	players[0]->formations[3]->melded = true;



	tiles.clear();
	tiles.push_back(new NormalTile("red", 9, 1));
	tiles.push_back(new NormalTile("blue", 9, 2));
	tiles.push_back(new NormalTile("yellow", 6, 1));
	tiles.push_back(new NormalTile("black", 10, 2));
	tiles.push_back(new NormalTile("black", 13, 2));
	tiles.push_back(new NormalTile("red", 5, 2));
	tiles.push_back(new NormalTile("black", 12, 2));



	players[1]->playerboard->addtoBoard(tiles);

	tiles.clear();
	tiles.push_back(new NormalTile("red", 9, 1));
	tiles.push_back(new NormalTile("blue", 9, 2));
	tiles.push_back(new NormalTile("yellow", 6, 1));
	tiles.push_back(new NormalTile("yellow", 10, 1));
	tiles.push_back(new NormalTile("black", 10, 1));
	tiles.push_back(new NormalTile("black", 10, 2));
	tiles.push_back(new NormalTile("red", 10, 1));
	tiles.push_back(new NormalTile("blue", 10, 1));
	tiles.push_back(new NormalTile("black", 9, 1));
	tiles.push_back(new NormalTile("black", 11, 2));
	tiles.push_back(new NormalTile("black", 12, 2));
	tiles.push_back(new NormalTile("yellow", 13, 1));
	tiles.push_back(new NormalTile("blue", 13, 1));
	tiles.push_back(new NormalTile("red", 13, 1));


	for (const auto& t : tiles)
	{
		stackqueue.push_back(t);
	}


	// vector <Tile*> stackqueue = game.DivideStacks(stacks, alltiles, players);
	vector <Tile*> queue;

	// Player::DisplayPlayers(players);
	cout << endl;
	cout << "Stacks queue:" << endl;
	Tile::DisplayTiles(stackqueue); cout << endl;
	game.Match(players, stackqueue, alltiles, queue);



	// SECOND RUN: 
	alltiles = Tile::CreateTiles();
	stacks = Tile::CreateStacks(alltiles);
	Tile::DisplayStacks(stacks);
	

	tiles.clear();
	tiles.push_back(new NormalTile("black", 10, 1));
	tiles.push_back(new NormalTile("yellow", 10, 1));
	tiles.push_back(new NormalTile("red", 10, 1));
	tiles.push_back(new NormalTile("blue", 10, 1));
	tiles.push_back(new NormalTile("black", 11, 2));
	tiles.push_back(new NormalTile("black", 12, 2));
	tiles.push_back(new NormalTile("yellow", 13, 1));
	tiles.push_back(new NormalTile("black", 13, 1));
	tiles.push_back(new NormalTile("blue", 13, 1));
	tiles.push_back(new NormalTile("red", 13, 1));
	tiles.push_back(new NormalTile("blue", 5, 1));
	tiles.push_back(new NormalTile("red", 7, 1));
	tiles.push_back(new NormalTile("yellow", 2, 1));
	tiles.push_back(new NormalTile("red", 4, 1));
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new JokerTile(1));


	players[0]->playerboard->addtoBoard(tiles);

	players[0]->firstmeld = true;

	
	tilez.push_back(new NormalTile("black", 11, 2));
	tilez.push_back(new NormalTile("black", 12, 2));
	tilez.push_back(new NormalTile("black", 13, 1));

	players[0]->formations.push_back(new Formation(tilez));
	tilez.clear();

	tilez.push_back(new NormalTile("red", 13, 2));
	tilez.push_back(new NormalTile("blue", 13, 2));
	tilez.push_back(new NormalTile("yellow", 13, 1));

	players[0]->formations.push_back(new Formation(tilez));
	tilez.clear();

	players[0]->formations[0]->melded = true;
	players[0]->formations[1]->melded = true;

	tilez.push_back(new JokerTile(2));
	tilez.push_back(new NormalTile("black", 12, 2));
	tilez.push_back(new NormalTile("black", 13, 1));

	players[0]->formations.push_back(new Formation(tilez));
	tilez.clear();

	tilez.push_back(new JokerTile(2));
	tilez.push_back(new NormalTile("blue", 13, 2));
	tilez.push_back(new NormalTile("yellow", 13, 1));

	players[0]->formations.push_back(new Formation(tilez));

	players[0]->formations[2]->melded = true;
	players[0]->formations[3]->melded = true;



	tiles.clear();
	tiles.push_back(new NormalTile("red", 9, 1));
	tiles.push_back(new NormalTile("blue", 9, 2));
	tiles.push_back(new NormalTile("yellow", 6, 1));
	tiles.push_back(new NormalTile("black", 10, 2));
	tiles.push_back(new NormalTile("black", 13, 2));
	tiles.push_back(new NormalTile("red", 5, 2));
	tiles.push_back(new NormalTile("black", 12, 2));



	players[1]->playerboard->addtoBoard(tiles);

	tiles.clear();
	tiles.push_back(new NormalTile("red", 9, 1));
	tiles.push_back(new NormalTile("blue", 9, 2));
	tiles.push_back(new NormalTile("yellow", 6, 1));
	tiles.push_back(new NormalTile("yellow", 10, 1));
	tiles.push_back(new NormalTile("black", 10, 1));
	tiles.push_back(new NormalTile("black", 10, 2));
	tiles.push_back(new NormalTile("red", 10, 1));
	tiles.push_back(new NormalTile("blue", 10, 1));
	tiles.push_back(new NormalTile("black", 9, 1));
	tiles.push_back(new NormalTile("black", 11, 2));
	tiles.push_back(new NormalTile("black", 12, 2));
	tiles.push_back(new NormalTile("yellow", 13, 1));
	tiles.push_back(new NormalTile("blue", 13, 1));
	tiles.push_back(new NormalTile("red", 13, 1));


	for (const auto& t : tiles)
	{
		stackqueue.push_back(t);
	}


	// vector <Tile*> stackqueue = game.DivideStacks(stacks, alltiles, players);
	

	// Player::DisplayPlayers(players);
	cout << endl;
	cout << "Stacks queue:" << endl;
	Tile::DisplayTiles(stackqueue); cout << endl;
	game.Match(players, stackqueue, alltiles, queue);

	game.Match(players, stackqueue, alltiles, queue);
}

#endif