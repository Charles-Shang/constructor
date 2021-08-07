```{C++}
void Board::printBoard() {
    int vertex = 0;
    int edge = 0;
    int tileNum = 0;
    int tileNumForValue = 0;
    int tileNumForType = 0;
    int tileNumForGeese = 0;

    int col = 5;
    int row = 10;
    // 10 rows of block
    for (int a = 1; a <= row; ++a) {
        // 4 rows in each block
        for (int b = 1; b <= 4; ++b) {
            if (a <= row - 1 && a >= 3 && b == 1) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            // each row in 5 column
            for (int c = 1; c <= col; ++c) {
                // print blank block
                if (a == 1 && (c == 1 || c == col)) {  // top two cornors
                    std::cout << "  ";
                    ps();
                } else if ((a == 1 && c == col - 1) || (a == 2 && c == col) ||
                           (a == row && c == col)) {  // right
                    if (b == 1) {                     // frame
                        if (vertex < 10) {
                            std::cout << " ";
                        }
                        std::cout << vertex << "|       ";  // | with 7 spaces
                        ++vertex;
                    } else {
                        if (a == row) {
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
                           (a == row &&
                            c == 1)) {  // left (top x 2 and bottom x 1)
                    ps();
                    if (b == 1) {  // frame
                        std::cout << " |";
                    } else {
                        std::cout << "  ";
                    }
                } else if ((a == row - 1 && c == 1) ||
                           (a == row && c == 2)) {  // left (bottom x 2)
                    if (b == 1) {                   // frame
                        std::cout << vertex << "|--" << edge << "--|";
                        ++vertex;
                        ++edge;
                    } else {
                        std::cout << "  ";
                        ps();
                    }
                } else if ((a == row - 1 && c == col) ||
                           (a == row && c == col - 1)) {  // right (bottom x 2)
                    if (b == 1) {                         // frame
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
                    if (b == 1) {               // frame
                        if (vertex < 10) {
                            std::cout << " ";
                        }
                        std::cout << vertex << "|  ";
                        printTileValue(tiles[tileNumForValue].getTileValue());
                        ++tileNumForValue;
                        std::cout << "  |";
                        ++vertex;
                    } else {
                        if (b == 4) {
                            std::cout << " |";
                            ps();
                        } else if (b == 2) {
                            std::cout << " |  ";
                            if (tiles[tileNumForGeese].getHasGeese()) {
                                std::cout << "GEESE ";
                            } else {
                                std::cout << "      ";
                            }
                            ++tileNumForGeese;
                        } else {
                            if (edge < 10) {
                                std::cout << " ";
                            }
                            std::cout << edge;
                            ++edge;
                            ps();
                        }
                    }
                } else {           // non-empty blocks
                    if (b == 1) {  // frame
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
                        if (tileNum < 10) {
                            std::cout << " ";
                        }
                        std::cout << tileNum << "   ";  // 3 spaces
                        ++tileNum;
                        ++edge;
                    } else {
                        std::cout << " |  ";
                        printTileType(tiles[tileNumForType].getTileType());
                        ++tileNumForType;
                    }
                }
            }
            // right most edges
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
            } else if (a == row - 1 && b == 1) {
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
    std::cout << "--|" << vertex << "|" << std::endl;
}
```

