//
//  Player.cpp
//  Azul
//
//  Created by Thien Nguyen on 22/4/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//

#include "headers/Player.h"

//Constructor
Player::Player(std::string name)
{
    this->name = name;
    this->point = 0;
}

//Destructor
Player::~Player()
{
    this->name = "";
    this->point = 0;
    
}

//Sets a player's point
void Player::setPoint(int pts)
{
   if(pts >= 0)this->point = pts;
    
   else this->point = 0;
}

//Gets a player's point
int Player::getPoint()
{
    return this->point;
}

//Gets a player's name
std::string Player::getName()
{
    return this->name;
}

void Player::printInfo()
{
    /*
     * Prints a player's info (name and point)
     */
    std::cout <<"Name: "<<this->name<<std::endl;
    std::cout <<"Point: "<<this->point<<std::endl;
    std::cout <<std::endl;
}


