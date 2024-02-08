// Name: Foram Patel
// Student Number: 200465914
// Date: March 13, 2022

#pragma once
#include <string>
using namespace std;

#include "Location.h"

const char ID_NOT_INITIALIZED = '\0';

class Item
{
  public:
    Item ();  // new in A3
    Item (char id1, const Location& location, int points1, const string& world_description1, const string& inventory_description1);
    void debugPrint () const;
    bool isInitialized () const;  // new in A3
    char getId () const;
    bool isInInventory () const;
    bool isAtLocation (const Location& location) const;
    //
    // itemGetPlayerPoints
    //
    // Purpose: To get the points of the particular item
    // Parameter(s): N/A
    // Precondition(s): isInvariantValue()
    // Returns: the number of points the item has, if it is in inventory. Otherwise, returns 0
    // Side effect: N/A
    //
    int getPlayerPoints () const; 
    void printDescription () const;
    bool operator< (const Item& other) const;  // new in A3
    void reset ();
    void moveToInventory ();
    void moveToLocation (const Location& location);
    void printLocationItemDescription (const Item items[], Location location, int item_count);

  private:
    bool isInvariantValue () const;  // new in A3
    char item_id;
    Location start_location, current_location;
    bool check_item;
    int item_worth;
    string description_ground, description_inventory;
};