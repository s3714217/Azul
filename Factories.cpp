//
//  Factories.cpp
//  Azul
//
//  Created by Thien Nguyen on 22/4/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//

#include "headers/Factories.h"

//Constructor
Factories::Factories(int numberOfPlayer, int seed)
{
   /*
    Initializing number of factories according to number of player
    Initializing TileBag and BoxLid as LinkedList
    Adding 100 Tiles of different Colours (25 each) to the BoxLid   
    Set up the factories with input seed
   */
    if(numberOfPlayer == 2)
    {
        this->numberOfFactory = TWO_P_FAC;
    }
    else if(numberOfPlayer == 3)
    {
         this->numberOfFactory = THREE_P_FAC;
    }
    else if(numberOfPlayer == 4)
    {
        this->numberOfFactory = FOUR_P_FAC;
    }
    
    TileBag = new LinkedList();
    BoxLid = new LinkedList();
    factories = new Tile*[this->numberOfFactory];
    
    this->factories[0] = new Tile[this->numberOfFactory * MAX_REMAIN];
    
    for(int x = 1; x < this->numberOfFactory; x++)
    {
        this->factories[x] = new Tile[NUMBEROFTILE];
    }
        Tile* red = new Tile(RED);
        Tile* black = new Tile(BLACK);
        Tile* dark_b = new Tile(DARK_BLUE);
        Tile* yellow = new Tile(YELLOW);
        Tile* light_b = new Tile(LIGHT_BLUE);

       for(int x =0; x != 20; x++)this->BoxLid->addBack(red);
       for(int x =0; x != 20; x++)this->BoxLid->addBack(black);
       for(int x =0; x != 20; x++)this->BoxLid->addBack(dark_b);
       for(int x =0; x != 20; x++)this->BoxLid->addBack(yellow);
       for(int x =0; x != 20; x++)this->BoxLid->addBack(light_b);

   if(seed > -1)
   {
     this->setUp(seed);
   }

}
//Destructor
Factories::~Factories()
{
    //delete all pointers
    BoxLid->~LinkedList();
    TileBag->~LinkedList();

    this->numberOfFactory = 0;
    
    for(int x = 0; x != this->numberOfFactory; x++)
    {
        delete this->factories[x];
    }
    delete this->factories;
}

void Factories::addSecondCentral()
{
    this->secondCentral = new Tile[this->numberOfFactory * MAX_REMAIN];
    this->secondCentral[0] = FIRST_PLAYER;
}

