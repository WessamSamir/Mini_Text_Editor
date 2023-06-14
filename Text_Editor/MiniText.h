#pragma once
#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <utility>

using namespace std;

class MiniText
{
	map<int, string>Lines;
	stack<pair<int, pair<int, string>>>undostack;
	int numline;
	int Count;
	string input;

public:
	
	MiniText();
	MiniText(int numline, string input);
	void open();
	void close();
	void add();
	void insert();
	void Delete();
	void update();
	void Find();
	void DeleteRange();
	void Replace();
	void getLine();
	void show();
	void undo();
};

