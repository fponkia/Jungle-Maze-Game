// Name: Foram Patel
// Student Number: 200465914
// Date: March 13, 2022

# pragma once

#include <iostream>
#include "Location.h"

using namespace std;

class Node
{
  public:
    Node ();
    Node (unsigned int description1, unsigned int north1, unsigned int south1, unsigned int east1, unsigned int west1, bool is_death1);
    void debugPrint () const;
    unsigned int getDescription () const;
    Location getNorth () const;
    Location getSouth () const;
    Location getEast  () const;
    Location getWest  () const;
    bool isDeath () const;

  private:
    unsigned int description, north, south, east, west;
    bool is_death;
};