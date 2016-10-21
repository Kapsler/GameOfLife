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
	std::vector<char> neighbors;

	//cout << "Counting neighbors" << endl;

	//int lineAbove = mod(line - 1, lines);
	//int lineBelow = mod(line + 1, lines);
	//int cellBefore = mod(cell - 1, rows);
	//int cellAfter = mod(cell + 1, rows);

	//cout << "Line Above: " << lineAbove << endl;
	//cout << "Line Below: " << lineBelow << endl;
	//cout << "Cell Before: " << cellBefore << endl;
	//cout << "Cell After: " << cellAfter << endl;

	//X__
	//___
	//___
	neighbors.push_back(board[mod(line - 1, lines)][mod(row - 1, rows)]);
	//_X_
	//___
	//___
	neighbors.push_back(board[mod(line - 1, lines)][(row)%rows]);
	//__X
	//___
	//___
	neighbors.push_back(board[mod(line - 1, lines)][mod(row + 1, rows)]);
	//___
	//X__
	//___
	neighbors.push_back(board[(line)%lines][mod(row - 1, rows)]);
	//___
	//__X
	//___
	neighbors.push_back(board[(line)%lines][mod(row + 1, rows)]);
	//___
	//___
	//X__
	neighbors.push_back(board[mod(line + 1, lines)][mod(row - 1, rows)]);
	//___
	//___
	//_X_
	neighbors.push_back(board[mod(line + 1, lines)][(row)%rows]);
	//___
	//___
	//__X
	neighbors.push_back(board[mod(line + 1, lines)][mod(row + 1, rows)]);

	//std::cout << "Neighbors for cell " << line << " " << cell << " = " << neighborcount << endl;
	return std::count(neighbors.begin(), neighbors.end(), 'x');
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
