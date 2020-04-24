//
//  LinkedList.cpp
//  Azul
//
//  Created by Thien Nguyen on 22/4/20.
//  Copyright © 2020 Thien Nguyen. All rights reserved.
//

#include "LinkedList.h"

 LinkedList::LinkedList()
{
    head = nullptr;
    len = 0;
}
 
 LinkedList::~LinkedList()
{
    this->clear();
}

int LinkedList::size()
{
    return this->len;
}

Tile* LinkedList::getFirst()
{
   if(this->head != nullptr)
   {
    Node* temp = this->head;
    delete this->head;
    this->head = temp->next;
    this->len--;
    return temp->tile;
   }
    else
    {
        return nullptr;
    }
    
    
}

bool LinkedList::remove(Tile *tile)
{
    Node* temp = this->head;
    if(this->head->tile->getColour() == tile->getColour())
    {
        this->head = this->head->next;
        delete temp;
        this->len--;
        return true;
    }
    
    for(int x=0; x < this->len-1; x++)
    {
       
        if(temp->next->tile->getColour() == tile->getColour())
        {
            delete temp->next;
            temp->next = temp->next->next;
            this->len--;
            return true;
        }
        temp = temp->next;
    }
    
    return false;
}

void LinkedList::clear()
{
    if(head != nullptr)
    {
        Node* checkingNode = head->next;
        
        while(checkingNode != nullptr)
        {
            Node* next = checkingNode->next;
            checkingNode = nullptr;
            delete checkingNode;
            checkingNode = next;
        }
        head = nullptr;
    }
    this->len = 0;
}

void LinkedList::addFront(Tile* tile)
{
    Node* tempHead = new Node(tile, this->head);
    this->head = tempHead;
    this->len++;
}

void LinkedList::addBack(Tile* tile)
{
    if(this->head != nullptr)
  {
      Node* temp = this->head;
      
      while(temp->next != nullptr)
      {
          temp = temp->next;
      }
      temp->next = new Node(tile, nullptr);
      this->len++;
  }
  else
  {
         this->head =new Node(tile, nullptr);
         this->len++;
   }
}

void LinkedList::shuffle()
{
    std::vector<Tile*> shuffling ;
    Node* node = this->head;
    while (node != nullptr) {
        shuffling.push_back(node->tile);
        node = node->next;
    }
    
   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
   std::default_random_engine e(seed);
   std::shuffle (shuffling.begin(), shuffling.end(), e);
  
    
    node = this->head;
    for (int x=0; x < shuffling.size(); x++)
    {
        if(shuffling[x] != nullptr)
        {
            node->tile = new Tile(shuffling[x]->getColour());
            node = node->next;
        }
    }
}

void LinkedList::printAll()
{
    std::string text = " ";
    Node* node = this->head;
    while (node != nullptr) {
        text.push_back(node->tile->getColour());
        text.push_back(' ');
        node = node->next;
    }
    
    std::cout<< text<<std::endl;
}

