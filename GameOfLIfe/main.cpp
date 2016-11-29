
#define __CL_ENABLE_EXCEPTIONS
#include "CommandLineParser.h"
#include <iostream>
#include "LifeSimulation.h"
#include "ReaderWriter.h"
#include "TimerClass.h"

using namespace std;

double timed1, timed2, timed3;
string inputFilename, outputFilename, time1, time2, time3, mode, devicetype;
int generations, threadnum, devicenum, platformnum;
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

	}
	
	if (input.cmdOptionExists("--mode"))
	{
		mode = input.getCmdOption("--mode");
	}
	else
	{
		cerr << "Parameter --mode not found!" << endl;
		return false;
	}  

	if(mode == "omp")
	{
		if (input.cmdOptionExists("--threads"))
		{
			threadnum = stoi(input.getCmdOption("--threads"));
		}
		else
		{
			cerr << "Parameter --threads not found!" << endl;
			return false;
		}
	}

	if(mode == "ocl")
	{
		if (input.cmdOptionExists("--device"))
		{
			devicetype = input.getCmdOption("--device");
		}
		else
		{
			if (input.cmdOptionExists("--deviceId"))
			{
				devicenum = stoi(input.getCmdOption("--deviceId"));
			}
			else
			{
				cerr << "Parameter --deviceId not found!" << endl;
				return false;
			}

			if (input.cmdOptionExists("--platformId"))
			{
				platformnum = stoi(input.getCmdOption("--platformId"));
			}
			else
			{
				cerr << "Parameter --platformId not found!" << endl;
				return false;
			}
		}


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
	ReaderWriter* readerwriter = new ReaderWriter(inputFilename, simulation->getBoardPtr(), simulation->GetLinesPtr(), simulation->GetRowsPtr());
	//time1 = timer->GetFormattedDuration("");
	timed1 = timer->GetTime();

	//Run
	timer->StartTimer();
	time2 = simulation->Run(generations, mode, threadnum, devicetype, devicenum, platformnum);
	timed2 = timer->GetTime();

	//Output
	timer->StartTimer();
	readerwriter->WriteToFile(outputFilename, simulation->getBoardPtr());
	//time3 = timer->GetFormattedDuration("");
	timed3 = timer->GetTime();

	//Free Stuff
	delete readerwriter;
	delete simulation;
	delete timer;

	//if (measure) cout << time1 << " " << time2 << " " << time3 << endl;
	if (measure) cout << timer->FormatTime(timed1 + timed2 + timed3) << endl;

	return 0;
}
