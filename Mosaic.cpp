//
//  Mosaic.cpp
//  Azul
//
//  Created by Thien Nguyen on 23/4/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//

#include "headers/Mosaic.h"

Mosaic::Mosaic(Player* player)
{
    this->player = player;
    this->pointBoard = new Tile*[BOARD_SIZE];
    this->turnBoard = new Tile*[BOARD_SIZE];
    this->pointCalculator = new char*[BOARD_SIZE];
    this->colourCounting = new bool[NUMBEROFCOLOUR];
    for(int x =0; x < 5; x++)
    {
        this->turnBoard[x] = new Tile[x+1];
        this->pointBoard[x] = new Tile[BOARD_SIZE];
        this->pointCalculator[x] = new char[BOARD_SIZE];
    }
    
    for(int x=0; x< BOARD_SIZE; x++)
    {
        for(int y = 0; y <BOARD_SIZE; y++)
        {
            this->pointCalculator[x][y] = EMPTY;
        }
    }
    
    for(int x = 0; x <= BOARD_SIZE-1; x++)
    {
        for(int y = BOARD_SIZE-1; y >= 0; y--)
        {
            if(x+y < BOARD_SIZE-1)
            {
                 this->turnBoard[x][y].setColour(' ');
            }
            else
            {
                this->turnBoard[x][y].setColour(EMPTY);
            }
            
        }
    }
     
    for(int x = 0; x <= BOARD_SIZE-1; x++)
    {
       
        
        this->pointBoard[x][x] =    EMPTY_DARK_BLUE;
        this->pointBoard[x][x+1] =  EMPTY_YELLOW;
        this->pointBoard[x][x+2] =  EMPTY_RED;
        this->pointBoard[x][x+3] =  EMPTY_BLACK;
        this->pointBoard[x][x+4] =  EMPTY_LIGHT_BLUE;
        
        this->pointBoard[x][x-1] =  EMPTY_LIGHT_BLUE;
        this->pointBoard[x][x-2] =  EMPTY_BLACK;
        this->pointBoard[x][x-3] =  EMPTY_RED;
        this->pointBoard[x][x-4] =  EMPTY_YELLOW;
    }
    
    remainder = new LinkedList();
    for(int x =0; x < BROKEN_LEN; x++)
    {
        this->broken[x] = nullptr;
    }
}

Mosaic::~Mosaic()
{
    player->~Player();
    for(int x =0; x < BOARD_SIZE; x++)
    {
        delete this->pointBoard[x];
        delete this->turnBoard[x];
        delete this->pointCalculator[x];
    }
    for(int x =0; x < BROKEN_LEN;x++)
    {
        delete broken[x];
    }
    delete this->remainder;
}

bool Mosaic::isFirst()
{
    return this->containedFirst;
}

bool Mosaic::placeTile(int row, Colour c, int number)
{
    row -= 1;
    if(c == FIRST_PLAYER)
    {
        this->containedFirst = true;
        this->broken[this->brokenPts] = new Tile(c);
        this->brokenPts++;
        return true;
    }
    
    bool valid = false;
    for(int x = 0; x <BOARD_SIZE; x++)
    {
       if(this->pointBoard[row][x].getColour() == tolower(c))
       {
           valid = true;
       }
        
    }
    for(int x = 0; x <BOARD_SIZE; x++)
    {
        if(this->turnBoard[row][x].getColour() != EMPTY
        && this->turnBoard[row][x].getColour() != c
        && this->turnBoard[row][x].getColour() != ' ')
        {
            valid = false;
        }
    }
    
    if(valid == true)
    {
        for (int x =0; x <= BOARD_SIZE; x++)
        {
           
            if(this->turnBoard[row][5-x].getColour() == EMPTY && number != 0)
            {
                this->turnBoard[row][5-x] = c;
                number--;
            }
        }
        if(number != 0)
        {
            
            for(int x =0; x < number; x++)
            {
                if(brokenPts < BROKEN_LEN)
                {
                    
                    this->broken[this->brokenPts] = new Tile(c);
                    this->brokenPts++;

                }
            }
        }
        return valid;
        
    }
    
    else
    {   if(number != 0)
    {
        for(int x =0; x < number; x++)
        {
            if(brokenPts < BROKEN_LEN)
            {
                this->broken[this->brokenPts] = new Tile(c);
                this->brokenPts++;
                
            }
        }
    }
        return valid;
    }
    
}

