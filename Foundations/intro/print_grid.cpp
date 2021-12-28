#include "print_grid.h"

string getBoardString(Board cell){
    switch(cell) {
        case Board::Object: return "N   ";
        default: return "0   ";
    }
}

vector<Board> parseLine(string& line){
    istringstream line_stream(line);
    int i;
    char c;
    vector<Board> vec;
    while(line_stream >> i >> c && c == ',')
        if(i==0)
            vec.push_back(Board::Free);
        else
            vec.push_back(Board::Object);
    return vec;
}

// TODO: Add the ReadBoardFile function here.
vector<vector<Board>> readBoardFile(){
    std::ifstream board_file("C:\\study\\cpp_course\\Foundations\\intro\\1.board");
    string line;
    vector<vector<Board>> board;
    if (board_file) {
        while (getline(board_file, line)) {
            board.push_back(parseLine(line));
        }
    }
    return board;
}

// printBoard not used in this exercise
void printBoard(const vector<vector<Board>>& board) {
    for (const auto & i : board) {
        for (auto j : i) {
            cout << getBoardString(j);
        }
        cout << "\n";
    }
}

int run_func() {
    // TODO: Call the ReadBoardFile function here.
    auto board  = readBoardFile();
    printBoard(board);
    return 0;
}
