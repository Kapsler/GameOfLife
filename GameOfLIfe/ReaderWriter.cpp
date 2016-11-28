#include "ReaderWriter.h"

ReaderWriter::ReaderWriter(string inputFilename,
	vector<char> *board, int* linesptr, int* rowsptr)
{
	lines = linesptr;
	rows = rowsptr;

	readInputFile(inputFilename);
	extractValuesFromContent(board);
}

ReaderWriter::~ReaderWriter()
{
}

void ReaderWriter::WriteToFile(string outputFilename, vector<char> *board) const
{
	ofstream fileStream(outputFilename);

	if (fileStream)
	{
		//Write
		fileStream << *rows << ',' << *lines << endl;

		int counter = 0;
		for(const auto &i : *board)
		{
			fileStream << i;
			counter++;

			if (counter >= *rows)
			{
				fileStream << endl;
				counter = 0;
			}
				
		}

		fileStream.close();

	}
	else
	{
		cerr << "Couldn't write to " << outputFilename << endl;
	}
}

void ReaderWriter::extractValuesFromContent(vector<char> *board) const
{
	char comma;

	stringstream contentStream(content);
	contentStream >> *rows;
	contentStream >> comma;
	contentStream >> *lines;

	char buffer;
	buffer = contentStream.get(); // newline
	buffer = contentStream.get();

	board->reserve(*rows * *lines);

	while(buffer != EOF)
	{
		if(buffer != '\n')
		{
			board->push_back(buffer);
		}

		buffer = contentStream.get();
	}
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

