/*
 Name: Foram Patel
 Student Number: 200465914
 Date: March 13, 2022
*/

#include <iostream>
#include <string>
#include "Location.h"
#include "Node.h"

using namespace std;

#pragma once

//declaring constants
const unsigned int MAX_DESCRIPTION_COUNT = 1000;
const unsigned int MAX_NODE_COUNT = 1000;
const Location NO_SUCH_VALUE = {4294967295};


class World
{
  public:
    //
    // World
    //
    // Purpose: Initialize and load the descriptions and nodes.
    // Parameter(s):
    //  <1> game_name: constains the name of the game. With the help of
    //                 the game name, nodes and description functions are 
    //                 called and thus loaded resprectively.
    // Precondition(s): N/A
    // Returns: N/A
    // Side effect: calles the loadNodes and loadDescription functions that loads the nodes values and descriptions.
    //
    World (const string& game_name);
    void debugPrint () const;
    bool isValid (const Location& location) const;
    bool isDeath   (const Location& location) const;
    bool isVictory (const Location& location) const;
    bool canGoNorth (const Location& location) const;
    bool canGoSouth (const Location& location) const;
    bool canGoEast  (const Location& location) const;
    bool canGoWest  (const Location& location) const;
    Location getNorth (const Location& location) const;  // new in A3
    Location getSouth (const Location& location) const;  // new in A3
    Location getEast  (const Location& location) const;  // new in A3
    Location getWest  (const Location& location) const;  // new in A3
    Location getStart () const;
    void printStartMessage () const;
    void printEndMessage () const;
    void printDescription (const Location& location) const;

  private:
    Node nodes[MAX_NODE_COUNT];
    string description[MAX_DESCRIPTION_COUNT];  //declaring global variable
    unsigned int start_node, victory_node, start_description, end_description;
    unsigned int node_count;
    unsigned int description_count = 0;
    void loadNodes (const string& filename);
    void loadDescriptions (const string& filename);
    bool isInvariantTrue () const;  // new in A3
};