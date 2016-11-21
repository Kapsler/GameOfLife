#pragma once
#include <vector>
#include <iostream>

using namespace std;

class LifeSimulation
{
public:
	LifeSimulation();
	~LifeSimulation();

	vector<vector<char>>* getBoardPtr();

	void Run(int generations);
	void SimulateLifeIteration();
	void SimulateLifeOMP();
	bool CheckCell(const int &line, const int &row) const;
	void DebugOutput();

private:
	int inline CountNeighbors(const int &line, const int &row) const;
	int inline mod(int first, const int &second) const;
	void inline ToggleCell(const int &line, const int &row);

	vector<vector<char>> board;
	int lines, rows;
	bool** changes;
};