int Factories::takeTile(Colour c, int factory, int central)
{
    /*
    Removing a Tile from the factories
    - checking if the tile existed
    - return the number of tiles in that factories
    - return 0 if no tiles found
    */
    
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
                    if(this->secondCentral != nullptr && central == 2)
                    {
                        this->secondCentral[this->leftover_second] = this->factories[factory][x].getColour();
                        this->factories[factory][x] = ' ';
                        this->leftover_second++;
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
    }
    else
    {
        if(secondCentral != nullptr && central == 2)
        {
            for(int x =0; x < this->numberOfFactory * MAX_REMAIN; x++)
            {
                if(this->secondCentral[x].getColour() == c)
                {
                    numberOfTile++;
                    this->secondCentral[x] = ' ';
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
    }
    size -= numberOfTile;
    return numberOfTile;
}

bool Factories::ContainColour(Colour c, int factory)
{
    /*
    check if the factory containing the colour
    */
    if(factory != 0)
    {
        for(int x =0; x < NUMBEROFTILE; x++)
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
    /*
        Adding all the remain tiles from the mosaic to the boxlid
    */
   if(tile != nullptr && tile->getColour() != FIRST_PLAYER)
   {
    this->BoxLid->addBack(tile);
   }
}

void Factories::PrintFactories()
{
    /*
        Print out the all factories
    */
    std::cout <<"Factories: "<<this->size<<" tiles left"<<std::endl;
    std::cout << 0 <<"(1): ";
    for(int y =0; y < this->numberOfFactory*MAX_REMAIN; y++)
    {
        if(this->factories[0][y].getColour() != ' ')
        {
            std::cout <<this->getConsoleColour(this->factories[0][y].getColour())<<" ";
        }
    }
    std::cout <<std::endl;
    if(this->secondCentral != nullptr)
    {
        std::cout << 0 <<"(2): ";
        for(int y =0; y < this->numberOfFactory*MAX_REMAIN; y++)
        {
            if(this->secondCentral[y].getColour() != ' ')
            {
                std::cout <<this->getConsoleColour(this->secondCentral[y].getColour())<<" ";
            }
        }
        std::cout <<std::endl;
    }
    
    for(int x =1; x < this->numberOfFactory; x++)
    {
        std::cout << x <<": ";
        for(int y =0; y < NUMBEROFTILE; y++)
        {
           std::cout <<this->getConsoleColour(this->factories[x][y].getColour())<<" ";
        }
        std::cout <<std::endl;
    }
    std::cout <<std::endl;
}

void Factories::setUp(int seed)
{
    /*
    Set up the boxlid by shuffling (once at the start of the game)
    Add certain number of tile to TileBag
    TileBag distributing the tiles to all factories
    */
    this->leftover = 1;
    this->leftover_second = 1;
    for(int x = 1; x < this->numberOfFactory * MAX_REMAIN; x++)
    {
        this->factories[0][x] = ' ';
    }
     this->factories[0][0] = FIRST_PLAYER;
   
    if(this->secondCentral != nullptr)
    {
        this->secondCentral[0] =FIRST_PLAYER;
    }
    if(shuffled == false)
    {
        this->BoxLid->shuffle(seed);
        shuffled =true;
    }
    
    for(int x =0; x < NUMBEROFTILE*(this->numberOfFactory -1); x++)
    {
        Tile* temp = this->BoxLid->getFirst();
        if(temp != nullptr)
        {
            this->TileBag->addFront(temp);
        }
    }
    size = 1;
    if(secondCentral != nullptr)
    {
        size += 1;
    }
        for(int x = 1; x < this->numberOfFactory; x++)
        {
        for(int y = 0; y<4; y++)
        {
            size++;
            Tile* temp = TileBag->getFirst();
            if(temp != nullptr)
            {
                this->factories[x][y] = temp->getColour();
            }
        }
        }
        this->first = true;
    

}



bool Factories::isEmpty()
{
  //Check if the factories is empty to end a round
   if(size > 0)
   {
       return false;
   }
    return true;
}

void Factories::removeFirst()
{
    //Remove the first tile
    if(secondCentral != nullptr)
    {
        secondCentral[0] = ' ';
        this->size -= 1;
    }
    factories[0][0] = ' ';
    this->first = false;
    this->size -=1;
}

bool Factories::isFirst()
{
    //setter for first player tile
    return this->first;
}

void Factories::setShuffled(bool s)
{
    //setter for if the boxlid is shuffled
    this->shuffled = s;
}

void Factories::setTileBag(LinkedList* TileBag)
{
    //setter for TileBag
    this->TileBag = TileBag;
}
void Factories::setBoxLid(LinkedList *BoxLid)
{
    //setter for BoxLid
    this->BoxLid = BoxLid;
}
void Factories::setSecondCentral(Tile* second)
{
    this->secondCentral = second;
    this->leftover_second = 1;
   
    
    for(int x = 0; x < MAX_REMAIN*this->numberOfFactory;x++)
    {
        if(this->secondCentral[x].getColour() != ' ' )
        {
            this->size++;
            this->leftover_second++;
            if(this->factories[0][x].getColour() == FIRST_PLAYER)
            {
                this->first = true;
            }
        }
    }
    
}
void Factories::setNumberOfFactory(int numberOfFactory)
{
    //setter for Number of factories
    this->numberOfFactory = numberOfFactory;
}
void Factories::setFactories(Tile **factories)
{
    //setter for factories
    
    this->factories = factories;
    int size = 0;
    int left = 0;
    
    for(int x =1; x < this->numberOfFactory; x++)
    {
        for(int y =0; y < NUMBEROFTILE; y++)
        {
            if(this->factories[x][y].getColour() != ' ')
            {
                size++;
            }
        }
    }
   
    for(int x = 0; x < MAX_REMAIN*this->numberOfFactory;x++)
    {
        if(this->factories[0][x].getColour() != ' ')
        {
            left++;
            if(this->factories[0][x].getColour() == FIRST_PLAYER)
            {
                this->first = true;
            }
        }
    }
    
    
    this->size = size +left;
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

Tile* Factories::getSecondCentral()
{
    return this->secondCentral;
}

std::string Factories::getConsoleColour(char c)
{
    std::string s = "";
    if(c == BLACK)
    {
        s = C_BLACK;
        s.push_back(c);
        s += NORMAL;
        return s;
    }
    if(c == RED)
    {
        s = C_RED;
        s.push_back(c);
        s += NORMAL;
        return s;
    }
    if(c == DARK_BLUE)
    {
        s = C_DARK_BLUE;
        s.push_back(c);
        s += NORMAL;
        return s;
    }
    if(c == LIGHT_BLUE)
    {
        s = C_LIGHT_BLUE;
        s.push_back(c);
        s += NORMAL;
        return s;
    }
    if(c == YELLOW)
    {
         s = C_YELLOW;
         s.push_back(c);
         s += NORMAL;
         return s;
    }
    if(c == FIRST_PLAYER)
    {
        return C_FIRST_PLAYER;
    }
    return "";
    
}

