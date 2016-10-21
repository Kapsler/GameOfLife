#pragma once
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

class InputReader
{
public:
	InputReader(string inputFilename,
		vector<vector<char>> *board);
	~InputReader();

	int numberOfLines, lineLength;
private:
	void extractValuesFromContent(vector<vector<char>> *board);
	void readInputFile(string inputFilename);

	string content;
	//vector<vector<char>> board;
	vector<char> line;
};
