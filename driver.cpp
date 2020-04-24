//
//  main.cpp
//  Azul
//
//  Created by Thien Nguyen on 22/4/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//

#include <iostream>
#include "LinkedList.h"
#include "Player.h"
#include "Factories.h"
#include "ColorCode.h"
#include "Mosaic.h"

void loadGame()
{
    
}

void saveGame()
{
    
}


void startGame()
{
     std::cout<<"START A NEW GAME"<<std::endl;
     std::cout<<std::endl;
     
    std::cout<<"ENTER NAME FOR PLAYER 1:"<<std::endl<<">";
    std::string temp;
    std::cin>>temp;
    Player* player1 = new Player(temp);
    std::cout<<std::endl;
    
    std::cout<<"ENTER NAME FOR PLAYER 2:"<<std::endl<<">";
    std::cin>>temp;
    Player* player2 = new Player(temp);
    std::cout<<std::endl;
    
    std::cout<<"Let's Play!"<<std::endl;
    std::cout<<std::endl;
    
    
    
    Factories* factories = new Factories(2);
    Mosaic* mosaic_1 = new Mosaic(player1);
    Mosaic* mosaic_2 = new Mosaic(player2);
    
    bool p1turn = true;
    bool nextp1turn = false;
    
    while(mosaic_1->winCheck() != true  && mosaic_2->winCheck() != true)
    {
        mosaic_1->placeTile(1, RED, 1);
        mosaic_1->turnCheck();
        mosaic_1->placeTile(1, LIGHT_BLUE, 1);
        mosaic_1->turnCheck();
        mosaic_1->placeTile(1, DARK_BLUE, 1);
        mosaic_1->turnCheck();
        mosaic_1->placeTile(1, YELLOW, 1);
        mosaic_1->turnCheck();
        mosaic_1->placeTile(1, BLACK, 1);
        mosaic_1->turnCheck();
        
     
        factories->isEmpty();
        std::cout<<std::endl;
        std::cout<<"=== Start Round ===";
        std::cout<<std::endl;
        p1turn = nextp1turn;
        
        while(factories->isEmpty() != true)
        {
            factories->isEmpty();
            if(p1turn == true)
            {
                std::cout<<"TURN FOR PLAYER:" <<mosaic_1->getPlayer()->getName()<<std::endl;
                factories->PrintFactories();
                std::cout<<std::endl;
                mosaic_1->PrintMosaic();
                std::cout<<std::endl;
            }
    
            else
            {
                std::cout<<"TURN FOR PLAYER : "<<mosaic_2->getPlayer()->getName()<<std::endl;
                factories->PrintFactories();
                std::cout<<std::endl;
                mosaic_2->PrintMosaic();
                std::cout<<std::endl;
            }
            
            int fac = 0 , row =0 , n = 0;
            char c = ' ';
            bool takefirst = false;
            
           bool validInput = false;
           std::cout << "> ";
           while(validInput != true)
           {
               fac = 99; row = 99; n=0;
               c = ' ';
            
            std::string command;
            std::string input;
            
            std::cin.ignore(0);
            std::getline(std::cin, input);
             
            for(int x = 0; x<input.size(); x++)
            {
               if(x < 4)command.push_back(input[x]);
               else if(x == 5)fac = input[x]-48;
               else if(x == 7)c = input[x];
               else if(x == 9)row = input[x]-48;
            }
               
               if(command =="Turn")
               {
                   if(fac > 5 || row > 5 || c == FIRST_PLAYER)
                   {
                       std::cout<<"Invalid Input"<<std::endl;
                       std::cout << "> ";
                   }
                   else
                   {
                       
                       if(fac ==0 && factories->isFirst() == true)
                       {
                           takefirst = true;
                       }
                       n = factories->takeTile(c, fac);
                    
                       if(n != 0)
                       {
                           validInput = true;
                           std::cout<<"Turn Successful"<<std::endl;
                          
                       }
                       else
                       {
                           std::cout<<"This Factory does not contain this Colour"<<std::endl;
                           std::cout << "> ";
                       }
                       
                   }

               }
               else if(command.size() != 0)
               {
                   std::cout<<"Invalid Command"<<std::endl;
                   std::cout << "> ";
               }
             
            if (std::cin.eof())
            {
                std::cout << "Goodbye." <<std::endl;
                std::exit(EXIT_SUCCESS);
            }
               
          }
            
           if(p1turn == true)
           {
               if(takefirst == true)
               {
                 mosaic_1->placeTile(row, FIRST_PLAYER , n);
                 factories->removeFirst();
                 takefirst = false;
                 nextp1turn = true;
               }
               mosaic_1->placeTile(row, c, n);
               p1turn = false;
               
           }
           else
           {
              if(takefirst == true)
              {
                 mosaic_2->placeTile(row, FIRST_PLAYER , n);
                 factories->removeFirst();
                 takefirst = false;
                 nextp1turn = false;
               }
               mosaic_2->placeTile(row, c, n);
               p1turn = true;
           }
        }
        std::cout<<std::endl;
        std::cout<<"=== End of Round ===";
        std::cout<<std::endl;
        
        mosaic_1->turnCheck();
        mosaic_2->turnCheck();
        int len = mosaic_1->returnTile()->size();
        for(int x =0; x <= len; x++)
        {
          factories->addRemain(mosaic_1->returnTile()->getFirst());
            
        }
        len = mosaic_2->returnTile()->size();
        for(int x =0; x <= len; x++)
        {
          factories->addRemain(mosaic_2->returnTile()->getFirst());
           
        }
       
        factories->setUp();
        
    
    std::cout<<std::endl;
    std::cout<<"===GAME OVER===";
    std::cout<<std::endl;
    }
}



