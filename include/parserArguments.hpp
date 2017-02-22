#ifndef DEF_PARSERARGUMENTS
#define DEF_PARSERARGUMENTS

#include <string>
#include <vector>
#include <map>

/**
* Parse the arguments and the options provided in the command line
**/

class parserArguments
{
	public:
		parserArguments(std::vector<std::string> optionsNames, std::vector<std::string> parametersNames);
		~parserArguments();
		bool askHelp();

		size_t nbArguments() const __attribute__((pure));
		void parse(int argc, char* argv[]);

		std::string getArgument(size_t index) const;
		bool getOption(std::string name) const;
		std::string getParameter(std::string name) const;
		std::string getParameter(std::string name, std::string def) const;

		static std::vector<std::string> getOptionsNames();
		static std::vector<std::string> getParametersNames();

	private:
		std::vector<std::string> arguments;
		std::map<std::string, bool> options;
		std::map<std::string, std::string> parameters;
};

#endif
