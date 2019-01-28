#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>

#include "GraphData.h"

inline void println(std::string const &str = "") {
	std::cout << str << std::endl;
}

static std::vector<std::string> split(std::string const &s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

inline bool parseGraphData(GraphData &gd, std::ifstream &file) {
	{
		bool success = true;

		enum sectionType {
			NONE, VERTICES, EDGES
		};

		sectionType section = NONE;

		std::cout << "Parsing definition file..." << std::endl;

		try {
			std::string line;
			std::regex const csvRgx(R"((\w+)(,\s*\d+)*)"); // regex to match comma separated values
			std::regex const parensRgx("\\((.*?)\\)"); // regex to match values wrapped in parens

			while (std::getline(file, line)) {

				if (line == "Vertices:") {
					section = VERTICES;
					std::cout << "\nFound the Vertices section:" << std::endl;

					continue;
				}

				if (line == "Edges:") {
					section = EDGES;
					std::cout << "\nFound the Edges section:" << std::endl;

					continue;
				}

				if (section == VERTICES) {
					std::sregex_iterator next(line.begin(), line.end(), csvRgx);
					std::sregex_iterator end;
					while (next != end) {
						std::smatch match = *next;

						char vertex = match.str()[0];

						std::cout << "Add vertex " << vertex << std::endl;
						gd.addVertex(vertex);

						next++;
					}
				}

				if (section == EDGES) {
					std::sregex_iterator next(line.begin(), line.end(), parensRgx);
					std::sregex_iterator end;
					while (next != end) {
						std::smatch match = *next;
						std::string str = match.str();

						// remove the parens
						str.erase(std::remove(str.begin(), str.end(), '('), str.end());
						str.erase(std::remove(str.begin(), str.end(), ')'), str.end());

						// split off the comma into a vector
						auto vector = split(str, ',');
						char u = vector[0][0];
						char v = vector[1][0];
						int w = std::stoi(vector[2]);

						std::cout << "Adding edge " << u << " <--> " << v << " with a weight of " << w << std::endl;
						gd.addEdge(u, v, w);

						next++;
					}
				}
			}
		}
		catch (...) {
			success = false;
		}

		return success;
	}
}
