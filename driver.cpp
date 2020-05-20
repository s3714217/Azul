//
//  main.cpp
//  Azul
//
//  Created by Thien Nguyen on 22/4/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//


#include "headers/driver.h"

void Azul::loadGame(std::string filename)
{
    
    if(filename.size() > 0)
    {
        
       filename += ".save";
       filename = "save/"+filename;
       std::string line;
       std::ifstream stream (filename);
        bool readingGame = false;
        bool readingMosaic = false;
        bool readingFactories = false;
        Mosaic* temp = nullptr;
        std::shared_ptr<Mosaic> mos1 = nullptr;
        std::shared_ptr<Mosaic> mos2 = nullptr;
        std::shared_ptr<Factories> fact = nullptr;
      if(stream.is_open())
      {
          while(getline(stream,line))
          {
             
              if(line == "game") readingGame = true;
              else if(line == "mosaic") readingMosaic = true;
              else if(line == "factories") readingFactories = true;
              
              if(readingGame == true)
              {
                  std::string type;
                  std::string input;
                  for(int x =0; x < (int) line.length(); x++)
                  {
                      if(line[x] != ' ')
                       {
                           input.push_back(line[x]);
                       }
                      else if(line[x] == ' ')
                      {
                          type = input;
                          input = "";
                          
                      }
                      if(x == (int)line.length()-1)
                      {
                          if(type == "active")
                          {
                              if(mos1->getPlayer()->getName() == input)
                              {
                                  mos1->setTurn(true);
                                  mos2->setTurn(false);
                              }
                              else if(mos2->getPlayer()->getName() == input)
                              {
                                  mos2->setTurn(true);
                                  mos1->setTurn(false);
                              }
                          }
                          else if(type == "turn")
                          {
                               int turn = std::stoi(input);
                           
                            this->startGame(mos1, mos2, fact, false, 0, turn);
                          }
                      }
                  }
                  
                  
                  if(line == "#")
                  {
                      readingGame = false;
                  }
              }
              else if(readingMosaic == true)
              {
                 
                  std::string type;
                  std::string input;
                  for(int x =0; x <(int) line.length(); x++)
                  {
                      if(line[x] != ' ')
                      {
                          input.push_back(line[x]);
                      }
                     else if(line[x] == ' ')
                     {
                         type = input;
                         input = "";
                         
                     }
                     if(x == (int)line.length()-1)
                     {
                        
                         if(type == "name")
                         {
                             temp = new Mosaic(new Player(input));
                         }
                         else if(type == "point")
                         {
                             int point = std::stoi(input);
                             temp->getPlayer()->setPoint(point);
                         }
                         else if(type == "turnboard")
                         {
                        
                             int line = 0;
                             int location =NUMBEROFTILE;
                             Tile** tempboard = new Tile*[BOARD_SIZE];
                             tempboard[0] = new Tile[BOARD_SIZE];
                             for(int y = 0; y < (int) input.length(); y++)
                             {
                                 if(input[y] != '|' && input[y] != ',')
                                 {
                                     if(input[y] == 'E')
                                     {
                                         tempboard[line][location] = ' ';
                                     }
                                     else
                                     {
                                         tempboard[line][location] = input[y];
                                     }
                                    
                                     location--;
                                 }
                                 else if(input[y] == '|')
                                 {
                                     location = NUMBEROFTILE;
                                     line++;
                                     if(line < BOARD_SIZE)
                                     {
                                        tempboard[line] = new Tile[BOARD_SIZE];
                                     }
                                  
                                 }
                                 if( y ==(int) input.length() -1)
                                 {
                                     for(int m = 0; m <= BOARD_SIZE-1; m++)
                                     {
                                         for(int n = BOARD_SIZE-1; n >= 0; n--)
                                         {
                                             if(m+n < BOARD_SIZE-1)
                                             {
                                                 
                                                 tempboard[m][n].setColour(' ');
                                             }
                                             else
                                             {
                
                                                 if(tempboard[m][n].getColour() == ' ')
                                                 {
                                                     tempboard[m][n].setColour(EMPTY);
                                                 }
                                             }
                                         }
                                     }
                                     temp->setTurnBoard(tempboard);
                                     
                                 }
                             }
                         }
                         else if(type == "pointboard")
                         {
                      
                              Tile** tempboard = new Tile*[BOARD_SIZE];
                              int nodecount = 0;
                              int currentline = 0;
                              tempboard[0] = new Tile[BOARD_SIZE];
                             
                             for(int y = 0; y <(int) input.length(); y++)
                             {
                                 if(input[y] != ',')
                                 {
                                     tempboard[currentline][nodecount] = input[y];
                                     nodecount++;
                                 }
                                 if(nodecount == 5)
                                 {
                                     nodecount = 0;
                                     currentline++;
                                     if(currentline < BOARD_SIZE)
                                     {
                                        tempboard[currentline] = new Tile[BOARD_SIZE];
                                     }
                                 }
                                 if( y == (int)input.length() -1)
                                 {
                                    
                                     temp->setPointBoard(tempboard);
                                     
                                 }
                             }
                            
                         }
                         else if(type == "broken")
                         {
                           
                             int brokenPts = 0;
                             if(input != "E")
                             {
                                 for(int y = 0; y < (int)input.length(); y++)
                                 {
                                     if(input[y] != ',')
                                     {
                                        
                                         temp->setBroken(new Tile(input[y]), brokenPts);
                                         if(input[y] == 'F')
                                         {
                                             temp->setFirst(true);
                                         }
                                         brokenPts++;
                                     }
                                        
                                      
                                 }
                                
                             }
                         }
                         else if(type == "remainder")
                         {
                             LinkedList* list = new LinkedList();
                             if(input != "E")
                             {
                                 
                                 for(int y = 0; y <(int) input.length(); y++)
                                 {
                                     if(input[y] != ',')
                                     {
                                         list->addBack(new Tile(input[y]));
                                     }
                                 }
                                 temp->setRemainder(list);
                             }
                         }
                         else if(type == "pointmap")
                         {
                             char** tempboard = new char*[BOARD_SIZE];
                             int nodecount = 0;
                             int currentline = 0;
                             tempboard[0] = new char[BOARD_SIZE];
                            
                            for(int y = 0; y <(int) input.length(); y++)
                            {
                                if(input[y] != ',')
                                {
                                    tempboard[currentline][nodecount] = input[y];
                                    nodecount++;
                                }
                                if(nodecount == 5)
                                {
                                    nodecount = 0;
                                    currentline++;
                                    if(currentline < BOARD_SIZE)
                                    {
                                        tempboard[currentline] = new char[BOARD_SIZE];
                                    }
                                }
                                if( y ==(int) input.length() -1)
                                {
                                    temp->setPointCalculator(tempboard);
                                }
                            }
                         }
                         
                     }
                      
                      
                  }
                  if(line == "#")
                  {
                      if(mos1 == nullptr)
                      {
                          mos1 =  std::shared_ptr<Mosaic>(temp);
                          
                      }
                      else
                      {
                          mos2 = std::shared_ptr<Mosaic>(temp);
                          
                      }
                      readingMosaic = false;
                  }
              }
              else if(readingFactories == true)
              {
                  std::string type;
                  std::string input;
                  
                  for(int x =0; x <(int) line.length(); x++)
                  {
                      if(line[x] != ' ')
                      {
                          input.push_back(line[x]);
                      }
                     else if(line[x] == ' ')
                     {
                         type = input;
                         input = "";
                     }
                     if(x ==(int) line.length()-1)
                     {
                         
                         if(type == "number")
                         {
                             fact = std::shared_ptr<Factories>(new Factories(std::stoi(input), -1));
                         }
                         else if(type == "factories")
                         {
                             Tile** tempboard = new Tile*[BOARD_SIZE];
                             int currentLine = 0;
                             int currentCol = 0;
                             tempboard[0] = new Tile[MAX_REMAIN * fact->getNumberOfFactory()];
                            
                             for(int y = 0; y <(int) input.length(); y++)
                             {
                                 if(input[y] != '|' && input[y] != ',' && input[y] != 'E')
                                 {
                                     tempboard[currentLine][currentCol] = input[y];
                                     currentCol++;
                                 }
                                 else if(input[y] == '|')
                                 {
                                     currentCol = 0;
                                     currentLine++;
                                     if(currentLine < NOFACTORY)
                                     {
                                        tempboard[currentLine] = new Tile[NUMBEROFTILE];
                                     }
                                 }
                                 if( y ==(int) input.length() -1)
                                 {
                                     fact->setFactories(tempboard);
                                 }

                             }
                         }
                         else if(type == "boxlid")
                         {

                             LinkedList* list = new LinkedList();
                             for(int y = 0; y < (int)input.length(); y++)
                             {
                                 if(input[y] != ',')
                                {
                                    list->addBack(new Tile(input[y]));
                                }
                                 if(y == (int)input.length() -1)
                                 {
                                     if(list->size() > 1)
                                     {
                                         fact->setBoxLid(list);
                                     }
                                 }
                             }
                             
                         }
                     }
                      
                  }
                  if(line == "#")
                  {
                      readingFactories = false;
                  }
              }
          }
          
          stream.close();
      }
      else
      {
          std::cout << "File can't be found"<<std::endl;
      }
    }
    else
    {
      std::cout<<"Error: Please enter a valid filename!"<<std::endl;
    }
}


