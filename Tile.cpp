//
//  Tile.cpp
//  Azul
//
//  Created by Thien Nguyen on 22/4/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//

#include "headers/Tile.h"

Tile::Tile()
{
    this->colour = ' ';
}

Tile::Tile(Colour c)
{
    this->colour = c;
}

void Tile::setColour(Colour c)
{
    this->colour = c;
}

Colour Tile::getColour()
{
    return this->colour;
}

bool Tile::isSameColour(Tile* tile)
{
  if(tile->getColour() == this->colour)
  {
      return true;
  }
    return false;
}
