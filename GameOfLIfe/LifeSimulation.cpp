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

void LifeSimulation::Run(int generations, string mode)
{
	changes = new bool[board.size()];

	for(auto i = 0; i < generations; ++i)
	{
		SimulateLifeIteration();
	}

	delete[] changes;

  }

//void LifeSimulation::SimulateLifeIteration()
//{
//	for (int i = 0; i < lines; i++)
//	{
//		fill(changes[i], changes[i]+rows-1, false) ;
//	}
//
//	for (int i = 0; i < lines; ++i)
//	{
//		std::vector<bool> changeline;
//		for (int j = 0; j < rows; ++j)
//		{
//			changes[i][j] = CheckCell(i, j);
//		}
//		
//	}
//
//	for(auto i = 0; i < lines; ++i)
//	{
//		for(auto j = 0; j < rows; ++j)
//		{
//			if(changes[i][j])
//			{
//				ToggleCell(i, j);
//			}
//		}
//	}
//
//}
//
//void LifeSimulation::SimulateLifeOMP()
//{
//	#pragma omp parallel num_threads(4)
//	{
//		#pragma omp for
//		for (auto i = 0; i < lines; i++)
//		{
//			fill(changes[i], changes[i] + rows - 1, false);
//		}
//
//		#pragma omp for
//		for (auto i = 0; i < lines; ++i)
//		{
//			for (auto j = 0; j < rows; ++j)
//			{
//				changes[i][j] = CheckCell(i, j);
//			}
//
//		}
//
//		#pragma omp for
//		for (auto i = 0; i < lines; ++i)
//		{
//			for (auto j = 0; j < rows; ++j)
//			{
//				if (changes[i][j])
//				{
//					ToggleCell(i, j);
//				}
//			}
//		}
//	}
//
//}

void LifeSimulation::SimulateLifeIteration()
{

	fill(changes, changes + sizeof(changes), false);

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
			if (changes[i * rows + j])
			{
				ToggleCell(i, j);
			}
		}
	}
}

bool LifeSimulation::CheckCell(const int& line, const int& row) const
{
	const int neighbors = CountNeighbors(line, row);

	//Alive
	if (board[line * rows + row] == 'x')
	{
		if (neighbors >= 4 || neighbors <= 1)
		{
			return true;
		}
	}
	//Dead
	else
	{
		if (neighbors == 3)
		{
			return true;
		}
	}

	return false;
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
