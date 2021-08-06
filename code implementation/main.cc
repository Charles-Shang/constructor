/*
 * Name: Yifan Qu and Jiaqi Shang
 * Course: CS 246
 * Term: Spring 2021
 * Final Project: Game of Constructor
 */

#include <stdio.h>
#include <iostream>

using std::cin;
using std::string;


// print spaces inside tiles (intotal there are 8 spaces)
void ps() { std::cout << "       "; }

// print the board
void printBoard() {
    int vertex = 0;
    int edge = 0;
    int tile = 0;
    // 10 rows of block
    for (int a = 1; a <= 10; ++a) {
        // 4 rows in each block
        for (int b = 1; b <= 4; ++b) {
            // each row in 5 column
            for (int c = 0; c <= 5; ++c) {
                if (a == 1 || (a + c) % 2 == 1) {
                    if ((a == 1 && (c == 1 || c == 2)) || ()) {
                        std::cout << "  ";
                        ps();
                    }
                }
            }
        }
    }
}

int main() {
    // string name;
    // cin >> name;
    // std::cout << guardName(name) << std::endl;
    printBoard();
}