void Mosaic::turnCheck()
{
    
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        bool fullrow = true;
        Colour c = EMPTY;
        for (int y = BOARD_SIZE-1; y >= 0; y--)
        {
            if(this->turnBoard[x][y].getColour() == EMPTY)
            {
                fullrow = false;
            }
            else if(this->turnBoard[x][y].getColour() != ' ')
            {
                c = this->turnBoard[x][y].getColour();
            }
        }
        
        if(fullrow == true)
        {
            for (int y = BOARD_SIZE-1; y >= 0; y--)
            {
                if(this->turnBoard[x][y].getColour() != ' ' && y < NUMBEROFTILE)
                {
                    this->turnBoard[x][y].setColour(EMPTY);
                    remainder->addBack(new Tile(c));
                }
                
                if(this->pointBoard[x][y].getColour() == tolower(c))
                {
                    this->pointBoard[x][y].setColour(c);
                    this->pointCalculator[x][y] = OCCUPIED;
                }
            }
            this->turnBoard[x][NUMBEROFTILE].setColour(EMPTY);
        }
    }
    this->pointCalculation();
   
}


bool Mosaic::winCheck()
{
    for(int x =0; x < BOARD_SIZE; x++)
    {
        bool fullrow = true;
        
        for(int y =0; y < BOARD_SIZE; y++)
        {
            if(this->pointBoard[x][y].getColour() == tolower(this->pointBoard[x][y].getColour()))
            {
                fullrow = false;
            }
           
        }
        
        if(fullrow)
        {
            return true;
        }
    }
    
    return false;
}

LinkedList* Mosaic::returnTile()
{
    for(int x = 0; x < brokenPts; x++)
    {
        if(this->broken[x]->getColour() != FIRST_PLAYER)
        {
            this->remainder->addBack(broken[x]);
            this->broken[x] = new Tile(' ');
        }
    }
    this->brokenPts = 0;
    return this->remainder;
}

Player* Mosaic::getPlayer()
{
    return this->player;
}

void Mosaic::PrintMosaic()
{
    std::cout <<"Mosaic for "<<this->player->getName()<<std::endl;
    
    for(int x =0; x < BOARD_SIZE; x++)
    {
        std::cout <<x+1<<": ";
        
        for (int y =0; y < BOARD_SIZE ;y++ )
        {
            std::cout <<this->turnBoard[x][y].getColour();
            std::cout <<"  ";
        }
        std::cout <<"||";
        for (int y =0; y < BOARD_SIZE ;y++ )
        {
            std::cout <<"  ";
            std::cout <<this->pointBoard[x][y].getColour();
            
        }
        
        std::cout <<std::endl;
    }
    
    std::cout <<"broken: ";
    for(int x = 0; x < BROKEN_LEN; x++)
    {
        if(broken[x] != nullptr)
        {
            std::cout<<broken[x]->getColour()<<" ";
            std::cout <<" ";
        }
    }
    std::cout <<std::endl;
}

