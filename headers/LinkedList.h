#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Node.h"
#include "ColorCode.h"
#include <algorithm>
#include <vector>
#include <random>
#include <iostream>

class LinkedList {
public:
   LinkedList();
   ~LinkedList();
      
   int size();
   void clear();
   Tile* getFirst();
   bool remove(Tile* tile);

   void addFront(Tile* tile);
   void addBack(Tile* tile);
    void shuffle(int seed);
    void printAll();
private:
       int len;
     Node* head;
};

#endif // LINKED_LIST_H
