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
		vector<char> *board, int* linesptr, int* rowsptr);
	~ReaderWriter();

	void WriteToFile(string outputFilename, vector<char> *board);

private:
	void extractValuesFromContent(vector<char> *board);
	void readInputFile(string inputFilename);

	string content;

	int *lines, *rows;

};
