//
//  Factories.cpp
//  Azul
//
//  Created by Thien Nguyen on 22/4/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//

#include "Factories.h"

Factories::Factories(int numberOfPlayer)
{
    if(numberOfPlayer == 2)
    {
        this->numberOfFactory = 6;
        
    }
    
    TileBag = new LinkedList();
    BoxLid = new LinkedList();
    
    factories = new Tile*[this->numberOfFactory];
    
    this->factories[0] = new Tile[this->numberOfFactory * MAX_REMAIN];
    
    for(int x = 1; x != this->numberOfFactory; x++)
    {
        this->factories[x] = new Tile[4];
    }
    
    this->setUp();
}

Factories::~Factories()
{
    this->TileBag->~LinkedList();
    this->BoxLid->~LinkedList();
    this->numberOfFactory = 0;
    
    for(int x = 0; x != this->numberOfFactory; x++)
    {
        delete this->factories[x];
    }
    delete this->factories;
}

int Factories::takeTile(Colour c, int factory)
{
    int numberOfTile = 0;
    if(factory != 0)
    {
        if(this->ContainColour(c, factory) )
        {
            for(int x =0; x < 4; x++)
            {
                if(this->factories[factory][x].getColour() == c)
                {
                    numberOfTile++;
                    this->factories[factory][x] = ' ';
                }
                else
                {
                    this->factories[0][this->leftover] = this->factories[factory][x].getColour();
                    this->factories[factory][x] = ' ';
                    this->leftover++;
                }
            }
        }
    }
    else
    {
        
        
        if(this->ContainColour(c, factory) )
        {
            for(int x =0; x < this->numberOfFactory * MAX_REMAIN; x++)
            {
                if(this->factories[factory][x].getColour() == c)
                {
                    numberOfTile++;
                    this->factories[factory][x] = ' ';
                }
            }
        }
    }
    size -= numberOfTile;
    return numberOfTile;
}

bool Factories::ContainColour(Colour c, int factory)
{
    if(factory != 0)
    {
        for(int x =0; x < 4; x++)
        {
            if(this->factories[factory][x].getColour() == c)
            {
                return true;
            }
        }
    }
    else
    {
        for(int x =0; x < this->numberOfFactory * MAX_REMAIN; x++)
        {
            if(this->factories[factory][x].getColour() == c)
            {
                return true;
            }
        }
    }
    return false;
}

void Factories::addRemain(Tile *tile)
{
   if(tile->getColour() != FIRST_PLAYER)
   {
    this->BoxLid->addBack(tile);
   }
}

void Factories::PrintFactories()
{
    std::cout <<"Factories: "<<std::endl;
    std::cout << 0 <<": ";
    for(int y =0; y < this->numberOfFactory*MAX_REMAIN; y++)
    {
        if(this->factories[0][y].getColour() != ' ')
        {
            std::cout <<this->factories[0][y].getColour()<<" ";
        }
    }
    std::cout <<std::endl;
    for(int x =1; x < this->numberOfFactory; x++)
    {
        std::cout << x <<": ";
        for(int y =0; y < 4; y++)
        {
           std::cout <<this->factories[x][y].getColour()<<" ";
        }
        std::cout <<std::endl;
    }
    std::cout <<std::endl;
}

void Factories::setUp()
{
    this->factories[0][0] = FIRST_PLAYER;
    
    for(int x =0; x != 20; x++)this->BoxLid->addBack(new Tile(RED));
    for(int x =0; x != 20; x++)this->BoxLid->addBack(new Tile(BLACK));
    for(int x =0; x != 20; x++)this->BoxLid->addBack(new Tile(YELLOW));
    for(int x =0; x != 20; x++)this->BoxLid->addBack(new Tile(DARK_BLUE));
    for(int x =0; x != 20; x++)this->BoxLid->addBack(new Tile(LIGHT_BLUE));
    
    this->BoxLid->shuffle();
    for(int x =0; x != 4*(this->numberOfFactory -1); x++)this->TileBag->addFront(this->BoxLid->getFirst());
    
    size = (5 * 4) +1;
    
    for(int x = 1; x < this->numberOfFactory; x++)
    {
        for(int y = 0; y<4; y++)
        {
            this->factories[x][y] = TileBag->getFirst()->getColour();
        }
    }
    
}

void Factories::reset()
{
    this->factories[0][0] = FIRST_PLAYER;
    this->BoxLid->shuffle();
    for(int x =0; x != 4*(this->numberOfFactory -1); x++)this->TileBag->addFront(this->BoxLid->getFirst());
    size = (5 * 4) +1;
    
    for(int x = 1; x < this->numberOfFactory; x++)
    {
        for(int y = 0; y<4; y++)
        {
            this->factories[x][y] = TileBag->getFirst()->getColour();
        }
    }
    this->first = true;
}

bool Factories::isEmpty()
{
   if(size != 0)
   {
       return false;
   }
    return true;
}

void Factories::removeFirst()
{
    factories[0][0] = ' ';
    this->first = false;
    this->size -=1;
    std::cout << "test";
}

bool Factories::isFirst()
{
    return this->first;
}
