// Name: Foram Patel
// Student Number: 200465914
// Date: March 13, 2022

#include "Game.h"
#include <cassert>

Game::Game (const string& game_name): world(game_name), item(game_name), score()
{
  player_location = world.getStart();
  assert(isInvariantTrue());
}

bool Game::isOver () const
{
  assert(isInvariantTrue());
  if(world.isDeath(player_location) || world.isVictory(player_location))
  {
    return true;
  }
  return false;
}

void Game::printStartMessage () const
{
  assert(isInvariantTrue());
  world.printStartMessage();
}

void Game::printEndMessage () const
{
  assert(isInvariantTrue());
  world.printEndMessage();
}

void Game::printDescription () const
{
  assert(isInvariantTrue());
  world.printDescription(player_location);
  item.printAtLocation(player_location);
}

void Game::printInventory () const
{
  assert(isInvariantTrue());
  item.printInventory();
}

void Game::printScore () const
{
  assert(isInvariantTrue());
  cout << item.getScore();
}

void Game::reset ()
{
  assert(isInvariantTrue());
  player_location = world.getStart();
  item.reset();
  assert(isInvariantTrue());
}

void Game::moveNorth ()
{
  assert(isInvariantTrue());
  if(world.canGoNorth(player_location))
  {
    player_location = world.getNorth(player_location);
    printDescription();
  }
  else
  {
    cout << "There is no way to go in that direction" << endl;
  }
  assert(isInvariantTrue());
}

void Game::moveSouth ()
{
  assert(isInvariantTrue());
  if(world.canGoSouth(player_location))
  {
    player_location = world.getSouth(player_location);
    printDescription();
  }
  else
  {
    cout << "There is no way to go in that direction" << endl;
  }
  assert(isInvariantTrue());
}
void Game::moveEast ()
{
  assert(isInvariantTrue());
  if(world.canGoEast(player_location))
  {
    player_location = world.getEast(player_location);
    printDescription();
  }
  else
  {
    cout << "There is no way to go in that direction" << endl;
  }
  assert(isInvariantTrue());
}

void Game::moveWest ()
{
  assert(isInvariantTrue());
  if(world.canGoWest(player_location))
  {
    player_location = world.getWest(player_location);
    printDescription();
  }
  else
  {
    cout << "There is no way to go in that direction" << endl;
  }
  assert(isInvariantTrue());
}

void Game::takeItem (char id)
{
  assert(isInvariantTrue());
  item.take(id, player_location);
  assert(isInvariantTrue());
}

void Game::leaveItem (char id)
{
  assert(isInvariantTrue());
  item.leave(id, player_location);
  assert(isInvariantTrue());
}

void Game::updateScoreTable(const string& name)
{
  score.insert(name, item.getScore());
  cout << endl;
  score.print();
}

bool Game::isInvariantTrue () const
{
  if(world.isValid(player_location))
  {
    return true;
  }
  return false;
}