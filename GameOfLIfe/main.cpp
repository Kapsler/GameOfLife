#include "CommandLineParser.h"
#include <iostream>
#include "LifeSimulation.h"
#include "ReaderWriter.h"
#include "TimerClass.h"

using namespace std;

string inputFilename, outputFilename, time1, time2, time3, mode;
int generations;
bool measure;

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

	}if (input.cmdOptionExists("--mode"))
	{
		mode = input.getCmdOption("--mode");
	}
	else
	{
		cerr << "Parameter --mode not found!" << endl;
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

	if (input.cmdOptionExists("--measure"))
	{
		measure = true;;
	}
	else
	{
		measure = false;
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
	time1 = timer->GetFormattedDuration("");


	//DebugOutput
	//simulation->DebugOutput();

	//Run
	timer->StartTimer();
	cout << mode << endl;
	time2 = simulation->Run(generations, mode);

	//DebugOutput
	//simulation->DebugOutput();

	//Output
	timer->StartTimer();
	readerwriter->WriteToFile(outputFilename, simulation->getBoardPtr());

	//Free Stuff
	delete readerwriter;
	delete simulation;
	delete timer;
	time3 = timer->GetFormattedDuration("");

	if (measure) cout << time1 << " " << time2 << " " << time3 << endl;

	return 0;
}
