// Name: Foram Patel
// Student Number: 200465914
// Date: March 13, 2022

#pragma once
#include <fstream>

using namespace std;

class Location
{
  public:
    unsigned int node_index;
    Location ();
    Location (unsigned int index);
    bool operator== (const Location& other) const;
    bool isInaccessible () const;
};

ostream& operator<< (ostream& out, const Location& location);