void Menu()
{
    std::cout<<" WELCOME TO AZUL!"<<std::endl;
    std::cout<<"------------------------"<<std::endl;
    bool exit = false;
    while(exit != true)
    {
   
    std::cout<<std::endl;
    std::cout<<"Menu"<<std::endl;
    std::cout<<"--------"<<std::endl;
    std::cout<<"1. New Game"<<std::endl;
    std::cout<<"2. Load Game"<<std::endl;
    std::cout<<"3. Credits "<<std::endl;
    std::cout<<"4. Quit"<<std::endl;
    std::cout<<std::endl;
    std::cout<<">";
    std::string command;
    std::cin>>command;
    
    
   if(command == "1")
   {
       std::cout<<std::endl;
       startGame();
   }
   else if(command == "2")
   {
       std::cout<<"Unavailable"<<std::endl;
   }
   else if(command == "3")
   {
        std::cout<<"------CREDITS------"<<std::endl;
       
        std::cout<<std::endl;
        std::cout<<"StudentID: S3714217"<<std::endl;
        std::cout<<"Name: Thien Nguyen"<<std::endl;
        std::cout<<"Email: s3714217@student.rmit.edu.au"<<std::endl;
        std::cout<<std::endl;
       
       std::cout<<std::endl;
       std::cout<<"StudentID: "<<std::endl;
       std::cout<<"Name: "<<std::endl;
       std::cout<<"Email: "<<std::endl;
       std::cout<<std::endl;
       
       std::cout<<std::endl;
       std::cout<<"StudentID: "<<std::endl;
       std::cout<<"Name: "<<std::endl;
       std::cout<<"Email: "<<std::endl;
       std::cout<<std::endl;
   }
   else if(command == "4")
   {
        std::cout << "Goodbye";
        std::exit(EXIT_SUCCESS);
   }
        
   else if (std::cin.eof()) {
       std::cout << "Goodbye." <<std::endl;
       std::exit(EXIT_SUCCESS);
    }
   else
   {
       std::cout << "Invalid input";
   }
        

    
    
    std::cout<<std::endl;
    }
}


int main() {
   
     Menu();
    
//    Mosaic* mos = new Mosaic(new Player("a"));
//   // Factories fac = new Factories(2);
//    std::cout<<mos->placeTile(1, RED, 1);
//    mos->PrintMosaic();
//
//    mos->turnCheck();
//    mos->placeTile(1, RED, 1);
//
//    mos->PrintMosaic();
}


