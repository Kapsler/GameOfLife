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

vector<vector<char>>* LifeSimulation::getBoardPtr()
{
	return &board;
}

void LifeSimulation::Run(int generations)
{

	lines = board.size();
	rows = board[0].size();

	cout << "Lines: " << lines << endl;
	cout << "Rows: " << rows << endl;

	//Initialize helping array
	changes = new bool*[lines];
	for (int i = 0; i < lines; i++)
	{
		changes[i] = new bool[rows];
	}

	for(auto i = 0; i < generations; ++i)
	{
		SimulateLifeIteration();
	}

	//Free helping array
	for (int i = 0; i < lines; i++)
	{
		delete[] changes[i];
	}
	delete[] changes;
}

void LifeSimulation::SimulateLifeIteration()
{
	for (int i = 0; i < lines; i++)
	{
		fill(changes[i], changes[i]+rows-1, false) ;
	}

	for (int i = 0; i < lines; ++i)
	{
		std::vector<bool> changeline;
		for (int j = 0; j < rows; ++j)
		{
			changes[i][j] = CheckCell(i, j);
		}
		
	}

	for(auto i = 0; i < lines; ++i)
	{
		for(auto j = 0; j < rows; ++j)
		{
			if(changes[i][j])
			{
				ToggleCell(i, j);
			}
		}
	}

}

bool LifeSimulation::CheckCell(const int &line, const int &row) const
{
	const int neighbors = CountNeighbors(line, row);

	//Alive
	if (board[line][row] == 'x')
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

int LifeSimulation::CountNeighbors(const int &line, const int &row) const
{
	int neighborcount = 0;
	int lineafter = line + 1;
	int linebefore = line - 1;
	int rowafter = row + 1;
	int rowbefore = row - 1;


	if(rowafter >= rows)
	{
		rowafter = mod(row + 1, rows);
	}
	if(rowbefore < 0)
	{
		rowbefore = mod(row - 1, rows);
	}
	if(lineafter >= lines)
	{
		lineafter = mod(line + 1, lines);
	}
	if(linebefore < 0)
	{
		linebefore = mod(line - 1, lines);
	}

	//X__
	//___
	//___
	if (board[linebefore][rowbefore] == 'x') neighborcount++;
	//_X_
	//___
	//___
	if (board[linebefore][row] == 'x') neighborcount++;
	//__X
	//___
	//___
	if (board[linebefore][rowafter] == 'x') neighborcount++;
	//___
	//X__
	//___
	if (board[line][rowbefore] == 'x') neighborcount++;
	//___
	//__X
	//___
	if (board[line][rowafter] == 'x') neighborcount++;
	//___
	//___
	//X__
	if (board[lineafter][rowbefore] == 'x') neighborcount++;
	//___
	//___
	//_X_
	if (board[lineafter][row] == 'x') neighborcount++;
	//___
	//___
	//__X
	if (board[lineafter][rowafter] == 'x') neighborcount++;

	return neighborcount;
}

int inline LifeSimulation::mod(int first, const int& second) const
{
	//return (first%second + second) % second;
	return ((first %= second) < 0) ? first + second : first;
}

void LifeSimulation::ToggleCell(const int& line, const int& row)
{
	if (board[line][row] == 'x')
	{
		board[line][row] = '.';
	} else
	{
		board[line][row] = 'x';
	}
}

void LifeSimulation::DebugOutput()
{
	for(const auto &i : board)
	{
		for(const auto & j : i)
		{
			std::cout << j;
		}

		std::cout << endl;
	}
}
