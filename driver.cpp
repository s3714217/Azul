//
//  main.cpp
//  Azul
//
//  Created by Thien Nguyen on 22/4/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//

#include <iostream>
#include "Player.h"
#include "Factories.h"
#include "ColorCode.h"
#include "Mosaic.h"

void loadGame(std::string filename)
{
    
    if(filename.size() > 0)
    {
      filename += ".save";
      filename = "save/"+filename;
      std::cout<<"Function unavailable"<<std::endl;
    }
    else
    {
      std::cout<<"Error: Please enter a valid filename!"<<std::endl;
    }
}


void saveGame(std::shared_ptr<Mosaic> mos1,std::shared_ptr<Mosaic> mos2,std::shared_ptr<Factories> fact ,std::string filename)
{
    if(filename.size() > 0)
    {
        filename += ".save";
        filename = "save/"+filename;
        std::cout<<"Function unavailable"<<std::endl;
    }
    else
    {
         std::cout<<"ERROR: Please enter a valid filename"<<std::endl;
    }
}


void startGame(std::shared_ptr<Mosaic> mosaic_1,std::shared_ptr<Mosaic> mosaic_2, std::shared_ptr<Factories> factories,bool newgame)
{

    if(newgame == true)
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
        
        mosaic_1= std::shared_ptr<Mosaic>(new Mosaic(player1));
        mosaic_2= std::shared_ptr<Mosaic>(new Mosaic(player2));
        factories = std::shared_ptr<Factories>(new Factories(2));
    }
    else
    {
        std::cout<<"CONTINUE THE GAME"<<std::endl;
        std::cout<<std::endl;
        
    }
    
    
    
    bool p1turn = true;
    bool nextp1turn = false;
     int round = 1;
    
    while(mosaic_1->winCheck() != true  && mosaic_2->winCheck() != true)
    {
        
        std::cout<<std::endl;
        std::cout<<"=== Start Round " <<round<<" ===";
        std::cout<<std::endl;
        p1turn = nextp1turn;
        std::string log = "";
        
        while(factories->isEmpty() != true)
        {
            
            factories->isEmpty();
            if(p1turn == true)
            {
                std::cout<<"TURN FOR PLAYER: "<<mosaic_1->getPlayer()->getName()<<"   ";
                std::cout<<"POINTS: "<<mosaic_1->getPlayer()->getPoint()<<std::endl;
                factories->PrintFactories();
                std::cout<<std::endl;
                mosaic_1->PrintMosaic();
                std::cout<<std::endl;
            }
    
            else
            {
                std::cout<<"TURN FOR PLAYER: "<<mosaic_2->getPlayer()->getName()<<"   ";
                std::cout<<"POINTS: "<<mosaic_2->getPlayer()->getPoint()<<std::endl;
                factories->PrintFactories();
                std::cout<<std::endl;
                mosaic_2->PrintMosaic();
                std::cout<<std::endl;
            }
            
            int fac = 0 , row =0 , n = 0;
            char c = ' ';
            std::string command;
            std::string filename;
            bool takefirst = false;
            
           bool validInput = false;
           std::cout << "> ";
           while(validInput != true)
           {
               command = "";
               fac = 99; row = 99; n=0;
               c = ' ';
            
            
            std::string input;
            
            std::cin.ignore(0);
            std::getline(std::cin, input);
             
            for(int x = 0; x<input.size(); x++)
            {
                if(command =="save")
                {
                    if(input[x] != ' ')
                    {
                        filename.push_back(input[x]);
                    }
                }
               if(x < 4)command.push_back(tolower(input[x]));
               else if(x == 5)fac = input[x]-48;
               else if(x == 7)c = toupper(input[x]);
               else if(x == 9)row = input[x]-48;
              
            }
               if(command =="turn")
               {
                   if(fac > 5|| 0 > fac ||0 >= row || row > 5 || c == FIRST_PLAYER)
                   {
                       std::cout<<"ERROR: Invalid Turn"<<std::endl;
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
                           std::cout<<"INFO: Turn Successful"<<std::endl;
                          
                       }
                       else
                       {
                           std::cout<<"ERROR: This Factory does not contain this Colour"<<std::endl;
                           std::cout << "> ";
                       }
                       
                   }

               }
               else if(command == "save")
               {
                   saveGame(mosaic_1, mosaic_2, factories,filename);
                   std::cout << "> ";
               }
               else if(command == "quit")
               {
                   std::cout<<std::endl;
                   std::cout<<"=== GAME ENDED ===";
                   std::cout<<std::endl;
                   return;
                   
               }
               else if(command.size() != 0)
               {
                   std::cout<<"ERROR: Invalid Command"<<std::endl;
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
                 nextp1turn = true;
               }
               mosaic_1->placeTile(row, c, n);
               p1turn = false;
               log += mosaic_1->getPlayer()->getName() + " > " +command+ " ";
               
           }
           else
           {
              if(takefirst == true)
              {
                 mosaic_2->placeTile(row, FIRST_PLAYER , n);
                 factories->removeFirst();
                 nextp1turn = false;
               }
               mosaic_2->placeTile(row, c, n);
               p1turn = true;
               log += mosaic_2->getPlayer()->getName() + " > " +command+ " ";
           }
            
            log += std::to_string(fac) + " ";
            log.push_back(c);
            log +=" " + std::to_string(row);
            log.push_back('\n');
        }
        
        std::cout<<"LOG: All turns happened "<<std::endl;
        std::cout<<log;
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
        round++;
    }
    std::cout<<std::endl;
    if(mosaic_1->getPlayer()->getPoint() > mosaic_2->getPlayer()->getPoint())
    {
        std::cout<<"Player "<<mosaic_1->getPlayer()<<" win the game!"<<std::endl;
    }
    else if(mosaic_1->getPlayer()->getPoint() < mosaic_2->getPlayer()->getPoint())
    {
        std::cout<<"Player "<<mosaic_2->getPlayer()<<" win the game!"<<std::endl;
    }
    else
    {
        std::cout<<"Draw!"<<std::endl;
    }
    
    std::cout<<std::endl;
    std::cout<<"=== GAME OVER ===";
    std::cout<<std::endl;
    
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
    std::cout<<"----------"<<std::endl;
    std::cout<<"1. New Game"<<std::endl;
    std::cout<<"2. Load Game"<<std::endl;
    std::cout<<"3. Credits "<<std::endl;
    std::cout<<"4. Quit"<<std::endl;
    std::cout<<std::endl;
    std::cout<<">";
    std::string command;
    std::cin>>command;
    
    std::shared_ptr<Mosaic> mosaic_1;
    std::shared_ptr<Mosaic> mosaic_2;
    std::shared_ptr<Factories> factories;
           
   if(command == "1")
   {
       std::cout<<std::endl;
       startGame(mosaic_1, mosaic_2,factories,true);
   }
   else if(command == "2")
   {
       std::string filename = " ";
       std::cout<<"Enter loading filename: ";
       std::cin>>filename;
       std::cout<<std::endl;
       loadGame(filename);
      
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
}


