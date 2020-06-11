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
    /*
    load game function that read the save files and initailize all objects
    start game with the read in object
    */
    
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
        Mosaic* mos[MAX_PLAYER];
        Factories* fac = nullptr;
        
        
        for(int x = 0; x < MAX_PLAYER; x++)
        {
            mos[x] = nullptr;
        }
        
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
                            
                              for(int k = 0; k < MAX_PLAYER; k++)
                              {
                                  if(mos[k] != nullptr && mos[k]->getPlayer()->getName()==input)
                                  {
                                     
                                      mos[k]->setTurn(true);
                                  }
                                  else if(mos[k] != nullptr)
                                  {
                                      
                                      mos[k]->setTurn(false);
                                  }
                                  
                              }
                            
                          }
                          else if(type == "turn")
                          {
                            int turn = std::stoi(input);
                            this->NUM_FAC = fac->getNumberOfFactory();
                              
                            this->startGame(mos, fac, false, 0, turn);
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
                             if(input[0] == 'A' && input[1] == 'I')
                             {
                                 temp->set_AI(true);
                             }
                             
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
                      
                      for(int k =0; k < MAX_PLAYER; k++)
                      {
                          if(mos[k] == nullptr)
                          {
                              mos[k] = temp;
                              k = MAX_PLAYER;
                          }
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
                             this->NUM_MOS =std::stoi(input);
                             fac = new Factories(std::stoi(input), -1);
                         }
                         else if(type == "factories")
                         {
                             Tile** tempboard = new Tile*[fac->getNumberOfFactory()];
                             int currentLine = 0;
                             int currentCol = 0;
                             
                             tempboard[0] = new Tile[MAX_REMAIN * fac->getNumberOfFactory()];
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
                                    
                                     if(currentLine < fac->getNumberOfFactory())
                                     {
                                        tempboard[currentLine] = new Tile[NUMBEROFTILE];
                                     }
                                 }
                                 if( y ==(int) input.length() -1)
                                 {
                                     fac->setFactories(tempboard);
                                 }

                             }
                         }
                         else if(type == "secondcentral")
                         {
                             Tile* temp = new Tile[MAX_REMAIN * fac->getNumberOfFactory()];
                             int location = 0;
                             for(int y = 0; y <(int) input.length(); y++)
                             {
                                 if(input[y] != ',' && input[y] != 'E')
                                 {
                                     temp[location] = input[y];
                                     location++;
                                 }
                             }
                             
                             fac->addSecondCentral();
                             fac->setSecondCentral(temp);
                             
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
                                         fac->setBoxLid(list);
                                         fac->setShuffled(true);
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
          //catch exception if no file can be found
          std::cout << "File can't be found"<<std::endl;
      }
    }
    else
    {
      
      std::cout<<"Error: Please enter a valid filename!"<<std::endl;
    }
}


