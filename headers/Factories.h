//
//  Factories.hpp
//  Azul
//
//  Created by Thien Nguyen on 22/4/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//

#ifndef Factories_h
#define Factories_h

#include "ColorCode.h"
#include "LinkedList.h"
#include <iostream>
#include <cstdio>


class Factories{
    
public:
    Factories(int numberOfPlayer, int seed);
    ~Factories();
    int takeTile(Colour c, int factory, int central);
    void addRemain(Tile* tile);
    void PrintFactories();
    bool ContainColour(Colour c, int factory);
    bool isEmpty();
    void removeFirst();
    bool isFirst();
    void setUp(int seed);
    void addSecondCentral();
    
    void setTileBag(LinkedList* TileBag);
    void setBoxLid(LinkedList* BoxLid);
    void setNumberOfFactory(int numberOfFactory);
    void setFactories(Tile** factories);
    void setShuffled(bool s);
    void setSecondCentral(Tile* second);
    
    std::string getConsoleColour(char c);
    
    Tile* getSecondCentral();
    LinkedList* getTileBag();
    LinkedList* getBoxLid();
    int getNumberOfFactory();
    Tile** getFactories();
     int size = 0;
    
private:
    
    
    LinkedList* TileBag;
    LinkedList* BoxLid;
    int numberOfFactory;
    Tile** factories;
    int leftover = 1;
    int leftover_second = 1;
    bool first;
   
    bool shuffled = false;
    Tile* secondCentral = nullptr;
    
};
#endif /* Factories_hpp */
