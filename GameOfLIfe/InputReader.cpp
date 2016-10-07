#include "InputReader.h"

InputReader::InputReader(string inputFilename)
{
	readInputFile(inputFilename);
	extractValuesFromContent();
}

InputReader::~InputReader()
{
}

vector<vector<bool>> InputReader::getBoard()
{
	return board;
}

void InputReader::extractValuesFromContent()
{
	char comma;

	stringstream contentStream(content);
	contentStream >> lineLength;
	contentStream >> comma;
	contentStream >> numberOfLines;

	char buffer;
	buffer = contentStream.get(); // newline
	buffer = contentStream.get();

	while(buffer != EOF)
	{
		if(buffer == '.')
		{
			line.push_back(false);
		} else if(buffer == 'x')
		{
			line.push_back(true);
		} else if(buffer == '\n')
		{
			board.push_back(line);
		}

		buffer = contentStream.get();
	}

	cout << numberOfLines << endl;
	cout << lineLength << endl;
	cout << board.size() << endl;
	cout << board[0].size() << endl;
}


void InputReader::readInputFile(string inputFilename)
{
	stringstream contentStream;
	ifstream fileStream(inputFilename);
	if(fileStream)
	{
		contentStream << fileStream.rdbuf();
	fileStream.close();

	content = contentStream.str();
	} else
	{
		cerr << "Inputfile " << inputFilename << " not Found!" << endl;
	}
	
}

