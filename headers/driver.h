//
//  driver.h
//  Azul
//
//  Created by Thien Nguyen on 12/5/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//

#ifndef driver_h
#define driver_h

#include <iostream>
#include <fstream>
#include <memory>
#include <chrono>
#include "Player.h"
#include "Factories.h"
#include "ColorCode.h"
#include "Mosaic.h"
#include "AI.h"
class Azul{
   
public:
    Azul();
    ~Azul();
    
    void Menu(int seed);
    void startGame(Mosaic* all_mos[], Factories* all_fac,bool newgame, int seed, int round);
    void saveGame(Mosaic* all_mos[], Factories* all_fac,std::string filename, int round, int num);
    void loadGame(std::string filename);
    bool winGame(Mosaic* all_mos[], int num);
    bool endTurn(Factories* all_fac, int num);
    
private:
    int NUM_MOS = 0;
    int NUM_FAC = 0;
    
};

#endif /* driver_h */
