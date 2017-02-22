#include <iostream>
#include <cstdlib>
#include "../include/parserArguments.hpp"

using namespace std;

/**
* Build the list of possible options and parameters
**/

parserArguments::parserArguments(vector<string> optionsNames, vector<string> parametersNames) :
    arguments(vector<string>()), options(map<string, bool>()), parameters(map<string, string>())
{
	for (string option : optionsNames)
		options[option] = false;

	for (string param : parametersNames)
		parameters[param] = "";

	options["h"] = false;
	options["-help"] = false;
}

/**
* Destructor
**/

parserArguments::~parserArguments() {}

/**
* Does the user ask for help?
**/

bool parserArguments::askHelp()
{
	return options["h"] || options["-help"];
}

/**
* Return the number of arguments
**/

size_t parserArguments::nbArguments() const
{
	return arguments.size();
}

/**
* Parse arguments and options
**/

void parserArguments::parse(int argc, char* argv[])
{
	unsigned int nbArgs = 0;
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			string option = string(argv[i]).substr(1);
			if (option.find("=") == string::npos)
			{
				if (options.count(option) == 0)
					cerr << "Unknown option : " << option << endl;
				else
					options[option] = true;
			}
			else
			{
				if (parameters.count(option.substr(0,option.find("="))) == 0)
					cerr << "Unknown parameter : " << option.substr(0,option.find("=")) << endl;
				else
					parameters[option.substr(0,option.find("="))] = option.substr(option.find("=")+1);
		}	}
		else
		{
			arguments.push_back(argv[i]);
			nbArgs++;
}	}	}

/**
* Get the argument in a given index
**/

string parserArguments::getArgument(size_t index) const
{
	return arguments[index];
}

/**
* Is the option used?
**/

bool parserArguments::getOption(string name) const
{
	return options.at(name);
}

/**
* Get the parameter of an option
**/

string parserArguments::getParameter(string name) const
{
	return parameters.at(name);
}

/**
* Get the parameter of an option, with a default result otherwise
**/

string parserArguments::getParameter(string name, string def) const
{
	if (parameters.count(name) == 0)
		return def;
	if (parameters.at(name) == "")
		return def;
	return parameters.at(name);
}

/**
* Get all the possible options
**/

vector<string> parserArguments::getOptionsNames()
{
	vector<string> liste(2);
	liste[0] = "-stats";
	liste[1] = "-cex";
	return liste;
}

/**
* Get all the possible arguments
**/

vector<string> parserArguments::getParametersNames()
{
	vector<string> liste(3);
	liste[0] = "o";
	liste[1] = "i";
	liste[2] = "-iterations";
	return liste;
}
