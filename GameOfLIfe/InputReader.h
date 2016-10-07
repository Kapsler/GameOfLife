#pragma once
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

class InputReader
{
public:
	InputReader(string inputFilename);
	~InputReader();

	vector<vector<bool>> getBoard();

	int numberOfLines, lineLength;
private:
	void extractValuesFromContent();
	void readInputFile(string inputFilename);

	string content;
	vector<vector<bool>> board;
	vector<bool> line;
};
