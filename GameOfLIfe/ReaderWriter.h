#pragma once
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

class ReaderWriter
{
public:
	ReaderWriter(string inputFilename,
		vector<vector<char>> *board);
	~ReaderWriter();

	static void WriteToFile(string outputFilename, vector<vector<char>> *board);

	int numberOfLines, lineLength;
private:
	void extractValuesFromContent(vector<vector<char>> *board);
	void readInputFile(string inputFilename);

	string content;
	vector<char> line;
};
