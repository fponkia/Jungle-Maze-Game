/*
 Name: Foram Patel
 Student Number: 200465914
 Date: March 13, 2022

 Program Description: takes the input from the user to where to go in a game and then prints the description accordingly. The game starts as starting position.

*/

#include <iostream>
#include <string>

#include "World.h"
#include "Item.h"
#include "Location.h"
#include "Game.h"

using namespace std;

int main() {
  Game game("jungle");
  string last_line, input_line, name;
  input_line = "";  //initializing it to empty.
  bool quit;
  quit = false;

  game.printStartMessage();
  cout << "Please Enter the name of the Player: ";
  getline(cin, name);
  cout << endl;
  cout << "Hello, " << name << endl;
  game.printDescription();

  //game gets started
  while(!game.isOver() && quit == false){
    
    //taking the input from the user to move the player in a desired direction.
    cout << "Next? ";
    getline(cin, input_line);

    //making sure that input has some characters in it.
    if(input_line.length() == 0){
      cout << "Invalid command!" << endl;
    }

    else if(input_line[0] == '#'){
      cout << "Invalid command!" << endl;
    }

    // this is used to quit the game.
    else if(input_line[0] == 'q'){
      //asking the suer if he really want to quit the game.
      cout << "Are you sure you want to quit? ";
      getline(cin, input_line); //getting the input for the confirmation.
      if(input_line[0] == 'y'){
        quit = true; //if yes than change the variable to true (quiting the game).
      }
    }

    //wants to move north
    else if(input_line[0] == 'n'){
      game.moveNorth();
    }
    
    //wants to move south
    else if(input_line[0] == 's'){
      game.moveSouth();
    }

    //wants to move east
    else if(input_line[0] == 'e'){
      game.moveEast();
    }

    //wants to move west
    else if(input_line[0] == 'w'){
      game.moveWest();
    }

    else if(input_line[0] == 't'){
      cout << "Take what? ";
      getline(cin, input_line);

      game.takeItem(input_line[0]);
    }

    else if(input_line[0] == 'l'){
      cout << "Leave what? ";
      getline(cin, input_line);

      game.leaveItem(input_line[0]);
    }

    //printing the description of the item that is in inventory
    else if(input_line[0] == 'i'){
      game.printInventory();
    }

    else if(input_line[0] == 'r')
    {
      //asking the suer if he really want to quit the game.
      cout << "Are you sure you want to reset? ";
      getline(cin, input_line); //getting the input for the confirmation.
      if(input_line[0] == 'y'){
        //printing the final points for the player
        cout << "In this game you scored ";
        game.printScore();
        cout << " points." << endl << endl;

        game.updateScoreTable(name);
        
        game.reset();
        game.printDescription();
      }
    }

    else{
      cout << "Invalid command!" << endl;
    }

  }

  cout <<  endl;
  game.printEndMessage();  //prints end message.

  //printing the final points for the player
  cout << "In this game you scored ";
  game.printScore();
  cout << " points." << endl << endl;

  game.updateScoreTable(name);
  
  cout << "Press [ENTER] to continue...";
  getline(cin, last_line);

  return 0;
} 