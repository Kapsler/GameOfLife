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

	vector<char>* getBoardPtr();
	int* GetLinesPtr();
	int* GetRowsPtr();

	string Run(int generations, string mode);
	void SimulateLifeOMP();
	void SimulateLifeOCL();
	void DebugOutput();

	//1D
	void SimulateLifeIteration();
	bool CheckCell(const int &line, const int &row) const;
private:
	//1D
	int inline CountNeighbors(const int &line, const int &row) const;
	void inline ToggleCell(const int &line, const int &row);

	void InitOCL();

	TimerClass timer;
	vector<char> board;
	int lines, rows;
	bool* changes;
};
