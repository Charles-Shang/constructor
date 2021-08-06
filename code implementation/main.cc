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

// return the random tile num (note that Park does not have a tile num)
void printTileNum(int tile) {
    if (tile < 10) {
        std::cout << " ";
    }
    std::cout << tile;
}

void printTileType(int tile) { std::cout << "TYPE  "; }

// print spaces inside tiles (in total there are 8 spaces)
void ps() { std::cout << "        "; }

// print the board
void printBoard() {
    int vertex = 0;
    int edge = 0;
    int tile = 0;
    // 10 rows of block
    for (int a = 1; a <= 10; ++a) {
        // 4 rows in each block
        for (int b = 1; b <= 4; ++b) {
            if (a <= 9 && a >= 3 && b == 1) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            // each row in 5 column
            for (int c = 1; c <= 5; ++c) {
                // print blank block
                if (a == 1 && (c == 1 || c == 5)) {  // top two cornors
                    std::cout << "  ";
                    ps();
                } else if ((a == 1 && c == 4) || (a == 2 && c == 5) ||
                           (a == 10 && c == 5)) {  // right
                    if (b == 1) {
                        if (vertex < 10) {
                            std::cout << " ";
                        }
                        std::cout << vertex << "|       ";  // | with 7 spaces
                        ++vertex;
                    } else {
                        if (a == 10) {
                            std::cout << "  ";
                            ps();
                        } else {
                            if (b == 2 || b == 4) {
                                std::cout << " |";
                                ps();
                            } else {
                                std::cout << " " << edge;
                                ps();
                                ++edge;
                            }
                        }
                    }
                } else if ((a == 1 && c == 2) || (a == 2 && c == 1) ||
                           (a == 10 && c == 1)) {  // left
                    ps();
                    if (b == 1) {
                        std::cout << " |";
                    } else {
                        std::cout << "  ";
                    }
                } else if ((a == 9 && c == 1) || (a == 10 && c == 2)) {
                    if (b == 1){
                        std::cout << vertex << "|--" << edge << "--|";
                        ++vertex;
                        ++edge;
                    } else {
                        std::cout << "  ";
                        ps();
                    }
                } else if ((a == 9 && c == 5) || (a == 10 && c == 4)) {
                    if (b == 1){
                        std::cout << vertex << "|--" << edge << "--|";
                        ++vertex;
                        ++edge;
                    } else if (b == 2 || b == 4) {
                        std::cout << " |";
                        ps();
                    } else {
                        std::cout << edge;
                        ++edge;
                        ps();
                    }
                
                } else if ((a + c) % 2 == 1) {  // other blank block
                    if (b == 1) {
                        if (vertex < 10) {
                            std::cout << " ";
                        }
                        std::cout << vertex << "|  ";
                        printTileNum(tile);
                        std::cout << "  |";
                        ++vertex;
                    } else {
                        if (b == 2 || b == 4) {
                            std::cout << " |";
                        } else {
                            if (edge < 10) {
                                std::cout << " ";
                            }
                            std::cout << edge;
                            ++edge;
                        }
                        ps();
                    }
                } else {
                    if (b == 1) {
                        if (vertex < 10) {
                            std::cout << " ";
                        }
                        std::cout << vertex << "|--";
                        if (edge < 10) {
                            std::cout << " ";
                        }
                        std::cout << edge << "--|";
                        ++edge;
                        ++vertex;
                    } else if (b == 2) {
                        std::cout << " |";
                        ps();
                    } else if (b == 3) {
                        if (edge < 10) {
                            std::cout << " ";
                        }
                        std::cout << edge << "   ";  // 3 spaces
                        if (tile < 10) {
                            std::cout << " ";
                        }
                        std::cout << tile << "   ";  // 3 spaces
                        ++tile;
                        ++edge;
                    } else {
                        std::cout << " |  ";
                        printTileType(tile);
                    }
                }
            }
            if (a <= 8 && a >= 3) {
                if (b == 1) {
                    std::cout << vertex << "|";
                    ++vertex;
                } else if (b == 2 || b == 4) {
                    std::cout << " | ";
                } else {
                    std::cout << edge;
                    ++edge;
                }
            } else if (a == 9 && b == 1) {
                std::cout << vertex << "|";
                ++vertex;
            }
            std::cout << std::endl;
        }
    }
    std::cout << "    ";
    ps();
    ps();
    std::cout << "|" << vertex << "|--" << edge;
    ++vertex;
    std::cout << "--|" << vertex << "|";
}

int main() { printBoard(); }
