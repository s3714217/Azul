//
//  AI.cpp
//  Azul
//
//  Created by Thien Nguyen on 26/5/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
///Users/thiennguyen/Desktop/Azul/Azul/AI.cpp

#include "headers/AI.h"

AI::AI(int seed)
{
    this->seed = seed;
}
AI::~AI()
{
    
}

//Generating 'appropriated' move command
std::string AI::generating_move(Mosaic *mos, Factories *fac)
{
    /*
        The function will scan and add all possible moves to list of solution
        Then every solution in list_solution will be sorted to lv1, lv2 and not_recommended list based on
            1. The excess tiles
            2. The constrain of rows on the wall
            3. The constrain of rows on play board
        - Tiles with acceptable number of excess tiles will be place to lv1
        - The solution that cause more broken tiles will be place to lv2 or not_recommended list
     
    @return solution in order if solution exist list_solution > lv1 > lv2 > not_recommended
     */
    //reading in the current Mosiac and Factories
    std::default_random_engine e(seed);
    std::string command = "turn";
    std::vector<Solution*> list_solution = this->get_ini_solution(mos, fac);
    std::vector<Solution*> list_solution_lv1;
    std::vector<Solution*> list_solution_lv2;
    std::vector<Solution*> not_recommended;
    
    int number_of_node[BOARD_SIZE] = {0,0,0,0,0};
    char colour_of_row[BOARD_SIZE] = {' ',' ',' ',' ',' '};
    char constrain_of_row[BOARD_SIZE][NUMBEROFCOLOUR];
    /*
     filtering all good moves from the list of solution
     adding all the bad moves to not recommended list
     */
    for(int x =0; x < BOARD_SIZE; x++)
    {
        for(int y =0; y < BOARD_SIZE; y++)
        {
            if(mos->getTurnBoard()[x][y].getColour() != ' ')
            {
                if(mos->getTurnBoard()[x][y].getColour() != EMPTY)
                {
                    number_of_node[x] += 1;
                    colour_of_row[x] = mos->getTurnBoard()[x][y].getColour();
                }
            }
            if(mos->getPointBoard()[x][y].getColour() == RED)
            {
                constrain_of_row[x][0] = RED;
            }
            else if(mos->getPointBoard()[x][y].getColour() == BLACK)
            {
                constrain_of_row[x][1] = BLACK;
            }
            else if(mos->getPointBoard()[x][y].getColour() == YELLOW)
            {
                constrain_of_row[x][2] = YELLOW;
            }
            else if(mos->getPointBoard()[x][y].getColour() == LIGHT_BLUE)
            {
                constrain_of_row[x][3] = LIGHT_BLUE;
            }
            else if(mos->getPointBoard()[x][y].getColour() == DARK_BLUE)
            {
                constrain_of_row[x][4] = DARK_BLUE;
            }
            
        }
    }
    int len = (signed) list_solution.size();
    for(int x = 0; x < len; x++)
    {
        Solution* s = list_solution[x];
        int excess = s->row - s->count - number_of_node[s->row-1] ;
        if(excess < 0)
        {
            if(excess == -1)
            {
                list_solution_lv1.push_back(s);
                list_solution[x] = nullptr;
            }
            else if (excess == -2)
            {
                list_solution_lv2.push_back(s);
                list_solution[x] = nullptr;
            }
            else
            {
                not_recommended.insert(not_recommended.begin(),s);
                list_solution[x] = nullptr;
            }
        }
        if(list_solution[x] != nullptr)
        {
            if(excess > 0)
            {
                if(excess == 1)
                {
                    list_solution_lv1.insert(list_solution_lv1.begin(),s);
                    list_solution[x] = nullptr;
                }
                else if (excess == 2)
                {
                    list_solution_lv2.insert(list_solution_lv2.begin(),s);
                    list_solution[x] = nullptr;
                }
                else
                {
                    not_recommended.insert(not_recommended.begin(),s);
                    list_solution[x] = nullptr;
                }
            }
        }
        if(list_solution[x] != nullptr)
        {
            
            if(colour_of_row[s->row] != ' ' && colour_of_row[s->row] != s->color)
            {
               
               not_recommended.push_back(s);
               list_solution[x] = nullptr;
            }
        }
        if(list_solution[x] != nullptr)
        {
            for(int y =0; y < NUMBEROFCOLOUR; y++)
            {
                if(constrain_of_row[s->row][y] == s->color)
                {
                 
                    not_recommended.push_back(s);
                    list_solution[x] = nullptr;
                }
            }
        }
    }
    
    
    /*
     get one of the solution in a good moves list
     if there is no good solution then get first solution from lv1 then lv2 then not recommend list
     */
    
    //std::shuffle(list_solution.begin(), list_solution.end(), e);
        
    for(Solution* s: list_solution)
    {
        if(s != nullptr)
        {
            
            command += " " +std::to_string(s->fac) +
            " " +s->color+
            " " +std::to_string(s->row);
            if(s->central == 2)
            {
                command += " "+std::to_string(s->central);
                
            }
            return command;
        }
    }
    if(list_solution_lv1.size() > 0)
    {
        command += " " +std::to_string(list_solution_lv1.back()->fac) +
        " " +list_solution_lv1.back()->color+
        " " +std::to_string(list_solution_lv1.back()->row);
        if(list_solution_lv1.back()->central == 2)
        {
            command += " "+std::to_string(not_recommended.at(0)->central);
        }
        return command;
    }
    else if (list_solution_lv2.size() > 0)
    {
        command += " " +std::to_string(list_solution_lv2.back()->fac) +
        " " +list_solution_lv2.back()->color+
        " " +std::to_string(list_solution_lv2.back()->row);
        if(list_solution_lv2.back()->central == 2)
        {
            command += " "+std::to_string(not_recommended.at(0)->central);
        }
        return command;
    }
    
        command += " " +std::to_string(not_recommended.back()->fac) +
        " " +not_recommended.back()->color+
        " " +std::to_string(not_recommended.back()->row);
        if(not_recommended.back()->central == 2)
        {
            command += " "+std::to_string(not_recommended.at(0)->central);
        }
        return command;
    
}

