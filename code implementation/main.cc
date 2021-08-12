/*
 * Name: Yifan Qu and Jiaqi Shang
 * Course: CS 246
 * Term: Spring 2021
 * Final Project: Game of Constructor
 */

#include <stdio.h>
#include <random>
#include <chrono>
#include <fstream>
#include <iostream>
#include "game.h"

using std::cin;
using std::string;

int main(int argc, char* argv[]) {
    bool load = false, board = false, randomBoard = false;
    std::string loadedFile, boardFile, finalFile = "layout.txt";
    int decision = 4;

    // unsigned seed =
    // std::chrono::system_clock::now().time_since_epoch().count();
    unsigned seed = 1000;

    for (int i = 0; i < argc; i++) {
        std::string flags{argv[i]};
        if (flags == "seed") {
            try {
                seed = std::stoi(std::string{argv[++i]});
            } catch (std::invalid_argument& e) {
                std::cerr << e.what() << std::endl;
                return 1;
            } catch (std::out_of_range& e) {
                std::cerr << e.what() << std::endl;
                return -1;
            }
        } else if (flags == "load") {
            load = true;
            std::cin >> loadedFile;
        } else if (flags == "board") {
            board = true;
            std::cin >> boardFile;
        } else if (flags == "random-board") {
            decision = 3;
            randomBoard = true;
        }
    }

    if (load && board) {
        while (true) {
            std::cout << "Only 'load' or 'board', choose again." << std::endl;
            std::string temp;
            if (temp == "load") {
                finalFile = loadedFile;
                randomBoard = false;
                decision = 1;
                board = false;
                break;
            } else if (temp == "board") {
                finalFile = boardFile;
                randomBoard = false;
                decision = 2;
                load = false;
                break;
            }
        }
    }

    std::default_random_engine rng{seed};

    Game g;
    g.initializeGame(decision, finalFile, rng);
    // g.play();

    // below command is only for temp use, will be delated eventually
    string command;
    while (true) {
        std::cin >> command;
        if (command == "test") {
            std::cout << "Testing mode enabled!" << std::endl;
            g.newMain();
        } else if (command == "play") {
            std::cout << "Play mode enabled!" << std::endl;
            g.play();
        }
    }
}
