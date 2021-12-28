//
// Created by jmuppave on 12/27/2021.
//

#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

using vec2dint_type = vector<vector<int>>;
using vec1dint_type = vector<int>;
//const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
const vec2dint_type delta {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

class XYCoords{
public:
    int x,y;
    explicit XYCoords(int _x=0, int _y=0):x{_x},y{_y}{};
};

enum class GridStates {Free,Object,Closed,Path,Start,End};
using grid_type = vector<vector<GridStates>>;
using row_type = vector<GridStates>;

string getGridString(GridStates cell){
    switch(cell) {
        case GridStates::Object: return "N   ";
        case GridStates::Path: return "P   ";
        case GridStates::Start: return "S   ";
        case GridStates::End: return "F   ";
        default: return "0   ";
    }
}

//string getGridString(GridStates cell){
//    switch(cell) {
//        case GridStates::Object: return "⛰️   ";
//        case GridStates::Path: return "🚗   ";
//        case GridStates::Start: return "🚦   ";
//        case GridStates::End: return "🏁   ";
//        default: return "0️   ";
//    }
//}

row_type parseLine(string& line){
    istringstream line_stream(line);
    int i;
    char c;
    row_type vec;
    while(line_stream >> i >> c && c == ',')
        if(i==0)
            vec.push_back(GridStates::Free);
        else
            vec.push_back(GridStates::Object);
    return vec;
}

// TODO: Add the ReadGridFile function here.
grid_type readGridFile(){
    std::ifstream grid_file("C:\\study\\cpp_course\\Foundations\\intro\\1.board");
    string line;
    grid_type grid;
    if (grid_file) {
        while (getline(grid_file, line)) {
            grid.push_back(parseLine(line));
        }
    }
    return grid;
}

bool compareCostHeuristic(const vec1dint_type& a, const vec1dint_type& b){
    return (a[2]+a[3]) > (b[2]+b[3]);
}

void vecSort(vec2dint_type& open_vec){
    sort(open_vec.begin(), open_vec.end(), compareCostHeuristic);
}

bool checkValidCell(int x, int y, const grid_type& grid){
    bool on_grid_x = (x >= 0 && x < grid.size());
    bool on_grid_y = (y >= 0 && y < grid[0].size());
    if (on_grid_x && on_grid_y)
        return grid[x][y] == GridStates::Free;
    return false;
}

int heuristic(const int x, const int y, const XYCoords& goal){
    return abs(goal.x - x) + abs(goal.y - y);
}

void addToOpen(const vec1dint_type& cell_details, vec2dint_type& open_vec, grid_type& grid){
    open_vec.push_back(cell_details);
    grid[cell_details[0]][cell_details[1]] = GridStates::Closed;
}

void expandNeighbours(
        const vec1dint_type& current, const XYCoords& goal,
        vec2dint_type& open_vec, grid_type& grid
){
    for(vec1dint_type xy: delta){
        int x = current[0] + xy[0];
        int y = current[1] + xy[1];
        if (checkValidCell(x,y,grid)){
            addToOpen(
                    vec1dint_type {x,y,current[2]+1, heuristic(x,y,goal)},
                    open_vec, grid
            );
        }
    }
}

grid_type searchPath(grid_type grid, const XYCoords& start, const XYCoords& goal){
    vec2dint_type open_vec {};
    int x = start.x;
    int y = start.y;
    int g = 0; //Cost
    int h = heuristic(x, y, goal);
    addToOpen(vec1dint_type {x,y,g,h}, open_vec, grid);

    while(!open_vec.empty()){
        vecSort(open_vec);
        auto current = open_vec.back();
        open_vec.pop_back();
        x = current[0];
        y = current[1];
        grid[x][y] = GridStates::Path;
        if (x == goal.x && y==goal.y){
            grid[goal.x][goal.y] = GridStates::End;
            grid[start.x][start.y] = GridStates::Start;
            return grid;
        }
        expandNeighbours(current,goal,open_vec, grid);
    }
    cout << "No path found!" << "\n";
    return grid_type {};
}

// printGrid not used in this exercise
void printGrid(const grid_type & grid) {
    for (const auto & i : grid) {
        for (auto j : i) {
            cout << getGridString(j);
        }
        cout << "\n";
    }
}

int main() {
    // TODO: Call the ReadGridFile function here.
    auto grid  = readGridFile();
    XYCoords start(0,0);
    XYCoords goal(4,5);
    auto solution = searchPath(grid, start, goal);
    printGrid(solution);
}
