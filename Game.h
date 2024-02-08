// Name: Foram Patel
// Student Number: 200465914
// Date: March 13, 2022
#pragma once

#include <iostream>
#include "World.h"
#include "ItemManager.h"
#include "Location.h"
#include "ScoreTable.h"

using namespace std;

class Game
{
  public:
    Game (const string& game_name);
    bool isOver () const;
    void printStartMessage () const;
    void printEndMessage () const;
    void printDescription () const;
    void printInventory () const;
    void printScore () const;
    void reset ();
    void moveNorth ();
    void moveSouth ();
    void moveEast ();
    void moveWest ();
    void takeItem (char id);
    void leaveItem (char id);
    void updateScoreTable(const string& name);

  private:
    World world;
    ItemManager item;
    Location player_location;
    ScoreTable score;
    bool isInvariantTrue () const;
};