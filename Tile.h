
#ifndef TILE_H
#define TILE_H

#include "ColorCode.h"

class Tile {
    
public:
    Tile();
    Tile(Colour c);
    Colour getColour();
    void setColour(Colour c);
    bool isSameColour(Tile* tile);
    
private:
    Colour colour;
};

#endif //TILE_H