void Azul::saveGame(std::shared_ptr<Mosaic> mos1,std::shared_ptr<Mosaic> mos2,std::shared_ptr<Factories> fact ,std::string filename, int round)
{
    if(filename.size() > 0)
    {
        std::string output;
       
        filename += ".save";
        filename = "save/"+filename;
        bool read1 = false;
        bool read2 = false;
        std::shared_ptr<Mosaic> readin = nullptr;
        
        while(read1 == false || read2 == false)
        {
            
            if(read1 == false)
            {
                readin = mos1;
                read1 = true;
            }
            else
            {
                readin = mos2;
                read2 = true;
            }
            
            output += "$\n";
            output += "mosaic\n";
            output += "name " + readin->getPlayer()->getName() + "\n";
            output += "point " + std::to_string(readin->getPlayer()->getPoint()) + "\n";
            bool containedTile = false;
            std::string TBoard;
            std::string PBoard;
            std::string PMap;
            for(int x = 0; x <BOARD_SIZE; x++)
            {
                for(int y = 0; y <BOARD_SIZE; y++)
                {
                    PBoard += readin->getPointBoard()[x][y].getColour();
                    PMap += readin->getPointCalculator()[x][y];
                    if(x < BOARD_SIZE -1 || y < BOARD_SIZE-1)
                    {
                        PMap += ",";
                        PBoard += ",";
                    }
                    if(readin->getTurnBoard()[x][y].getColour() != ' '
                       &&readin->getTurnBoard()[x][y].getColour() != '.')
                    {
                       
                        if(containedTile == true)
                        {
                            TBoard += ",";
                        }
                        else
                        {
                            containedTile = true;
                        }
                         TBoard += readin->getTurnBoard()[x][y].getColour();
                        
                    }
                }
                if(containedTile == false)
                {
                    TBoard += "E";
                }
                containedTile = false;
                if(x < BOARD_SIZE -1) TBoard +="|";
            }
    
            output += "turnboard "+TBoard+"\n";
            output += "pointboard "+PBoard+"\n";
            output += "broken ";
            for(int x =0; x <BROKEN_LEN; x++)
            {
                if(readin->getBroken(x) != nullptr)
                {
                    if(x > 0) output += ",";
                    output += readin->getBroken(x)->getColour();
                    
                }
                else
                {
                    if(x == 0)
                    {
                        output += "E";
                    }
                    x = BROKEN_LEN;
                }
            }
            output += "\n";
            output += "remainder ";
          
            if (readin->getRemainder()->size() ==0)
            {
                output += "E";
            }
            else
            {
                
                for(int x =0; x < readin->getRemainder()->size(); x++)
                {
                    Tile* temp = readin->getRemainder()->getFirst();
                    output += temp->getColour();
                    readin->getRemainder()->addBack(temp);
                    delete temp;
                    if(x < readin->getRemainder()->size()-1)output += ",";
                    
                }
            }
           
            output += "\n";
            output += "pointmap "+PMap+"\n";
            output += "#\n";
        }
        output += "$\n";
        output += "factories\n";
        output += "number " + std::to_string(NUMBEROFPLAYER) +"\n";
        output += "factories ";
        
        for(int x = 0; x < MAX_REMAIN * fact->getNumberOfFactory(); x++)
        {
            if(fact->getFactories()[0][x].getColour() != ' ')
            {
             if(x > 0) output += ",";
             output +=fact->getFactories()[0][x].getColour();
            
            }
        }
        output += "|";
        for(int x = 1; x < fact->getNumberOfFactory(); x++)
        {
            for(int y = 0; y < NUMBEROFTILE; y++)
            {
                if(fact->getFactories()[x][y].getColour() != ' ')
                {
                    output +=fact->getFactories()[x][y].getColour();
                    if(y < NUMBEROFTILE -1) output += ",";
                }
                else if(y == 0)
                {
                    output += "E";
                }
            }
            if(x < fact->getNumberOfFactory() -1) output += "|";
        }
        output += "\n";
        output += "boxlid ";
       
        for(int x =0 ; x < fact->getBoxLid()->size(); x++)
        {
            Tile* temp =fact->getBoxLid()->getFirst();
            output += temp->getColour();
            fact->getBoxLid()->addBack(temp);
            if(x < fact->getBoxLid()->size()-1) output+=",";
        }
        output += "\n";
        output += "#\n";
        
        output += "$\n";
        output += "game\n";
        if(mos1->isTurn() == true)
        {
            output += "active "+mos1 ->getPlayer()->getName() + "\n";
        }
        else
        {
            output += "active "+mos2 ->getPlayer()->getName() + "\n";
        }
        output += "turn " + std::to_string(round)+"\n";
        output += "#";
        
        std::ofstream stream;
        stream.open(filename);
        stream << output;
        stream.close();
        
        std::cout<<"INFO: Succesfully saved"<<std::endl;
    }
    else
    {
         std::cout<<"ERROR: Please enter a valid filename"<<std::endl;
    }
}



