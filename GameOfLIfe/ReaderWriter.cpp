#include "ReaderWriter.h"

ReaderWriter::ReaderWriter(string inputFilename,
	vector<vector<char>> *board)
{
	readInputFile(inputFilename);
	extractValuesFromContent(board);
}

ReaderWriter::~ReaderWriter()
{
}

void ReaderWriter::WriteToFile(string outputFilename, vector<vector<char>> *board)
{
	ofstream fileStream(outputFilename);

	if (fileStream)
	{
		//Write
		fileStream << (*board)[0].size() << ',' << board->size() << endl;

		for(const auto &i : *board)
		{
			for(const auto &j : i)
			{
				fileStream << j;
			}
			fileStream << endl;
		}

		fileStream.close();

	}
	else
	{
		cerr << "Couldn't write to " << outputFilename << endl;
	}
}

void ReaderWriter::extractValuesFromContent(vector<vector<char>> *board)
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
			line.push_back('.');
		} else if(buffer == 'x')
		{
			line.push_back('x');
		} else if(buffer == '\n')
		{
			board->push_back(line);
			line.clear();
		}

		buffer = contentStream.get();
	}

	//cout << numberOfLines << endl;
	//cout << lineLength << endl;
	//cout << board->size() << endl;
	//cout << board[0].size() << endl;
}


void ReaderWriter::readInputFile(string inputFilename)
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

