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

using SectionRange = std::pair<int, int>;
using SectionPair  = std::pair<SectionRange, SectionRange>;
using SectionPairVector = std::vector<SectionPair>;

std::ostream &operator<<(std::ostream &out, const SectionRange &range);
std::ostream &operator<<(std::ostream &out, const SectionPair &pair);
SectionRange TranslateSectionRange(const std::string &input);
SectionPair  TranslateSectionPair(const std::string &input);
SectionPairVector CollectSectionPairs(std::ifstream &input);
bool DoesSectionPairOverlap(const SectionPair &pair);

int
main(int argv, char *argc[])
{
	try {
		std::ifstream input("input.txt");
		if (!input.is_open())
			throw std::runtime_error("Input file not found!");

		const auto sectionPairs = CollectSectionPairs(input);
		const auto pair = TranslateSectionPair("2-8,3-7");
		std::cout << pair.second.second << '\n';
		std::cout << std::boolalpha << DoesSectionPairOverlap(pair) << '\n';
		return 0;
	}
	catch (const std::exception &except) {
		std::cerr << "Something went wrong: " << except.what() << '\n';
	}
}

std::ostream &
operator<<(std::ostream &out, const SectionRange &range)
{
	out << range.first << '-' << range.second;
	return out;
}

std::ostream &operator<<(std::ostream &out, const SectionPair &pair)
{
	out << pair.first << ',' << pair.second;
	return out;
}

SectionRange
TranslateSectionRange(const std::string &input)
{
	const auto index = input.find_first_of('-');
	if (index == std::string::npos)
		throw std::runtime_error("There should be a dash here!");		
	return std::make_pair(std::stoi(input.substr(0, index)),
						  std::stoi(input.substr(index + 1)));
}

SectionPair
TranslateSectionPair(const std::string &input)
{
	const auto index = input.find_first_of(',');
	if (index == std::string::npos)
		throw std::runtime_error("There should be a comma here!");
	return std::make_pair(
		TranslateSectionRange(input.substr(0, index)),
		TranslateSectionRange(input.substr(index + 1))
		);
}

SectionPairVector
CollectSectionPairs(std::ifstream &input)
{   /**
	 ** Place the input data into a list of section range pairs.
	 **/	
	decltype(CollectSectionPairs(input)) results{};
	for (std::string line; std::getline(input, line); ) {
		decltype(results)::value_type pair = TranslateSectionPair(line);
		results.push_back(pair);
		std::cout << results.back() << '\n';
	}
	return results;
}

bool
DoesSectionPairOverlap(const SectionPair &pair)
{
	auto generateRangeView = [](const SectionRange &range) -> auto {
		return std::ranges::views::iota(range.first, range.second + 1);
	};
	const auto firstRange  = generateRangeView(pair.first);
	const auto secondRange = generateRangeView(pair.second);
	return (true);
}
