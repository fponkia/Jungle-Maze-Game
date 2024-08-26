// Name: Foram Patel
// Student Number: 200465914
// Date: April 8, 2022
#include "UnrelatedFloat.h"
#include <cassert>

float maxFloat (const float& a, const float& b, const float& c)
{
  if(a > b && a > c)
  {
    return a;
  }
  else if(b > a && b > c)
  {
    return b;
  }
  else
  {
    return c;
  }
}

float medianFloat (const float& a, const float& b, const float& c)
{
  if(a > b && a < c)
  {
    return a;
  }
  else if (a < b && a > c)
  {
    return a;
  }
  else if(b > a && b < c)
  {
    return b;
  }
  else if(b < a && b > c)
  {
    return b;
  }
  else if(c > a && c < b)
  {
    return c;
  }
  else
  {
    return c;
  }
}

float sumFloat (const float& a, const float& b, const float& c)
{
  return a+b+c;
}

float maxFloat (const float array[], unsigned int count)
{
  float largest;
  assert(array!=nullptr && count >= 1);
  largest = array[0];
  for(int i = 1 ; i < count ; i++)
    {
      if(array[i] > largest)
      {
        largest = array[i];
      }
    }
  return largest;
}

float sumFloat (const float array[], unsigned int count)
{
  float sum = 0;
  assert(array!=nullptr && count >= 1);
  for(int i = 0 ; i < count ; i++)
    {
      sum = sum + array[i];
    }
  return sum;
}