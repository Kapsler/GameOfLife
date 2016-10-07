#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class CommandLineParser {
public:
	CommandLineParser(int &argc, char **argv);
	const string& getCmdOption(const string &option) const;
	bool cmdOptionExists(const string &option) const;

private:
	vector<string> tokens;
};