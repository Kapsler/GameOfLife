#include "LifeSimulation.h"

LifeSimulation::LifeSimulation()
{
	lines = 0;
	rows = 0;
	changes = nullptr;
}

LifeSimulation::~LifeSimulation()
{
}

vector<char>* LifeSimulation::getBoardPtr()
{
	return &board;
}

int* LifeSimulation::GetLinesPtr()
{
	return &lines;
}

int* LifeSimulation::GetRowsPtr()
{	
	return &rows;
}

string LifeSimulation::Run(int generations, std::string mode)
{
	string time = "";
	changes = new char[board.size()];

	if (mode == "seq")
	{
		timer.StartTimer();
		for (auto i = 0; i < generations; ++i)
		{
			SimulateLifeIteration();
		}
		time = timer.GetFormattedDuration("");
	} else if(mode == "omp")
	{
		timer.StartTimer();
		for (auto i = 0; i < generations; ++i)
		{
			SimulateLifeOMP();
		}
		time = timer.GetFormattedDuration("");
		
	} else if(mode == "ocl")
	{

		timer.StartTimer();
		InitOCL();

		for (auto i = 0; i < generations; ++i)
		{
			SimulateLifeOCL();
		}

		queue_simulation.enqueueReadBuffer(output, CL_TRUE, 0, sizeof(char) * board.size(), &board[0]);
		queue_simulation.finish();

		time = timer.GetFormattedDuration("");
	} else
	{
		std::cerr << mode.c_str() << " is not a valid mode!" << endl;
		exit(0);
	}	

	delete[] changes;

	return time;
}

void LifeSimulation::SimulateLifeOMP()
{
	#pragma omp parallel num_threads(4)
	{
		#pragma omp for
		for (auto i = 0; i < lines; ++i)
		{
			for (auto j = 0; j < rows; ++j)
			{
				changes[i * rows + j] = CheckCell(i, j);
			}

		}

		#pragma omp for
		for (auto i = 0; i < lines; ++i)
		{
			for (auto j = 0; j < rows; ++j)
			{
				board[i * rows + j] = changes[i * rows + j];
			}

		}

	}
	
}

void LifeSimulation::SimulateLifeIteration()
{

	for (auto i = 0; i < lines; ++i)
	{
		for (auto j = 0; j < rows; ++j)
		{
			changes[i * rows + j] = CheckCell(i, j);
		}

	}

	for (auto i = 0; i < lines; ++i)
	{
		for (auto j = 0; j < rows; ++j)
		{
			board[i * rows + j] = changes[i * rows + j];
		}

	}
}

void LifeSimulation::SimulateLifeOCL()
{
	if(queue_simulation.enqueueNDRangeKernel(kernel_simulation, cl::NullRange, cl::NDRange(lines, rows), cl::NullRange) != CL_SUCCESS)
	{
		cout << "ERROR!" << endl;
	};
	queue_simulation.enqueueCopyBuffer(output, input, 0, 0, sizeof(char)*board.size());
	//queue_simulation.enqueueReadBuffer(output, CL_TRUE, 0, sizeof(char) * board.size(), &board[0]);
	//queue_simulation.enqueueWriteBuffer(input, CL_TRUE, 0, sizeof(char) * board.size(), &board[0]);
	queue_simulation.finish();
	//std::swap(input, output);

}

char LifeSimulation::CheckCell(const int& line, const int& row) const
{
	const int neighbors = CountNeighbors(line, row);

	//Alive
	if (board[line * rows + row] == 'x')
	{
		if (neighbors >= 4 || neighbors <= 1)
		{
			return '.';
		}

		return 'x';
	}
	//Dead
	else
	{
		if (neighbors == 3)
		{
			return 'x';
		}

		return '.';
	}

}

