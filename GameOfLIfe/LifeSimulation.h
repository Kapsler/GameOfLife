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

	string Run(int generations, string mode, int threadnum, string devicetype, int devicenum, int platformnum);
	void SimulateLifeIteration();
	void SimulateLifeOMP(int threadnum);
	void SimulateLifeOCL();
	void DebugOutput();

private:
	char CheckCell(const int &line, const int &row) const;
	int inline CountNeighbors(const int &line, const int &row) const;
	void inline ToggleCell(const int &line, const int &row);

	void InitOCL(string devicetype, int devicenum, int platformnum);
	string GetKernelCode(string inputFilename);

	TimerClass timer;
	vector<char> board;
	int lines, rows;
	char* changes;

	cl::Buffer input, output, linebuffer, rowbuffer;
	cl::Kernel kernel_simulation;
	cl::CommandQueue queue_simulation;
	cl::NDRange global, local, offset;

	int inline pow2roundup(int x);
};
