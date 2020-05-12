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

class Azul{
   
public:
    Azul();
    ~Azul();
    
    void Menu(int seed);
    void startGame(std::shared_ptr<Mosaic> mosaic_1,std::shared_ptr<Mosaic> mosaic_2, std::shared_ptr<Factories> factories,bool newgame, int seed, int round);
    void saveGame(std::shared_ptr<Mosaic> mos1,std::shared_ptr<Mosaic> mos2,std::shared_ptr<Factories> fact ,std::string filename, int round);
    void loadGame(std::string filename);
    
    
};

#endif /* driver_h */