void Mosaic::pointCalculation()
{
    int point = this->player->getPoint();
    std::vector<int> checkX;
    std::vector<int> checkY;
    bool horizontal = true;
    bool vertical = true;
    
   
    for(int x = 0; x < BOARD_SIZE; x++)
    {
        for(int y = 0; y < BOARD_SIZE; y++)
        {
            if(pointCalculator[x][y] == OCCUPIED)
            {
                checkX.push_back(x);
                checkY.push_back(y);
            }
        }
    }
    
    for(int n = 0; n < (signed)checkX.size(); n++)
    {
        pointCalculator[checkX[n]][checkY[n]] = COUNTED;
        bool horizontaladded = false;
        bool verticaladded = false;
        
        for(int m = checkY[n]+1; m < BOARD_SIZE; m++)
        {
            if(pointCalculator[checkX[n]][m] == COUNTED)
            {
                point++;
                
                if(m == checkY[n]+1)
                {
                    horizontaladded = true;
                    point++;
                }
            }
            else
            {
                m = 5;
                horizontal = false;
            }
        }
        
        for(int m = checkY[n]-1; m >= 0; m--)
        {
            if(pointCalculator[checkX[n]][m] == COUNTED)
           {
              
               point++;
               
               if(horizontaladded == false)
               {
                   horizontaladded = true;
                   point++;
               }
           }
           else
           {
               m = 0;
               horizontal = false;
           }
           
        }
        
       

        for(int m = checkX[n]+1; m <  BOARD_SIZE; m++)
        {
           if(pointCalculator[m][checkY[n]] == COUNTED)
           {
               point++;
               if(m == checkX[n]+1)
               {
                   verticaladded = true;
                   point++;
               }
           }
           else
           {
               m = 5;
               vertical = false;
           }
        }
        for(int m = checkX[n]-1; m >= 0; m--)
        {
           if(pointCalculator[m][checkY[n]] == COUNTED)
           {
               
               point++;
               if(verticaladded == false)
               {
                   verticaladded = true;
                   point++;
               }
           }
           else
           {
               m = 0;
               vertical = false;
           }
        }
        
        if(verticaladded == false && horizontaladded == false)
        {
            verticaladded = true;
            point++;
        }
        
        
        if(vertical == true)
        {
            point += 7;
        }
        if(horizontal == true)
        {
            point +=2;
        }
       
    }
    
    
    for (int x = 0; x <= brokenPts; x++)
    {
       if(broken[x] != nullptr)
       {
         if(x < 2) point--;
         else if(x < 5) point-=2;
         else point -=3;
       }
       else
       {
           x = brokenPts+1;
       }
        
    }
    
    int UCount = 0;
    int LCount = 0;
    int BCount = 0;
    int YCount = 0;
    int RCount = 0;
    
    for(int x = 0; x <  BOARD_SIZE; x++)
    {
        for(int y = 0; y <  BOARD_SIZE; y++)
        {
            if(this->pointBoard[x][y].getColour() == RED) RCount++;
            else if(this->pointBoard[x][y].getColour() == LIGHT_BLUE) LCount++;
            else if(this->pointBoard[x][y].getColour() == DARK_BLUE) BCount++;
            else if(this->pointBoard[x][y].getColour() == YELLOW) YCount++;
            else if(this->pointBoard[x][y].getColour() == BLACK) UCount++;
        }
    }
   // std::cout<<UCount;
    if(UCount == 5 && this->colourCounting[0] == false) {point+=10; this->colourCounting[0] = true;}
    if(LCount == 5 && this->colourCounting[1] == false) {point+=10; this->colourCounting[1] = true;}
    if(BCount == 5 && this->colourCounting[2] == false) {point+=10; this->colourCounting[2] = true;}
    if(YCount == 5 && this->colourCounting[3] == false) {point+=10; this->colourCounting[3] = true;}
    if(RCount == 5 && this->colourCounting[4] == false) {point+=10; this->colourCounting[4] = true;}
    
    this->player->setPoint(point);
}

void Mosaic::setPlayer(Player *player)
{
    this->player = player;
}
void Mosaic::setPointBoard(Tile **pointBoard)
{
    this->pointBoard = pointBoard;
    int UCount = 0;
    int LCount = 0;
    int BCount = 0;
    int YCount = 0;
    int RCount = 0;
    
    for(int x = 0; x <  BOARD_SIZE; x++)
    {
        for(int y = 0; y <  BOARD_SIZE; y++)
        {
            switch (pointBoard[x][y].getColour())
            {
                case RED: RCount++;
                case BLACK: UCount++;
                case LIGHT_BLUE: LCount++;
                case DARK_BLUE: BCount++;
                case YELLOW: YCount++;
            }
        }
    }
    if(UCount == 5 && this->colourCounting[0] == false) this->colourCounting[0] = true;
    if(LCount == 5 && this->colourCounting[1] == false) this->colourCounting[1] = true;
    if(BCount == 5 && this->colourCounting[2] == false) this->colourCounting[2] = true;
    if(YCount == 5 && this->colourCounting[3] == false) this->colourCounting[3] = true;
    if(RCount == 5 && this->colourCounting[4] == false) this->colourCounting[4] = true;
    
}
void Mosaic::setTurnBoard(Tile **turnBoard)
{
    this->turnBoard = turnBoard;
}
void Mosaic::setRemainder(LinkedList *remainder)
{
    this->remainder = remainder;
}
void Mosaic::setBroken(Tile* broken[])
{
    for(int x =0; x <  brokenPts; x++)
    {
        this->broken[x] = broken[x];
        
        if(broken[x] != nullptr)
        {
            brokenPts++;
            if(broken[x]->getColour() == FIRST_PLAYER)
            {
                this->containedFirst = true;
            }
        }
        
    }
}
void Mosaic::setPointCalculator(char **pointCalculator)
{
    this->pointCalculator = pointCalculator;
    
    
}


Tile** Mosaic::getPointBoard()
{
    return this->pointBoard;
}
Tile** Mosaic::getTurnBoard()
{
   return this->turnBoard;
}
LinkedList* Mosaic::getRemainder()
{
    return this->remainder;
}
Tile* Mosaic::getBroken(int index)
{
    return this->broken[index];
}
char** Mosaic::getPointCalculator()
{
    return this->pointCalculator;
}


