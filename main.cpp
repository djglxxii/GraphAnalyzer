#include <iostream>
#include <fstream>
#include <regex>

#include "GraphData.h"

#include "Utility.cpp"
#include "KruskalMst.h"
#include "DijkstraSp.h"
#include "Tsp.h"

static void runDjsShortestPath(GraphData const &gd);

static void runKruskalsMst(GraphData const &gd);

static void runTsp(GraphData const &gd);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "no input file specified!" << std::endl;
        system("pause");

        exit(EXIT_FAILURE);
    }

    std::string const filename = argv[1];
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Cannot open input file " << filename << std::endl;
        system("pause");
        exit(EXIT_FAILURE);
    }

    GraphData gd;
    bool success = parseGraphData(gd, file);

    if (!success) {
        std::cerr << "Failure during parsing of input file.  Please make sure the format is correct." << std::endl;
        system("pause");
        exit(EXIT_FAILURE);
    }

    file.close();

    bool isRunning = true;

    while (isRunning) {
        println();
        // menu
        println("----------------------------------------------");
        println("|      SUPER DUPER GRAPH ANALYZER 2000       |");
        println("----------------------------------------------");
        println("(1) Dijkstra's Shortest Path");
        println("(2) Kruskal's Minimum Spanning Tree");
        // println("(3) The Traveling Salesman");
        println("(Q) Quit");
        println("Type the number your option and press [ENTER]:");

        char option;
        std::cin >> option;

        switch (option) {
            case '1':
                runDjsShortestPath(gd);
                break;
            case '2':
                runKruskalsMst(gd);
                break;
            case '3':
                // runTsp(gd);
                break;
            case 'Q':
			case 'q':
                isRunning = false;
                break;
            default:
                println("Invalid selection! Try again.");
                break;
        }
    }

    println("GOODBYE!");
}

static void runDjsShortestPath(GraphData const &gd) {
    println("Welcome to Dijkstra's Shortest Path!");

    auto dj = DijkstraSp(gd);

    bool isRunning = true;

    while (isRunning) {
        char v1, v2;

        println("Please enter the START vertex (make sure vertex name exactly matches input file):");
        std::cin >> v1;

        println("Please enter the END vertex (make sure vertex name exactly matches input file):");
        std::cin >> v2;

        try {
            dj.showShortest(v1, v2);
        }
        catch (...) {
            println("oops!  Something unexpected happened. Check your input and try again.");
        }

        char input;
        println("Run Dijkstra again? (Y/N)");
        std::cin >> input;

        isRunning = input == 'Y' || input == 'y';
    }
}

static void runKruskalsMst(GraphData const &gd) {
    println("Welcome to Kruskal's Minimum Spanning Tree!");
    println("-------------------------------------------");

    auto kr = KruskalMst(gd);
    kr.showMinimumSpanningTree();
}

static void runTsp(GraphData const &gd) {
    println("Welcome to The Traveling Salesman Problem!");
    println("------------------------------------------");

    auto tsp = Tsp(gd);
    tsp.execute();
}