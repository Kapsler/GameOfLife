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
	const bool CheckCell(const int &line, const int &row) const;
	void DebugOutput();

private:
	const int CountNeighbors(const int &line, const int &row) const;
	const int inline mod(const int &first, const int &second) const;
	void ToggleCell(const int &line, const int &row);

	vector<vector<char>> board;
	int lines, rows;

};