//generating all possible move for AI
std::vector<Solution*> AI::get_ini_solution(Mosaic *mos, Factories *fac)
{
       std::vector<Solution*> list_solution;
       int times =fac->getNumberOfFactory();
       if(fac->getSecondCentral() != nullptr)
       {
           times += 1;
       }
         for(int y = 0; y < times; y++)
         {
             int RCount = 0;
             int YCount = 0;
             int UCount = 0;
             int BCount = 0;
             int LCount = 0;
             int len = 0;
             if(y >=1 )
             {
                 len = NUMBEROFTILE;
             }
             else
             {
                 len = MAX_REMAIN*fac->getNumberOfFactory();
             }
                 for(int x =0; x < len; x++)
                 {
                     char c = ' ';
                     if(fac->getSecondCentral() != nullptr && y == fac->getNumberOfFactory())
                     {
                        c = fac->getSecondCentral()[x].getColour();
                     }
                     else
                     {
                        c = fac->getFactories()[y][x].getColour();
                     }
                     if( c != ' ')
                     {
                         if(c == RED)
                         {
                             RCount++;
                         }
                         else if(c == YELLOW)
                         {
                             YCount++;
                         }
                         else if(c == BLACK)
                         {
                             UCount++;
                             
                         }
                         else if(c == DARK_BLUE)
                         {
                             BCount++;
                             
                         }
                         else if(c == LIGHT_BLUE)
                         {
                             LCount++;
                         }
                      
                     }
                 }
             if(RCount > 0)
             {
                 for(int x = 1; x <= BOARD_SIZE; x++)
                 {
                     Solution* s = new Solution(x,y,RED,RCount);
                     if(fac->getSecondCentral() != nullptr && y == fac->getNumberOfFactory())
                     {
                         s->fac= 0;
                         s->central = 2;
                     }
                      list_solution.push_back(s);
                 }
             }
             if(YCount > 0)
             {
                 for(int x = 1; x <= BOARD_SIZE; x++)
                 {
                     Solution* s = new Solution(x,y,YELLOW,YCount);
                     if(fac->getSecondCentral() != nullptr && y == fac->getNumberOfFactory())
                     {
                         s->fac= 0;
                         s->central = 2;
                     }
                     list_solution.push_back(s);
                 }
             }
             if(UCount > 0)
             {
                 for(int x = 1; x <= BOARD_SIZE; x++)
                 {
                     Solution* s = new Solution(x,y,BLACK,UCount);
                     if(fac->getSecondCentral() != nullptr && y == fac->getNumberOfFactory())
                     {
                         s->fac= 0;
                         s->central = 2;
                     }
                     list_solution.push_back(s);
                 }
             }
             if(BCount > 0)
             {
                 for(int x = 1; x <= BOARD_SIZE; x++)
                 {
                     Solution* s = new Solution(x,y,DARK_BLUE,BCount);
                     if(fac->getSecondCentral() != nullptr && y == fac->getNumberOfFactory())
                     {
                         s->fac= 0;
                         s->central = 2;
                     }
                     list_solution.push_back(s);
                 }
             }
             if(LCount > 0)
             {
                 for(int x = 1; x <= BOARD_SIZE; x++)
                 {
                     Solution* s = new Solution(x,y,LIGHT_BLUE,LCount);
                     if(fac->getSecondCentral() != nullptr && y == fac->getNumberOfFactory())
                     {
                         s->fac= 0;
                         s->central = 2;
                     }
                    
                     list_solution.push_back(s);
                 }
             }
         }
    
    return list_solution;
}

//class represent a solution for AI
Solution::Solution(int row, int fac, char color, int count)
{
    this->row = row;
    this->fac = fac;
    this->color = color;
    this->count = count;
    this->central = 0;
}
Solution::~Solution()
{
    
}
