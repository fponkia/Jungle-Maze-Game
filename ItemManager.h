// Name: Foram Patel
// Student Number: 200465914
// Date: March 13, 2022

#pragma once

#include <iostream>
#include "Location.h"
#include "Item.h"

using namespace std;

const unsigned int NO_SUCH_ITEM = 999999999;

class ItemManager
{
  public:
    ItemManager();
    ItemManager (const string& game_name);
    ItemManager (const ItemManager& to_copy);
    ~ItemManager ();
    ItemManager& operator= (const ItemManager& to_copy);
    unsigned int getCount () const;
    int getScore () const;
    void printAtLocation (const Location& location) const;
    void printInventory () const;
    bool isInInventory (char id) const;
    void reset ();
    bool take  (char id, const Location& player_location);
    bool leave (char id, const Location& player_location);

  private:
    //Item items[ITEM_COUNT];
    unsigned int num_of_Items = 0;
    Item* items;
    unsigned int find (char id) const;
    void load (const string& filename);
    void sort ();
    bool isInvariantTrue () const;
};