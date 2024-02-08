// Name: Foram Patel
// Student Number: 200465914
// Date: March 13, 2022

#include "Node.h"

Node::Node ()
{
  description = 0;
  north = 0;
  south = 0;
  east = 0;
  west = 0;
  is_death = false;
}

Node::Node (unsigned int description1, unsigned int north1, unsigned int south1, unsigned int east1, unsigned int west1, bool is_death1)
{
  description = description1;
  north = north1;
  south = south1;
  east = east1;
  west = west1;
  is_death = is_death1;
}

void Node::debugPrint () const
{
  if(is_death)
  {
    cout << "D " << description << " " << north << " " << south << " " << east << " " << west << endl;
  }
  else
  {
    cout << "N " << description << " " << north << " " << south << " " << east << " " << west << endl;
  }
}

unsigned int Node::getDescription () const
{
  return description;
}

Location Node::getNorth () const
{
  Location loc(north);
  return loc;
}

Location Node::getSouth () const
{
  Location loc(south);
  return loc;
}

Location Node::getEast  () const
{
  Location loc(east);
  return loc;
}

Location Node::getWest  () const
{
  Location loc(west);
  return loc;
}

bool Node::isDeath () const
{
  if(is_death)
    return true;
  return false;
}