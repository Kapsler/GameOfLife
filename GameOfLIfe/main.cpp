#include "CommandLineParser.h"
#include <iostream>
#include "LifeSimulation.h"
#include "ReaderWriter.h"
#include "TimerClass.h"

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

	//Init stuff
	TimerClass* timer = new TimerClass();
	LifeSimulation* simulation = new LifeSimulation();

	//Read Input
	timer->StartTimer();
	ReaderWriter* readerwriter = new ReaderWriter(inputFilename, simulation->getBoardPtr());
	cout << "Reading from File took " << timer->GetTime() << " seconds." << endl;


	//DebugOutput
	//simulation->DebugOutput();

	//Run
	timer->StartTimer();
	simulation->Run(generations);
	cout << "Running " << generations << " generations took " << timer->GetTime() << " seconds." << endl;

	//DebugOutput
	//simulation->DebugOutput();

	//Output
	timer->StartTimer();
	readerwriter->WriteToFile(outputFilename, simulation->getBoardPtr());
	cout << "Writing to File took " << timer->GetTime() << " seconds." << endl;

	//Free Stuff
	delete readerwriter;
	delete simulation;
	delete timer;

	return 0;
}
