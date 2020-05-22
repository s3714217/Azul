//
//  Tile.cpp
//  Azul
//
//  Created by Thien Nguyen on 22/4/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//

#include "headers/Tile.h"

//Constructor
Tile::Tile()
{
    this->colour = ' ';
}

//Constructor for a tile with a given Colour
Tile::Tile(Colour c)
{
    this->colour = c;
}

//Sets a tile's colour
void Tile::setColour(Colour c)
{
    this->colour = c;
}

//Gets a tile's colour
Colour Tile::getColour()
{
    return this->colour;
}

//Checks the colour of 2 tiles
bool Tile::isSameColour(Tile* tile)
{
  if(tile->getColour() == this->colour)
  {
      return true;
  }
    return false;
}