int LifeSimulation::CountNeighbors(const int& line, const int& row) const
{
	int neighborcount = 0;
	int lineafter = line + 1;
	int linebefore = line - 1;
	int rowafter = row + 1;
	int rowbefore = row - 1;


	if (rowafter >= rows)
	{
		//rowafter = mod(row + 1, rows);
		rowafter = 0;
	}
	if (rowbefore < 0)
	{
		//rowbefore = mod(row - 1, rows);
		rowbefore = rows - 1;
	}
	if (lineafter >= lines)
	{
		//lineafter = mod(line + 1, lines);
		lineafter = 0;
	}
	if (linebefore < 0)
	{
		//linebefore = mod(line - 1, lines);
		linebefore = lines - 1;
	}

	//X__
	//___
	//___
	if (board[linebefore * rows + rowbefore] == 'x') neighborcount++;
	//_X_
	//___
	//___
	if (board[linebefore * rows + row] == 'x') neighborcount++;
	//__X
	//___
	//___
	if (board[linebefore * rows + rowafter] == 'x') neighborcount++;
	//___
	//X__
	//___
	if (board[line * rows + rowbefore] == 'x') neighborcount++;
	//___
	//__X
	//___
	if (board[line * rows + rowafter] == 'x') neighborcount++;
	//___
	//___
	//X__
	if (board[lineafter * rows + rowbefore] == 'x') neighborcount++;
	//___
	//___
	//_X_
	if (board[lineafter * rows + row] == 'x') neighborcount++;
	//___
	//___
	//__X
	if (board[lineafter * rows + rowafter] == 'x') neighborcount++;

	return neighborcount;
}

void LifeSimulation::ToggleCell(const int& line, const int& row)
{
	if (board[line * rows + row] == 'x')
	{
		board[line * rows + row] = '.';
	}
	else
	{
		board[line * rows + row] = 'x';
	}
}

void LifeSimulation::InitOCL()
{
	//get all platforms (drivers)
	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);
	if (all_platforms.size() == 0) {
		std::cout << " No platforms found. Check OpenCL installation!\n";
		exit(1);
	}

	//TODO Needs device parameter!
	cl::Platform default_platform = all_platforms[1];
	std::cout << "Using platform: " << default_platform.getInfo<CL_PLATFORM_NAME>() << endl;

	//get default device of the default platform
	std::vector<cl::Device> all_devices;
	default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
	if (all_devices.size() == 0) {
		std::cout << " No devices found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Device default_device = all_devices[0];
	std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << "\n";

	cl::Context context({ default_device });

	cl::Program::Sources sources;

	std::string kernel_code = GetKernelCode("./Kernel.txt");

	sources.push_back({ kernel_code.c_str(),kernel_code.length() });

	cl::Program program(context, sources);
	if (program.build({ default_device }) != CL_SUCCESS) {
		std::cout << " Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << endl;
		exit(1);
	}

	// create buffers on the device
	input = cl::Buffer(context, CL_MEM_READ_WRITE, sizeof(char) * board.size());
	output = cl::Buffer(context, CL_MEM_READ_WRITE, sizeof(char) * board.size());
	rowbuffer = cl::Buffer(context, CL_MEM_READ_WRITE, sizeof(int));
	linebuffer = cl::Buffer(context, CL_MEM_READ_WRITE, sizeof(int));

	//create queue to which we will push commands for the device.
	queue_simulation = cl::CommandQueue(context, default_device);

	// write arrays A and B to the device
	queue_simulation.enqueueWriteBuffer(input, CL_TRUE, 0, sizeof(char) * board.size(), &board[0]);
	queue_simulation.enqueueWriteBuffer(output, CL_TRUE, 0, sizeof(char) * board.size(), &changes[0]);
	queue_simulation.enqueueWriteBuffer(rowbuffer, CL_TRUE, 0, sizeof(int), &rows);
	queue_simulation.enqueueWriteBuffer(linebuffer, CL_TRUE, 0, sizeof(int), &lines);

	kernel_simulation = cl::Kernel(program, "simulatelife");
	kernel_simulation.setArg(0, input);
	kernel_simulation.setArg(1, rowbuffer);
	kernel_simulation.setArg(2, linebuffer);
	kernel_simulation.setArg(3, output);
}

string LifeSimulation::GetKernelCode(string inputFilename)
{
	string kernelcode;
	stringstream contentStream;
	ifstream fileStream(inputFilename);

	if (fileStream)
	{
		contentStream << fileStream.rdbuf();
		fileStream.close();

		kernelcode = contentStream.str();
	}
	else
	{
		cerr << "Kernel " << inputFilename << " not Found!" << endl;
	}

	return kernelcode;
}

void LifeSimulation::DebugOutput()
{
	int counter = 0;

	for(const auto &i : board)
	{
		std::cout << i;
		
		counter++;

		if(counter >= rows)
		{
			counter = 0;
			cout << endl;
		}
	}

	std::cout << endl;
}
