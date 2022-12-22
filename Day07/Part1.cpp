#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <array>
#include <cstdlib>
#include <cstdio>
#include <numeric>
#include <algorithm>
#include <ranges>
#include <string>
#include <utility>
#include <exception>
#include <cctype>
#include <stack>
#include <memory>
#include <regex>
#include <type_traits>
#include <variant>
#include <unordered_map>

struct File;
struct Directory;
// File system element.
using FSElement = std::variant<File, Directory>;
using DirectoryUMap = std::unordered_map<std::string, FSElement>;

struct Directory
{   /**
	 ** Each directory has its own DirectoryMap.
	 **/
    DirectoryUMap contents;
};

struct File
{
	std::size_t size;
};

void ProcessShellCommand(std::string_view command,
						 std::string_view argument,
						 const std::vector<std::string> &commandOutput,
						 DirectoryUMap &rootDirectory);
DirectoryUMap ProcessShellSession(std::ifstream &input);

int
main(int argv, char *argc[])
{
	try {
		std::ifstream input("input.txt");
		if (!input.is_open())
			throw std::runtime_error("Input file not found!");

		auto rootDirectory = ProcessShellSession(input);
		return 0;
	}
	catch (const std::exception &except) {
		std::cerr << "Something went wrong: " << except.what() << '\n';
	}
}

void
ProcessShellCommand(std::string_view command, std::string_view argument,
					const std::vector<std::string> &commandOutput,
					DirectoryUMap &rootDirectory)
{
	if (command == "cd") {
		std::cout << command << ' ' << argument << '\n';
		if (argument == "/") {

		}
		else if (argument == "..") {

		}
		else {

		}
	}
	else if (command == "ls") {
		std::cout << command << '\n';
		for (auto line : commandOutput) {
			std::cout << line << '\n';
		}
	}
	else
		throw std::runtime_error("Unrecognized command!");
}

DirectoryUMap
ProcessShellSession(std::ifstream &input)
{
	decltype(ProcessShellSession(input)) rootDirectory;
	std::string command, argument;
	std::vector<std::string> commandOutput;
	for (std::string line; std::getline(input, line); ) {
		// Currently not getting the last lines of output
		{
			std::string::size_type position{};
			if ((position = line.find_first_of('$')) != std::string::npos) {
				if (!command.empty()) {
					ProcessShellCommand(command, argument, commandOutput, rootDirectory);
				}
				commandOutput.clear();
				std::istringstream iss(line.substr(position + 2));
				iss >> command >> argument;
			} else {
				commandOutput.push_back(line);
			}
		}
	}
	return rootDirectory;
}
