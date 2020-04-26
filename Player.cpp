//
//  Player.cpp
//  Azul
//
//  Created by Thien Nguyen on 22/4/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//

#include "Player.h"


Player::Player(std::string name)
{
    this->name = name;
    this->point = 0;
}

Player::~Player()
{
    this->name = "";
    this->point = 0;
    
}

void Player::setPoint(int pts)
{
   if(pts >= 0)this->point = pts;
    
   else this->point = 0;
}

int Player::getPoint()
{
    return this->point;
}

std::string Player::getName()
{
    return this->name;
}

void Player::printInfo()
{
    
    std::cout <<"Name: "<<this->name<<std::endl;
    std::cout <<"Point: "<<this->point<<std::endl;
    std::cout <<std::endl;
}


