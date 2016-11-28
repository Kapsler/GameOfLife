#pragma once
#include <vector>
#include <iostream>
#include <CL/cl.hpp>
#include "TimerClass.h"
#include <fstream>

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
	char CheckCell(const int &line, const int &row) const;
private:
	//1D
	int inline CountNeighbors(const int &line, const int &row) const;
	void inline ToggleCell(const int &line, const int &row);

	void InitOCL();
	string GetKernelCode(string inputFilename);

	TimerClass timer;
	vector<char> board;
	int lines, rows;
	char* changes;

	cl::Buffer input, output, rowbuffer, linebuffer;
	cl::Kernel kernel_simulation;
	cl::CommandQueue queue_simulation;
};
