#pragma once
#include <vector>
#include <iostream>

using namespace std;

class LifeSimulation
{
public:
	LifeSimulation();
	~LifeSimulation();

	vector<char>* getBoardPtr();
	int* GetLinesPtr();
	int* GetRowsPtr();

	void Run(int generations);
	void DebugOutput();

	//1D
	void SimulateLifeIteration();
	bool CheckCell(const int &line, const int &row) const;
private:
	//1D
	int inline CountNeighbors(const int &line, const int &row) const;
	void inline ToggleCell(const int &line, const int &row);

	vector<char> board1d;
	int lines, rows;
	bool* changes1d;
};
