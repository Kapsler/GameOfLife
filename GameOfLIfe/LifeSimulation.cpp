#include "LifeSimulation.h"

LifeSimulation::LifeSimulation()
{
	lines = 0;
	rows = 0;
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

	for(auto i = 0; i < generations; ++i)
	{
		SimulateLifeIteration();
		//SimulateLifeRecursion(0);
	}
}

void LifeSimulation::SimulateLifeIteration()
{
	std::vector<std::vector<bool>> changes;

	for (int i = 0; i < lines; ++i)
	{
		std::vector<bool> changeline;
		for (int j = 0; j < rows; ++j)
		{
			changeline.push_back(CheckCell(i, j));
		}
		changes.push_back(changeline);
	}

	for(auto i = 0; i < changes.size(); ++i)
	{
		for(auto j = 0; j < changes[0].size(); ++j)
		{
			if(changes[i][j])
			{
				ToggleCell(i, j);
			}
		}
	}

}

void LifeSimulation::SimulateLifeRecursion(int cell)
{

	bool changed = false;
	char* current = &board[cell / rows][cell%rows];
	int neighbors = CountNeighbors(cell / rows, cell%rows);

	//Alive
	if (*current == 'x')
	{
		if(neighbors >= 4 || neighbors <= 1)
		{
			changed = true;
		}
	}
	//Dead
	else
	{
		if (neighbors == 3)
		{
			changed = true;
		}
	}

	//Recursion
	if((cell + 1) / rows < lines)
	{
		SimulateLifeRecursion(cell + 1);
	}

	//Change of state
	if(changed)
	{
		//cout << "Changed cell: " << currentLine << " " << cellIndex << endl;
		if (*current == 'x') 
		{
			*current = '.';
		}
		else
		{
			*current = 'x';
		}
	}

}

const bool LifeSimulation::CheckCell(const int &line, const int &row) const
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

const int LifeSimulation::CountNeighbors(const int &line, const int &row) const
{
	int neighborcount = 0;

	//X__
	//___
	//___
	if (board[mod(line - 1, lines)][mod(row - 1, rows)] == 'x') neighborcount++;
	//_X_
	//___
	//___
	if (board[mod(line - 1, lines)][(row) % rows] == 'x') neighborcount++;
	//__X
	//___
	//___
	if (board[mod(line - 1, lines)][mod(row + 1, rows)] == 'x') neighborcount++;
	//___
	//X__
	//___
	if (board[(line) % lines][mod(row - 1, rows)] == 'x') neighborcount++;
	//___
	//__X
	//___
	if (board[(line) % lines][mod(row + 1, rows)] == 'x') neighborcount++;
	//___
	//___
	//X__
	if (board[mod(line + 1, lines)][mod(row - 1, rows)] == 'x') neighborcount++;
	//___
	//___
	//_X_
	if (board[mod(line + 1, lines)][(row) % rows] == 'x') neighborcount++;
	//___
	//___
	//__X
	if (board[mod(line + 1, lines)][mod(row + 1, rows)] == 'x') neighborcount++;

	return neighborcount;
}

const int LifeSimulation::mod(const int& first, const int& second) const
{
	return (first%second + second) % second;
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
