//
//  Mosaic.hpp
//  Azul
//
//  Created by Thien Nguyen on 23/4/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//

#ifndef Mosaic_h
#define Mosaic_h
#include "ColorCode.h"
#include "LinkedList.h"
#include "Player.h"
#include <iostream>

class Mosaic{
    
public:
    Mosaic(Player* player);
    ~Mosaic();
    bool placeTile(int row, Colour c, int number);
    void turnCheck();
    bool winCheck();
    void PrintMosaic();
    bool isFirst();
    bool isTurn();
    LinkedList* returnTile();
    
    
    Player* getPlayer();
    Tile** getPointBoard();
    Tile** getTurnBoard();
    LinkedList* getRemainder();
    Tile* getBroken(int index);
    char** getPointCalculator();
    
    void setPlayer(Player* player);
    void setPointBoard(Tile** pointBoard);
    void setTurnBoard(Tile** turnBoard);
    void setRemainder(LinkedList* remainder);
    void setBroken(Tile* tile, int location);
    void setPointCalculator(char** pointCalculator);
    void setTurn(bool turn);
    void setFirst(bool first);
    
private:
    
    void pointCalculation();
    
    Player* player;
    Tile** pointBoard;
    Tile** turnBoard;
    LinkedList* remainder;
    Tile* broken[BROKEN_LEN];
    char** pointCalculator;
    bool* colourCounting;
    
    bool currentTurn = false;
    bool containedFirst = false;
    int brokenPts = 0;

};


#endif /* Mosaic_hpp */
