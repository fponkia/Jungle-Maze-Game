// Name: Foram Patel
//Student Number: 200465914
//Date: March 29, 2022
#pragma once
#include <iostream>
#include <string>

using namespace std;

class Element
{
  public:
    Element();
    ~Element();
    string name;
    int score;
    Element* p_next;
};

class ScoreTable
{
  public:
    //
    // ScoreTable
    //
    // Purpose: To initialize the p_head variable to nullptr
    // Parameter(s): N/A
    // Precondition(s): N/A
    // Returns: N/A
    // Side effect: initializes the p_head variable of Element to nullptr
    //
    ScoreTable ();

    //
    // ScoreTable
    //
    // Purpose: To initialize the p_head variable to nullptr
    // Parameter(s): const ScoreTable& to_copy
    // Precondition(s): N/A
    // Returns: N/A
    // Side effect: initializes the p_head variable of Element.
    //
    ScoreTable (const ScoreTable& to_copy);

    //
    // ~ScoreTable
    //
    // Purpose: To deallocate (delete) the p_head and the linked list
    // Parameter(s): N/A
    // Precondition(s): score of the linked list should be in descending order.
    // Returns: N/A
    // Side effect: deaalocate the p_head variable of Element to nullptr and also delete the linked list
    //
    ~ScoreTable ();

    //
    // operator=
    //
    // Purpose: To initialize the p_head variable to nullptr
    // Parameter(s): const ScoreTable& to_copy
    // Precondition(s): score of the linked list passed as a paramter should be in descending order.
    // Returns: pointer to the ScoreTable created (copied)
    // Side effect: delete the linked list and reassign the p_head and initializes the p_head variable of Element.
    //
    ScoreTable& operator= (const ScoreTable& to_copy);

    //
    // print
    //
    // Purpose: To print the contents of the linked list
    // Parameter(s): N/A
    // Precondition(s): score of the linked list should be in descending order.
    // Returns: N/A
    // Side effect: prints the contents of the linked list.
    //
    void print () const;

    //
    // insert
    //
    // Purpose: To insert an element in current the linked list
    // Parameter(s): const string& player_name and int score
    // Precondition(s): score of the linked list should be in descending order.
    // Returns: N/A
    // Side effect: adds an element in the current linked list.
    //
    void insert (const string& player_name, int score);
  private:
    Element* p_head;
    bool isInvariantTrue () const;
};

int getAllocatedElementCount ();
Element* copyLinkedList (const Element* p_head1);
void destroyLinkedList (Element* p_head);