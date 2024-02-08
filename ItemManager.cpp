// Name: Foram Patel
// Student Number: 200465914
// Date: March 13, 2022

#include <iostream>
#include <fstream>
#include <cassert>
#include "ItemManager.h"


ItemManager:: ItemManager ()
{
  num_of_Items = 0;
  items = new Item[num_of_Items];
  assert(isInvariantTrue());
}
ItemManager::ItemManager (const string& game_name)
{
  //cout << "Called game name version of the constructor" << endl;
  items = nullptr;
  load(game_name + "_items.txt");
  sort();
  assert(isInvariantTrue());
}

ItemManager::ItemManager (const ItemManager& to_copy)
{
  assert(to_copy.isInvariantTrue());
  num_of_Items = to_copy.num_of_Items;
  items = new Item[num_of_Items];

  for(int i = 0 ; i < num_of_Items ; i++)
  {
    items[i] = Item((to_copy.items[i]));
  }
  assert(isInvariantTrue());
}

ItemManager::~ItemManager ()
{
  assert(isInvariantTrue());
  delete[] items;
  items = nullptr;
}

ItemManager& ItemManager::operator= (const ItemManager& to_copy)
{
  if(&to_copy != this)
  {
    delete[] items;
    items = nullptr;
    
    num_of_Items = to_copy.num_of_Items;
    cout << "Num_of_Items = " << num_of_Items;
    items = new Item[num_of_Items];
  
    for(int i = 0 ; i < num_of_Items ; i++)
    {
      items[i] = Item((to_copy.items[i]));
    }
  }
  return *this;
}

unsigned int ItemManager::getCount () const
{
  assert(isInvariantTrue());
  return num_of_Items;
}

int ItemManager::getScore () const
{
  assert(isInvariantTrue());
  int player_score;
  player_score = 0;
  for(int i = 0 ; i < num_of_Items ; i++)
  {
    if(items[i].isInInventory()){
      player_score += items[i].getPlayerPoints();
    }
  }
  return player_score;
}

void ItemManager::printAtLocation (const Location& location) const
{
  assert(isInvariantTrue());
  for(int i = 0 ; i < num_of_Items ; i++)
  {
    if(items[i].isAtLocation(location))
    {
      items[i].printDescription();
    }
  }
}

void ItemManager::printInventory () const
{
  assert(isInvariantTrue());
  for(int i = 0 ; i < num_of_Items ; i++)
  {
    if(items[i].isInInventory())
    {
      items[i].printDescription();
    }
  }
}

bool ItemManager::isInInventory (char id) const
{
  assert(isInvariantTrue());
  if(find(id) >= 0 && find(id) < num_of_Items)
  {
    return true;
  }
  return false;
}

void ItemManager::reset ()
{
  assert(isInvariantTrue());
  for(int i = 0 ; i < num_of_Items ; i++)
  {
    items[i].reset();
  }
}

bool ItemManager::take  (char id, const Location& player_location)
{
  assert(isInvariantTrue());
    for(int i = 0 ; i < num_of_Items ; i++)
    {
      //checking that the id matches and is not in inventory of the player
      if(id == items[i].getId() && !items[i].isInInventory())
      {
        //making sure that the item in at that location of the player
        if(items[i].isAtLocation(player_location))
        {
          //moves the item to inventory
          items[i].moveToInventory();
          return true;
        }
      }
    }
    cout << "Invalid item" << endl;
    assert(isInvariantTrue());
    return false;
}

bool ItemManager::leave (char id, const Location& player_location)
{
  assert(isInvariantTrue());
    for(int i = 0 ; i < num_of_Items ; i++)
    {
      if(id == items[i].getId() && items[i].isInInventory())
      {
        //dropping the item at the current location of the player
        items[i].moveToLocation(player_location);
        return true;
      }
    }
    cout << "Invalid item" << endl;
    assert(isInvariantTrue());
    return false;
}

unsigned int ItemManager::find (char id) const
{
  int low, high, middle;
  low = 0;
  high = num_of_Items;
  
  while(low <= high)
    {
      middle = (low+middle)/2;
      if(items[middle].getId() == id)
        return middle;
      else if(items[middle].getId() < id)
        high = middle - 1;
      else
        low = low + 1;
    }
  
  return NO_SUCH_ITEM;
}

void ItemManager::load (const string& filename)
{
  string input_line = "";
  ifstream in_Data;
  char id;
  unsigned int start_location;
  int points, i;
  i = 0;
  string world_description, inventory_description;
  
  in_Data.open(filename);

  if(in_Data.fail())
  {
    cout << filename << " File not open" << endl;
  }

  in_Data >> num_of_Items;
  items = new Item[num_of_Items];
  
  for(int i = 0 ; i < num_of_Items ; i++)
    {
      getline(in_Data, input_line);
      in_Data >> id >> start_location >> points;
      getline(in_Data, input_line);
      getline(in_Data, world_description);
      getline(in_Data, inventory_description);

      Location loc = {start_location};
      items[i] = Item(id, loc, points, world_description, inventory_description);
    }
  in_Data.close();
  assert(items != nullptr);
}

//selection sort
void ItemManager::sort ()
{
  //cout << "inSort" << endl;
  int pos;
  for(int i = 0 ; i+1 < num_of_Items ; i++)
    {
      Item temp = items[i];
      pos = i;
      for(int j = i + 1 ; j < num_of_Items; j++)
        {
          if(items[j] < items[pos])
          pos = j;
        }
      if(pos > i)
      {
        Item temp = items[i];
        items[i] = items[pos];
        items[pos] = temp;
      }
    }
}

bool ItemManager::isInvariantTrue () const
{
  //cout << "num_of_items = " << num_of_Items << endl;
  for(int i = 0 ; i < num_of_Items ; i++)
  {
    if(!items[i].isInitialized())
    {
      return false;
    }
  }
  //cout << "Invariant 1" << endl;
  if(items == nullptr)
    {
      return false;
    }

  //cout << "Invariant 2" << endl;
  //cout << "num_of_items = " << num_of_Items << endl;
  for(int i = 0 ; i+1 < num_of_Items ; i++)
    {
      //cout << "Invariant 3, i=" << i<< endl;
      if(items[i+1] < items[i])
      {
        return false;
      }
    }
  return true;
}