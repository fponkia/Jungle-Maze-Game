// Name: Foram Patel
// Student Number: 200465914
// Date: March 13, 2022

#include "Location.h"

Location::Location ()
{
  node_index = 0;
}

Location::Location (unsigned int index)
{
  node_index = index;
}

bool Location::operator== (const Location& other) const
{
  return (node_index == other.node_index);
}

bool Location::isInaccessible () const
{
  if(node_index == 0)
  {
    return true;
  }
  return false;
}

ostream& operator<< (ostream& out, const Location& location)
{
  if(location.isInaccessible())
  {
    out << "(node = INACCESSIBLE)";
  }
  else
  {
    out << "(node = " << location.node_index << ")";
  }
  
  return out;
}