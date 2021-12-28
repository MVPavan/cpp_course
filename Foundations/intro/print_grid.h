//
// Created by jmuppave on 12/27/2021.
//

#ifndef UDACITY_PRINT_GRID_H
#define UDACITY_PRINT_GRID_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


enum class Board {Free,Object};

string getBoardString(Board cell);
vector<Board> parseLine(string& line);
vector<vector<Board>> readBoardFile();
int run_func();
void printBoard(const vector<vector<Board>>& board);

#endif //UDACITY_PRINT_GRID_H
