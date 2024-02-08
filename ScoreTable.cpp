// Name: Foram Patel
//Student Number: 200465914
//Date: March 29, 2022
#include "ScoreTable.h"
#include <cassert>

int num_of_Elements = 0;

Element::Element()
{
  name = "";
  score = 0;
  p_next = nullptr;
  num_of_Elements++;
}

Element::~Element()
{
  num_of_Elements--;
}

int getAllocatedElementCount ()
{
  return num_of_Elements;
}
Element* copyLinkedList (const Element* p_head1)
{
  if(p_head1 == nullptr)
  {
    return nullptr;
  }

  Element* p_head2 = new Element;

  p_head2 -> name = p_head1 -> name;
  p_head2 -> score = p_head1 -> score;

  const Element* p1 = p_head1;
  Element* p2 = p_head2;

  while(p1 -> p_next != nullptr)
    {
      Element* pTemp = new Element;

      p1 = p1 -> p_next;
      p2 -> p_next = pTemp;
      p2 = pTemp;

      p2 -> name = p1 -> name;
      p2 -> score = p1 -> score;
    }
  p2 -> p_next = nullptr;

  return p_head2;
}
void destroyLinkedList (Element* p_head)
{
  Element* pCurrent = nullptr;
  Element* pNext = p_head;
  while (pNext != nullptr) 
  {
    pCurrent = pNext;
    pNext = pCurrent->p_next;
    delete pCurrent;
  }
}

ScoreTable::ScoreTable ()
{
  p_head = nullptr;
  assert(isInvariantTrue());
}

ScoreTable::ScoreTable (const ScoreTable& to_copy)
{
  assert(to_copy.isInvariantTrue());
  Element* to_copy1 = new Element;
  to_copy1 = to_copy.p_head;

  if(to_copy1 == nullptr)
  {
    this ->p_head = nullptr;
  }
  else{

    Element* p_head2 = new Element;
    p_head2 -> name = to_copy1 -> name;
    p_head2 -> score = to_copy1 -> score;
    p_head2 -> p_next = nullptr;
  
    Element* p1 = to_copy1;
    Element* p2 = p_head2;
  
    while(p1 -> p_next != nullptr)
      {
        Element* pTemp = new Element;
        p1 = p1 -> p_next;
        p2 -> p_next = pTemp;
        p2 = pTemp;
        pTemp -> name = p1 -> name;
        pTemp -> score = p1 -> score;
      }
    p2 -> p_next = nullptr;
  
    this ->p_head = p_head2;
    }
  assert(isInvariantTrue());
}

ScoreTable::~ScoreTable ()
{
  assert(isInvariantTrue());
  while(p_head != nullptr)
  {
    Element* pNext = new Element;
    pNext = p_head -> p_next;
    delete p_head;
    p_head = pNext;
  }
  p_head = nullptr;
}

ScoreTable& ScoreTable::operator= (const ScoreTable& to_copy)
{
  assert(to_copy.isInvariantTrue());
  if(&to_copy != this)
  {
    while(p_head != nullptr)
    {
      Element* pNext = new Element;
      pNext = p_head -> p_next;
      delete p_head;
      p_head = pNext;
    }
    p_head = nullptr;
  
    Element* to_copy1 = new Element;
  to_copy1 = to_copy.p_head;

  if(to_copy1 == nullptr)
  {
    this ->p_head = nullptr;
    return *this;
  }
  else{

  Element* p_head2 = new Element;
  p_head2 -> name = to_copy1 -> name;
  p_head2 -> score = to_copy1 -> score;
  p_head2 -> p_next = nullptr;

  Element* p1 = to_copy1;
  Element* p2 = p_head2;

  while(p1 -> p_next != nullptr)
    {
      Element* pTemp = new Element;
      p1 = p1 -> p_next;
      p2 -> p_next = pTemp;
      p2 = pTemp;
      pTemp -> name = p1 -> name;
      pTemp -> score = p1 -> score;
    }
    cout << "I am Here" << endl;
  p2 -> p_next = nullptr;

  this ->p_head = p_head2;
    }
  
}
  return *this;
  assert(isInvariantTrue());
  }

void ScoreTable::print () const
{
  assert(isInvariantTrue());
  Element* p = p_head;
  cout << "Scores:" << endl;
  while(p != nullptr)
  {
    cout << p -> score << "\t" << p -> name << endl;
    p = p -> p_next;
  }
}

void ScoreTable::insert (const string& player_name, int score)
{
  assert(isInvariantTrue());
  //cout << "I am Here: "<<endl;
  Element* p = new Element;
  Element* pTemp = new Element;
  Element* previous = new Element;
  p -> name = player_name;
  p -> score = score;
  p -> p_next = nullptr;

  pTemp = p_head;

  if(p_head == nullptr)
  {
    p_head = p;
  }
    
  else if(p_head -> p_next == nullptr)
  {
    if (pTemp -> score < p -> score)
    {
      p_head = p;
      p_head -> p_next = pTemp;
    }
    else
      p_head -> p_next = p;
  }
    
  else{
  
  while(pTemp -> score > p -> score && pTemp -> p_next != nullptr)
  {
    previous = pTemp;
    pTemp = pTemp -> p_next;
  }

  if(p_head == pTemp)
  {
    p_head = p;
    p_head -> p_next = pTemp;
  }
  else
  {
    if(pTemp -> p_next == nullptr)
    {
      previous = pTemp;
      pTemp = pTemp -> p_next;
    }
    previous -> p_next = p;
    p -> p_next = pTemp;
  }
    }
  //cout << "I am Here" << endl;
  assert(isInvariantTrue());
}

bool ScoreTable::isInvariantTrue () const
{
  Element* p = new Element;
  Element* p1 = new Element;
  p = p_head;
  if(p == nullptr)
  {
    return true;
  }
  p1 = p_head -> p_next;
  while(p1 != nullptr)
    {
      if(p -> score < p1 -> score)
      {
        //cout << "I am Here" << endl;
        return false;
      }
      p = p -> p_next;
      p1 = p1 -> p_next;
    }
  return true;
}