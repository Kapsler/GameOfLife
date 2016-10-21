#include "CommandLineParser.h"
#include <iostream>
#include "InputReader.h"
#include "LifeSimulation.h"

using namespace std;

string inputFilename, outputFilename;
int generations;

bool handleParameters(int argc, char* argv[])
{
	CommandLineParser input(argc, argv);

	if (input.cmdOptionExists("--load"))
	{
		inputFilename = input.getCmdOption("--load");
	}
	else
	{
		cerr << "Parameter --load not found!" << endl;
		return false;
	}

	if (input.cmdOptionExists("--save"))
	{
		outputFilename = input.getCmdOption("--save");
	}
	else
	{
		cerr << "Parameter --save not found!" << endl;
		return false;
	}

	if (input.cmdOptionExists("--generations"))
	{
		generations = stoi(input.getCmdOption("--generations"));
	}
	else
	{
		cerr << "Parameter --generations not found!" << endl;
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	
	if(!handleParameters(argc, argv))
	{
		return -1;
	}

	//Init stuff & Input
	LifeSimulation* simulation = new LifeSimulation();
	InputReader* reader = new InputReader(inputFilename, simulation->getBoardPtr());

	//DebugOutput
	//simulation->DebugOutput();

	//Run
	simulation->Run(1);

	//DebugOutput
	//simulation->DebugOutput();

	//Output

	//Free Stuff
	delete reader;
	delete simulation;

	return 0;
}
