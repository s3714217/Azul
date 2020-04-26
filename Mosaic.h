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
    void setBroken(Tile* broken[]);
    void setPointCalculator(char** pointCalculator);
    
    
private:
    
    void pointCalculation();
    
    Player* player;
    Tile** pointBoard;
    Tile** turnBoard;
    LinkedList* remainder;
    Tile* broken[7];
    char** pointCalculator;
    
    bool containedFirst = false;
    int brokenPts = 0;
    bool won = false;

};


#endif /* Mosaic_hpp */
