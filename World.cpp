/*
 Name: Foram Patel
 Student Number: 200465914
 Date: March 13, 2022
*/
#include "World.h"
#include <cassert>

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


World::World (const string& game_name)
{
  loadNodes(game_name + "_nodes.txt");
  loadDescriptions(game_name + "_text.txt");
  assert(isInvariantTrue());
}

//loading the nodes from the textfile.
void World::loadNodes (const string& filename){
  char input, input1;
  unsigned int description1, north1, south1, east1, west1, obstacle1, obstacle2;
  ifstream my_Data;
  my_Data.open(filename); //opening the file

  // printing the message if file does not open
  if(my_Data.fail()){
    cout << "Not able to open " << filename << endl;
    exit(1);
  }

  my_Data >> node_count;
  my_Data >> start_node >> victory_node >> start_description >> end_description;
  //taking the input from the file.
  for(int i = 0 ; i < node_count ; i++)
  {
    my_Data >> input >> description1 >> north1 >> south1 >> east1 >> west1;
    if(input == 'N')
    {
      nodes[i] = Node(description1, north1, south1, east1, west1, false);
    }
    else if(input == 'D')
    {
      nodes[i] = Node(description1, north1, south1, east1, west1, true);
    }
    else if(input == 'O')
    {
      my_Data >> input1 >> obstacle1 >> obstacle2;
      nodes[i] = Node(description1, north1, south1, east1, west1, false);
    }
  }

  my_Data.close();  //closing the file
}

//loading the descriptions from the textfile.
void World::loadDescriptions (const string& filename){
  string line, current_index;
  line = "";
  current_index = "";
  int i = 0;

  ifstream my_Data;
  my_Data.open(filename);

  if(my_Data.fail()){
    cout << "Not able to open " << filename << endl;
    exit(2);
  }

  //avoiding the first two lines of the input
  getline(my_Data, line);
  description_count = stoi(line);
  getline(my_Data, line);
  
  for(int i = 0 ; i < description_count ; i++)
  {
    getline(my_Data, line);
    //current_index = current_index + line + "\n";
    while(line != "")
    {
      current_index = current_index + line + "\n";
      getline(my_Data, line);
    }
    description[i] = current_index;
    current_index = "";
  }

  my_Data.close();
}

//printing the world.
void World::debugPrint () const{
  cout << node_count << endl << start_node << " " << victory_node << endl;

  for(int i = 0 ; i < node_count ; i++)
  {
    nodes[i].debugPrint();
  }
  cout << endl;

  cout << description_count << endl;

  for(int i = 0 ; i < description_count ; i++)
  {
    cout << description[i] << endl;
  }
}
//determining that if the current position of the player is valid or not.
bool World::isValid (const Location& location) const{
  assert(isInvariantTrue());
  if(location.node_index < node_count){
    return true;
  }
  return false;
}

//determining if the player can move north or not.
bool World::canGoNorth (const Location& location) const{
  assert(isInvariantTrue());
  assert(isValid(location));
  if(nodes[location.node_index].getNorth().isInaccessible()){
    return false;
  }
  return true;
}

//determining if the player can move south or not.
bool World::canGoSouth (const Location& location) const{
  assert(isInvariantTrue());
  assert(isValid(location));
  if(nodes[location.node_index].getSouth().isInaccessible()){
    return false;
  }
  return true;
}

//determining if the player can move east or not.
bool World::canGoEast (const Location& location) const{
  assert(isInvariantTrue());
  assert(isValid(location));
  if(nodes[location.node_index].getEast().isInaccessible()){
    return false;
  }
  return true;
}

//determining if the player can move west or not.
bool World::canGoWest (const Location& location) const{
  assert(isInvariantTrue());
  assert(isValid(location));
  if(nodes[location.node_index].getWest().isInaccessible()){
    return false;
  }
  return true;
}

//
// getNorth
//
// Purpose: returns the new location of the player. In this case the location just one row above the .
// Parameter(s): 
//  <1> location: has the location of the player current's location
// Precondition(s): isInvariantTrue() and (isValid(location) &&
//                  canGoNorth(location));
// Returns: loc: new location
// Side effect: declares new location variable and intializes it with 
//              one row less and same column.
//

Location World::getNorth (const Location& location) const
{
  assert(isInvariantTrue());
  assert(isValid(location) && canGoNorth(location));
  Location loc = nodes[location.node_index].getNorth();
  return loc;
}

Location World::getSouth (const Location& location) const
{
  assert(isInvariantTrue());
  assert(isValid(location) && canGoSouth(location));
  Location loc = nodes[location.node_index].getSouth();
  return loc;
}

Location World::getEast  (const Location& location) const
{
  assert(isInvariantTrue());
  assert(isValid(location) && canGoEast(location));
  Location loc = nodes[location.node_index].getEast();
  return loc;
}

Location World::getWest  (const Location& location) const
{
  assert(isInvariantTrue());
  assert(isValid(location) && canGoWest(location));
  Location loc = nodes[location.node_index].getWest();
  return loc;
}

//determining if the player is at the death position or not.
bool World::isDeath (const Location& location) const{
  assert(isInvariantTrue());
  assert(isValid(location));
  if(nodes[location.node_index].isDeath())
  {
    return true;
  }
  return false;
}

//determining if the player is at the victory position or not.
bool World::isVictory (const Location& location) const{
  assert(isInvariantTrue());
  assert(isValid(location));
  if(location.node_index == victory_node)
  {
    return true;
  }
  return false;
}

//finding the value in the world and changing the position of the player to that location.
Location World::getStart () const
{
  assert(isInvariantTrue());
  Location loc(start_node);
  return loc;
}

//prints the description according to the position of the player
void World::printDescription (const Location& location) const{
  assert(isInvariantTrue());
  assert(isValid(location));
  unsigned int index;
  index = nodes[location.node_index].getDescription();

  cout << description[index] << endl;
}

//prints the start message
void World::printStartMessage () const{
  assert(isInvariantTrue());
  cout << description[start_description] << endl;
}

//prints the end message
void World::printEndMessage () const{
  assert(isInvariantTrue());
  cout << description[end_description] << endl;
}

bool World::isInvariantTrue () const
{
  if(description_count > MAX_DESCRIPTION_COUNT)
  {
    return false;
  }
  
  for(int i = 0 ; i < description_count ; i++)
  {
    if(description[i] == "")
    {
      return false;
    }
  }

  if(node_count > MAX_NODE_COUNT)
  {
    return false;
  }

  if(start_node >= node_count || victory_node >= node_count)
  {
    return false;
  }

  if(start_description >= description_count || end_description >= description_count)
  {
    return false;
  }

  for(int i = 0 ; i < node_count ; i++)
    {
      if(nodes[i].getDescription() >= description_count)
      {
        return false;
      }
    }

  return true;
}