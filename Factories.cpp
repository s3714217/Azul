//
//  Factories.cpp
//  Azul
//
//  Created by Thien Nguyen on 22/4/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//

#include "headers/Factories.h"

Factories::Factories(int numberOfPlayer, int seed)
{
    if(numberOfPlayer == 2)
    {
        this->numberOfFactory = NOFACTORY;
        
    }
    
    TileBag = new LinkedList();
    BoxLid = new LinkedList();
    
    factories = new Tile*[this->numberOfFactory];
    
    this->factories[0] = new Tile[this->numberOfFactory * MAX_REMAIN];
    
    for(int x = 1; x < this->numberOfFactory; x++)
    {
        this->factories[x] = new Tile[4];
    }
    
    for(int x =0; x != 20; x++)this->BoxLid->addBack(new Tile(RED));
       for(int x =0; x != 20; x++)this->BoxLid->addBack(new Tile(BLACK));
       for(int x =0; x != 20; x++)this->BoxLid->addBack(new Tile(YELLOW));
       for(int x =0; x != 20; x++)this->BoxLid->addBack(new Tile(DARK_BLUE));
       for(int x =0; x != 20; x++)this->BoxLid->addBack(new Tile(LIGHT_BLUE));
    
    this->setUp(seed);
}

Factories::~Factories()
{
    delete TileBag;
    delete BoxLid;
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
   if(tile != nullptr && tile->getColour() != FIRST_PLAYER)
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

void Factories::setUp(int seed)
{
    
    this->leftover = 1;
    
    for(int x = 1; x < this->numberOfFactory * MAX_REMAIN; x++)
    {
        this->factories[0][x] = ' ';
    }
    this->factories[0][0] = FIRST_PLAYER;
   
    if(shuffled == false)
    {
        this->BoxLid->shuffle(seed);
        shuffled =true;
    }
    
    for(int x =0; x < 4*(this->numberOfFactory -1); x++)
    {
        Tile* temp = this->BoxLid->getFirst();
        if(temp != nullptr)
        {
            this->TileBag->addFront(temp);
        }
    }
    size = 1;
    
    for(int x = 1; x < this->numberOfFactory; x++)
    {
        for(int y = 0; y<4; y++)
        {
            size++;
            this->factories[x][y] = TileBag->getFirst()->getColour();
        }
    }
    this->first = true;
    
}



bool Factories::isEmpty()
{
   if(size > 0)
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
}

bool Factories::isFirst()
{
    return this->first;
}


void Factories::setTileBag(LinkedList* TileBag)
{
    this->TileBag = TileBag;
}
void Factories::setBoxLid(LinkedList *BoxLid)
{
    this->BoxLid = BoxLid;
}
void Factories::setNumberOfFactory(int numberOfFactory)
{
    this->numberOfFactory = numberOfFactory;
}
void Factories::setFactories(Tile **factories)
{
    this->factories = factories;
    int size = 0;
    int left = 0;
    for(int x =0; x < 5; x++)
    {
        for(int y =0; y < 5; y++)
        {
            if(this->factories[x][y].getColour() != ' ')
            {
                size++;
            }
            if(this->factories[0][y].getColour() == FIRST_PLAYER)
            {
                this->first = true;
            }
            else  if(this->factories[0][y].getColour() != ' ')
            {
                left++;
            }
        }
    }
    this->size = size;
    this->leftover = left;
}

LinkedList* Factories::getTileBag()
{
    return this->TileBag;
}

LinkedList* Factories::getBoxLid()
{
    return this->BoxLid;
}
int Factories::getNumberOfFactory()
{
    return this->numberOfFactory;
}
Tile** Factories::getFactories()
{
    return this->factories;
}
