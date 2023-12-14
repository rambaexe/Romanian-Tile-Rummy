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

	for (const auto& f : form)
	{
		f->displayFormationinfo();
		cout << endl;
	}
	form.clear();


}

#endif