void Azul::saveGame(Mosaic* all_mos[], Factories* all_fac,std::string filename, int round, int num)
{
    //write out all object to files
    if(filename.size() > 0)
    {
        std::string output;
       
        filename += ".save";
        filename = "save/"+filename;
        
        for(int k =0; k < this->NUM_MOS; k++)
        {
            Mosaic* readin = all_mos[k];
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
        output += "number " + std::to_string(this->NUM_MOS) +"\n";
        output += "factories ";
        
        for(int x = 0; x < MAX_REMAIN * all_fac->getNumberOfFactory(); x++)
        {
            if(all_fac->getFactories()[0][x].getColour() != ' ')
            {
             if(x > 0) output += ",";
             output +=all_fac->getFactories()[0][x].getColour();
            
            }
        }
        output += "|";
        for(int x = 1; x < all_fac->getNumberOfFactory(); x++)
        {
            for(int y = 0; y < NUMBEROFTILE; y++)
            {
                if(all_fac->getFactories()[x][y].getColour() != ' ')
                {
                    output +=all_fac->getFactories()[x][y].getColour();
                    if(y < NUMBEROFTILE -1) output += ",";
                }
                else if(y == 0)
                {
                    output += "E";
                }
            }
            if(x < all_fac->getNumberOfFactory() -1) output += "|";
        }
        output += "\n";
        if(all_fac->getSecondCentral() != nullptr)
        {
            output += "secondcentral ";
            for(int x = 0; x < MAX_REMAIN * all_fac->getNumberOfFactory(); x++)
            {
                if(all_fac->getSecondCentral()[x].getColour() != ' ')
                {
                    if(x > 0) output += ",";
                    output +=all_fac->getSecondCentral()[x].getColour();
                }
                else if(x == 0)
                {
                    output += "E";
                }
            }
            output += "\n";
        }
        output += "boxlid ";
       
        for(int x =0 ; x < all_fac->getBoxLid()->size(); x++)
        {
            Tile* temp =all_fac->getBoxLid()->getFirst();
            output += temp->getColour();
            all_fac->getBoxLid()->addBack(temp);
            if(x < all_fac->getBoxLid()->size()-1) output+=",";
        }
        output += "\n";
        output += "#\n";
        
        output += "$\n";
        output += "game\n";
       
        for(int k =0; k < this->NUM_MOS; k++)
        {
            if(all_mos[k]->isTurn())
            {
                output += "active "+ all_mos[k]->getPlayer()->getName() + "\n";
            }
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



void Azul::startGame(Mosaic* all_mos[], Factories* all_fac,bool newgame, int seed, int round)
{
    AI* ai = new AI(seed);
    bool loadedGame = false;
    //start the game
    if(newgame == true)
    {
        //if the game is a new game then initialize
     std::cout<<"START A NEW GAME"<<std::endl;
     std::cout<<std::endl;
     
    std::cout<<"ENTER NUMBER OF PLAYER:"<<std::endl<<C_CURSOR;
    int num = 0;
    std::string temp;
        bool valid = false;
        
            while(valid == false)
            {
                bool wrongf = false;
                try {
                std::cin>>temp;
                num = std::stoi(temp);
                }
                catch (const std::exception& e){
                    wrongf = true;
                    std::cout<<"ERROR: Invalid number format"<<std::endl<<">";
                }
                if(wrongf == false)
                {
                    if(num > 4 || num < 2)
                    {
                       std::cout <<"ERROR: Invalid number of player"<<std::endl<<">";
                    }
                    else if(num < 4 || num > 2)
                    {
                        this->NUM_MOS = num;
                        valid = true;
                        std::cout<<std::endl;
                    }
                }
            }
        
        
        Player* player1 = nullptr;
        Player* player2 = nullptr;
        Player* player3 = nullptr;
        Player* player4 = nullptr;
        bool ai_active2 = false;
        bool ai_active3 = false;
        bool ai_active4 = false;
        
        if(num >= 2)
        {
            
           std::cout<<"ENTER NAME FOR PLAYER 1:"<<std::endl<<C_CURSOR;
           std::cin>>temp;
           player1 = new Player(temp);
               temp = "";
           std::cout<<std::endl;
           
            //Ask if player want to play with AI
           std::cout<<"ENTER NAME FOR PLAYER 2 (Type 'AI' to make this player an AI):"<<std::endl<<C_CURSOR;
           std::cin>>temp;
            if(temp == "AI")
            {
                temp += "_2";
                ai_active2 = true;
                std::cout<<"AI activated!"<<std::endl;
            }
                player2 = new Player(temp);
                temp = "";
            
           std::cout<<std::endl;
           
        }
        if(num >= 3)
        {
            std::cout<<"ENTER NAME FOR PLAYER 3 (Type 'AI' to make this player an AI):"<<std::endl<<C_CURSOR;
            std::cin>>temp;
            if(temp == "AI")
            {
                temp += "_3";
                ai_active3 = true;
                std::cout<<"AI activated!"<<std::endl;
            }
            player3 = new Player(temp);
                 temp = "";
            std::cout<<std::endl;
        }
        if(num >= 4)
        {
            std::cout<<"ENTER NAME FOR PLAYER 4 (Type 'AI' to make this player an AI):"<<std::endl<<C_CURSOR;
            std::cin>>temp;
            if(temp == "AI")
            {
                temp += "_4";
                ai_active4 = true;
                std::cout<<"AI activated!"<<std::endl;
            }
            player4 = new Player(temp);
                 temp = "";
            std::cout<<std::endl;
        }
        all_fac = new Factories(num, seed);
        valid = false;
        std::cout<<"ADD SECOND CENTRAL FACTORY (Y/N): "<<std::endl<<C_CURSOR;
        while(!valid)
        {
            std::cin>>temp;
            if(temp == "Y")
            {
                all_fac->addSecondCentral();
                valid = true;
            }
            else if(temp == "N")
            {
                valid = true;
            }
            else
            {
                std::cout<<"ERROR: Please enter Y or N"<<std::endl;
                std::cout<<C_CURSOR;
            }
        }
           
            
           std::cout<<"Let's Play!"<<std::endl;
           std::cout<<std::endl;
               
        for(int k = 0; k < num; k++)
        {
            if(k == 1)
            {
                all_mos[k] = new Mosaic(player2);
                 if(ai_active2)
                 {
                     
                     all_mos[k]->set_AI(true);
                 }
            }
            else if(k == 2 && player3 != nullptr)
            {
                all_mos[k] = new Mosaic(player3);
                if(ai_active3)
                {
                    all_mos[k]->set_AI(true);
                }
            }
            else if(k == 3 && player4 != nullptr)
            {
                all_mos[k] = new Mosaic(player4);
                if(ai_active4)
                {
                    all_mos[k]->set_AI(true);
                }
            }
            else if(k == 0)
            {
                all_mos[k] = new Mosaic(player1);
                all_mos[k]->setTurn(true);
            }
            else
            {
                 all_mos[k]->setTurn(false);
            }
            
        }
    }
    else
    {
        //continue if the game is loaded
        std::cout<<"CONTINUE THE GAME"<<std::endl;
        std::cout<<std::endl;
        loadedGame = true;
    }
    
    while(!this->winGame(all_mos, this->NUM_MOS))
    {
        
        //The game run until one of 4 players win
        
        std::cout<<std::endl;
        std::cout<<"=== Start Round " <<round<<" ===";
        std::cout<<std::endl;
        
        std::string log = "";
       
        if(loadedGame == false)
        {
            if(round > 1)
            {
                for(int k =0; k < this->NUM_MOS; k++)
                {
                    if(all_mos[k]->isFirst())
                    {
                        all_mos[k]->setTurn(true);
                        all_mos[k]->setFirst(false);
                    }
                    else
                    {
                        all_mos[k]->setTurn(false);
                    }
                }
            }
        }
        else
        {
            loadedGame = true;
        }
            
        while(!this->endTurn(all_fac, this->NUM_FAC))
        {
            //The turn run until the factories is empty
            for(int k =0; k < this->NUM_MOS; k++)
            {
                if(all_mos[k]->isTurn())
                {
                    std::cout<<"TURN FOR PLAYER: "<<all_mos[k]->getPlayer()->getName()<<"   ";
                    std::cout<<"POINTS: "<<all_mos[k]->getPlayer()->getPoint()<<std::endl;
                    all_fac->PrintFactories();
                    std::cout<<std::endl;
                    all_mos[k]->PrintMosaic();
                    std::cout<<std::endl;
                }
            }
            int fac = 0 , row =0 , n = 0, central = -1;
            char c = ' ';
            std::string command;
            std::string filename;
            bool takefirst = false;
            
           bool validInput = false;
           std::cout << C_CURSOR<<" ";
            
           while(validInput != true)
           {
               command = "";
               fac = 99; row = 99; n=0;c = ' ';central = 0;
               
            
            
            std::string input = "";
  
               for(int k = 0; k < this->NUM_MOS; k++)
               {
                   if(all_mos[k]->isTurn() && all_mos[k]->is_AI_active())
                   {
                       
                       input = ai->generating_move(all_mos[k], all_fac);
                       std::cout<<input<<std::endl;
                   }
               }
               if(input == "")
               {
                   std::cin.ignore(0);
                   std::getline(std::cin, input);
               }
               
            for(int x = 0; x < (signed)input.size(); x++)
            {
                if(command =="save")
                {
                    if(input[x] != ' ')
                    {
                        filename.push_back(input[x]);
                    }
                }
                else if(command == "view")
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
               else if(x == 11)central = input[x]-48;
            }
               bool valid = true;
               if(command =="turn")
               {
                   if(all_fac->getSecondCentral() != nullptr)
                   {
                       if(central > 2 || central < 0)
                       {
                           std::cout<<"ERROR: Invalid central factory selected! Type 'help' to view all the command"<<std::endl;
                           valid = false;
                           std::cout <<C_CURSOR<<" ";
                       }
                   }
                   if(0 > fac || fac >= all_fac->getNumberOfFactory()||0 >= row || row > 5 || c == FIRST_PLAYER)
                   {
                       std::cout<<"ERROR: Invalid Turn! Type 'help' to view all the command"<<std::endl;
                       std::cout <<C_CURSOR<<" ";
                   }
                   else
                   {
                       
                       
                       if(fac ==0 && all_fac->isFirst() == true)
                       {
                           takefirst = true;
                       }
                      
                       n = all_fac->takeTile(c, fac, central);
                       
                       if(n != 0)
                       {
                           validInput = true;
                           std::cout<<"INFO: Turn Successful"<<std::endl;
                           std::cout<<std::endl;
                          
                       }
                       else if(valid == true)
                       {
                           std::cout<<"ERROR: This Factory does not contain this Colour"<<std::endl;
                           std::cout <<C_CURSOR<<" ";
                       }
                       
                   }

               }
               else if(command == "save")
               {
                   saveGame(all_mos, all_fac,filename,round, NUM_MOS);
                   std::cout <<C_CURSOR<<" ";
               }
               else if(command == "view")
               {
                   bool exist = false;
                   for(int k = 0; k < this->NUM_MOS; k++)
                   {
                       if(all_mos[k]->getPlayer()->getName() == filename)
                       {
                           all_mos[k]->PrintMosaic();
                           exist = true;
                       }
                   }
                   if(filename == "factories")
                   {
                       all_fac->PrintFactories();
                       exist = true;
                   }
                   if(exist == false)
                   {
                       std::cout<<"Cannot find the mosaic of this player"<<std::endl;
                   }
                   filename = "";
                   std::cout <<C_CURSOR<<" ";
               }
               else if (command == "help")
               {
                   std::cout<<std::endl;
                   std::cout<<"view <Player name> | View player mosaic"<<std::endl;
                   std::cout<<"turn <Factory> <Colour> <Row> <Central>| Take tile from factories and place into the mosaic"<<std::endl;
                   std::cout<<"save <filename> | Save game"<<std::endl;
                   std::cout<<"quit | Quit to main menu"<<std::endl;
                   std::cout<<std::endl;
                   std::cout <<C_CURSOR<<" ";
               }
               else if(command == "quit")
               {
                   std::cout<<std::endl;
                   std::cout<<"=== GAME ENDED ==="<<std::endl;
                   std::cout<<std::endl;
                   this->Menu(seed);
               }
               else if(command.size() != 0)
               {
                   std::cout<<"ERROR: Invalid Command! Type 'help' to view all the command"<<std::endl;
                   std::cout <<C_CURSOR<<" ";
               }
             
            if (std::cin.eof())
            {
                std::cout << " Goodbye." <<std::endl;
                std::exit(EXIT_SUCCESS);
            }
               
          }
            
            for(int k = 0; k < this->NUM_MOS; k++)
            {
                if(all_mos[k]->isTurn())
                {
                    if(takefirst)
                    {
                        all_mos[k]->placeTile(row, FIRST_PLAYER , n);
                        all_mos[k]->setFirst(true);
                        all_fac->removeFirst();
                        takefirst = false;
                    }
                    all_mos[k]->placeTile(row, c, n);
                    all_mos[k]->setTurn(false);
                    log += all_mos[k]->getPlayer()->getName() + " "+C_CURSOR+" " +command+ " ";
                    if(k < this->NUM_MOS-1)
                    {
                        all_mos[k+1]->setTurn(true);
                    }
                    else
                    {
                        all_mos[0]->setTurn(true);
                    }
                    k = this->NUM_MOS;
                }
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
       
        int len = 0;
        for(int k =0; k < this->NUM_MOS; k++)
        {
            all_mos[k]->turnCheck();
            len = all_mos[k]->returnTile()->size();
            for(int x =0; x <= len; x++)
            {
                all_fac->addRemain(all_mos[k]->returnTile()->getFirst());
            }
        }
       
        all_fac->setUp(seed);
        round++;
    
    }
    std::cout<<std::endl;
    std::string winner = "";
    int pts =0;
    for(int k = 0; k < this->NUM_MOS; k++)
    {
       if( all_mos[k]->getPlayer()->getPoint() > pts)
       {
           pts = all_mos[k]->getPlayer()->getPoint();
           winner = all_mos[k]->getPlayer()->getName();
       }
    }
    
    if(winner == "")
    {
        std::cout<<"Draw!"<<std::endl;
    }
    else
    {
        std::cout<<"Player "<<winner<<" wins the game!"<<std::endl;
    }
    
  
    ai->~AI();
    for(int k = 0; k < this->NUM_MOS; k++)
    {
        if(all_mos[k] != nullptr)
        {
            all_mos[k]->~Mosaic();
        }
    }
    all_fac->~Factories();
    
    std::cout<<std::endl;
    std::cout<<"=== GAME OVER ===";
    std::cout<<std::endl;
    this->Menu(seed);
}


//print UI menu
void Azul::Menu(int seed)
{
    //Print out general menu
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
    std::cout<<C_CURSOR;
    std::string command;
    std::cin>>command;
    
    Mosaic* all_mosaic[4];
    Factories* all_factories = nullptr;
       
           
   if(command == "1")
   {
       std::cout<<std::endl;
       startGame(all_mosaic, all_factories,true,seed,1);
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
        std::cout << " Goodbye"<<std::endl;;
        std::exit(EXIT_SUCCESS);
   }
        
   else if (std::cin.eof()) {
       std::cout << " Goodbye." <<std::endl;
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

bool Azul::winGame(Mosaic* all_mos[], int num)
{
    //loop through the mos to see if players meet the win condition
    for(int x =0; x < num;x++)
    {
        if(all_mos[x]->winCheck())
        {
            return true;
        }
    }

    return false;
}
bool Azul::endTurn(Factories* all_fac, int num)
{
    //check if the factories are empty to end a turn
        if(all_fac->isEmpty())
        {
            return true;
        }
        
    
    return false;
}


int main(int argc, char *argv[]) {
   
        if(argc > 1)
       {
           Azul* azul = new Azul();
           int seed = *argv[1] - 48;
           azul->Menu(seed);

           delete azul;

           return EXIT_SUCCESS;
       }
       else
       {
           std::cout<<"Missing game seed"<<std::endl;
       }

    
}