void Azul::startGame(std::shared_ptr<Mosaic> mosaic_1,std::shared_ptr<Mosaic> mosaic_2, std::shared_ptr<Factories> factories,bool newgame, int seed, int round)
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
        mosaic_1->setTurn(true);
        mosaic_2= std::shared_ptr<Mosaic>(new Mosaic(player2));
        mosaic_2->setTurn(false);
        factories = std::shared_ptr<Factories>(new Factories(2, seed));
       
    }
    else
    {
        std::cout<<"CONTINUE THE GAME"<<std::endl;
        std::cout<<std::endl;
        
    }
    
    while(mosaic_1->winCheck() != true  && mosaic_2->winCheck() != true)
    {
        
        std::cout<<std::endl;
        std::cout<<"=== Start Round " <<round<<" ===";
        std::cout<<std::endl;
        
       if(newgame == true)
       {
        if(mosaic_1->isFirst())
        {
            mosaic_1->setTurn(true);
            mosaic_2->setTurn(false);
        }
        else if(mosaic_2->isFirst())
        {
            mosaic_2->setTurn(true);
            mosaic_1->setTurn(false);
        }
       }
        std::string log = "";
        
        while(factories->isEmpty() != true)
        {
            
            factories->isEmpty();
            if(mosaic_1->isTurn() == true)
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
             
            for(int x = 0; x < (signed)input.size(); x++)
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
                           std::cout<<std::endl;
                          
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
                   saveGame(mosaic_1, mosaic_2, factories,filename,round);
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
            
           if(mosaic_1->isTurn() == true)
           {
               if(takefirst == true)
               {
                 mosaic_1->placeTile(row, FIRST_PLAYER , n);
                 factories->removeFirst();
               }
               mosaic_1->placeTile(row, c, n);
               mosaic_2->setTurn(true);
               mosaic_1->setTurn(false);
               log += mosaic_1->getPlayer()->getName() + " > " +command+ " ";
               
           }
           else if(mosaic_2->isTurn() == true)
           {
              if(takefirst == true)
              {
                 mosaic_2->placeTile(row, FIRST_PLAYER , n);
                 factories->removeFirst();
               }
               mosaic_2->placeTile(row, c, n);
               mosaic_2->setTurn(false);
               mosaic_1->setTurn(true);
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
       
        factories->setUp(seed);
        round++;
    }
    std::cout<<std::endl;
    if(mosaic_1->getPlayer()->getPoint() > mosaic_2->getPlayer()->getPoint())
    {
        std::cout<<"Player "<<mosaic_1->getPlayer()->getName()<<" wins the game!"<<std::endl;
    }
    else if(mosaic_1->getPlayer()->getPoint() < mosaic_2->getPlayer()->getPoint())
    {
        std::cout<<"Player "<<mosaic_2->getPlayer()->getName()<<" wins the game!"<<std::endl;
    }
    else
    {
        std::cout<<"Draw!"<<std::endl;
    }
    
    std::cout<<std::endl;
    std::cout<<"=== GAME OVER ===";
    std::cout<<std::endl;

    
}



void Azul::Menu(int seed)
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
       startGame(mosaic_1, mosaic_2,factories,true,seed,1);
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
       std::cout<<"StudentID: S3786798"<<std::endl;
       std::cout<<"Name: Rian Lenjik"<<std::endl;
       std::cout<<"Email: s3786798@student.rmit.edu.au"<<std::endl;
       std::cout<<std::endl;
       
       std::cout<<std::endl;
       std::cout<<"StudentID: S3784231"<<std::endl;
       std::cout<<"Name: An Dinh Uong"<<std::endl;
       std::cout<<"Email: s3784231@student.rmit.edu.au"<<std::endl;
       std::cout<<std::endl;
   }
   else if(command == "4")
   {
        std::cout << "Goodbye"<<std::endl;;
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

Azul::Azul(){
    
}
Azul::~Azul(){
    
}


int main(int argc, char *argv[]) {
   
    if(argc > 1)
       {
           Azul* azul = new Azul();
           int seed = *argv[1] - 48;
           azul->Menu(seed);
       }
       else
       {
           std::cout<<"Missing game seed"<<std::endl;
       }
   
}