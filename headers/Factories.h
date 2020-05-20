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


class Factories{
    
public:
    Factories(int numberOfPlayer, int seed);
    ~Factories();
    int takeTile(Colour c, int factory);
    void addRemain(Tile* tile);
    void PrintFactories();
    bool ContainColour(Colour c, int factory);
    bool isEmpty();
    void removeFirst();
    bool isFirst();
    void setUp(int seed);
    
    void setTileBag(LinkedList* TileBag);
    void setBoxLid(LinkedList* BoxLid);
    void setNumberOfFactory(int numberOfFactory);
    void setFactories(Tile** factories);
    
    LinkedList* getTileBag();
    LinkedList* getBoxLid();
    int getNumberOfFactory();
    Tile** getFactories();
    
private:
    
    
    LinkedList* TileBag;
    LinkedList* BoxLid;
    int numberOfFactory;
    Tile** factories;
    int leftover = 1;
    bool first;
    int size = 0;
    bool shuffled = false;
};
#endif /* Factories_hpp */