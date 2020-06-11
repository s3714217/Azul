//
//  AI.hpp
//  Azul
//
//  Created by Thien Nguyen on 26/5/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//

#ifndef AI_hpp
#define AI_hpp

#include <vector>
#include "ColorCode.h"
#include "Player.h"
#include "Factories.h"
#include "ColorCode.h"
#include "Mosaic.h"


class Solution{
    
    public:

        Solution(int row, int fac, char Colour, int count);
        ~Solution();
    int row;
    int central;
    int fac;
    int count;
    char color;
    
    
};
class AI{
    
    public:
    
        AI(int seed);
        ~AI();
    
    std::string generating_move(Mosaic* mos, Factories* fac);
    std::vector<Solution*> get_ini_solution(Mosaic *mos, Factories *fac);
    
private:
    
    int seed;
};

#endif /* AI_hpp */
