// Name: Foram Patel
// Student Number: 200465914
// Date: March 13, 2022

#include <iostream>
#include <string>
#include <cassert>

#include "Item.h"

using namespace std;

Item::Item(): item_id(ID_NOT_INITIALIZED), check_item(false), item_worth(0), description_ground("[Item not initialized]"), description_inventory("[Item not initialized]"), start_location(), current_location()
{
  isInvariantValue();
}

Item::Item (char id1, const Location& location, int points1, const string& world_description1, const string& inventory_description1): item_id(id1), check_item(false), item_worth(points1), description_ground(world_description1), description_inventory(inventory_description1), start_location(location), current_location(location)
{
  isInvariantValue();
}

void Item::debugPrint () const
{
  cout << "id:\t\'" << item_id << "\'" << endl;
  cout << "start_location: " << start_location << endl;
  cout << "current_location: " << current_location << endl;
  cout << "is_in_inventory:\t" << check_item << endl;
  cout << "points:\t" << item_worth << endl;
  cout << "world_description:\t\"" << description_ground << "\"" <<endl;
  cout << "inventory_description:\t\"" << description_inventory << "\"" << endl;
}

bool Item::isInitialized () const
{
  isInvariantValue();
  if(item_id == ID_NOT_INITIALIZED)
  {
    return false;
  }
  return true;
}

char Item::getId () const
{
  isInvariantValue();
  return item_id;
}

bool Item::isInInventory () const
{
  isInvariantValue();
  if(check_item){
    return true;
  }
  return false;
}

bool Item::isAtLocation (const Location& location) const
{
  isInvariantValue();
  if(!isInInventory()){
    if(current_location == location)
    {
      return true;
    }
  }
  return false;
}

int Item::getPlayerPoints () const
{
  isInvariantValue();
  if(isInInventory()){
    return item_worth;
  }
  return 0;
}

void Item::printDescription () const
{
  isInvariantValue();
  if(isInInventory()){
    cout << description_inventory << endl;
  }
  else{
    cout << description_ground << endl;
  }
}

void Item::reset ()
{
  isInvariantValue();
  current_location = start_location;
  check_item = false;
  isInvariantValue();
}

void Item::moveToInventory ()
{
  isInvariantValue();
  check_item = true;
  isInvariantValue();
}

void Item::moveToLocation (const Location& location)
{
  isInvariantValue();
  current_location = location;
  check_item = false;
  isInvariantValue();
}

void Item::printLocationItemDescription (const Item items[], Location location, int item_count)
{
  for(int i = 0 ; i < item_count ; i++)
  {
    if(items[i].isAtLocation(location))
    {
      items[i].printDescription();
    }
  }
}

bool Item::operator< (const Item& other) const
{
  if(item_id < other.item_id)
  {
    return true;
  }
  return false;
}

bool Item::isInvariantValue () const
{
  if(description_ground == "" || description_inventory == "")
  {
    return false;
  }
  return true;
}