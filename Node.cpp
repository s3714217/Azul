//
//  Node.cpp
//  Azul
//
//  Created by Thien Nguyen on 22/4/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//

#include "headers/Node.h"

Node::Node(Tile* tile, Node* next)
{
    this->tile = tile;
    this->next = next;
}

Node::Node(Node& other)
{
    this->tile = other.tile;
    this->next = other.next;
}
