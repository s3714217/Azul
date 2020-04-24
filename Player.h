//
//  Player.hpp
//  Azul
//
//  Created by Thien Nguyen on 22/4/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//

#ifndef Player_h
#define Player_h
#include <string>
#include <iostream>

class Player{
    
public:
    Player(std::string name);
    ~Player();
    void setPoint(int pts);
    int getPoint();
    void printInfo();
    std::string getName();
    
private:
    std::string name;
    int point;
    
    };

#endif /* Player_hpp */
