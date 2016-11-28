#pragma once
#include <vector>
#include <iostream>
#include <CL/cl.hpp>
#include "TimerClass.h"

using namespace std;

class LifeSimulation
{
public:
	LifeSimulation();
	~LifeSimulation();

	vector<vector<char>>* getBoardPtr();

	string Run(int generations, string mode);
	void SimulateLifeIteration();
	void SimulateLifeOMP();
	void SimulateLifeOCL();
	bool CheckCell(const int &line, const int &row) const;
	void DebugOutput();

private:
	int inline CountNeighbors(const int &line, const int &row) const;
	int inline mod(int first, const int &second) const;
	void inline ToggleCell(const int &line, const int &row);

	void InitOCL();

	vector<vector<char>> board;
	int lines, rows;
	bool** changes;

	TimerClass timer;
};
