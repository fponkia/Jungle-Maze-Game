// Name: Foram Patel
// Student Number: 200465914
// Date: April 8, 2022
#include <cassert>


template <typename T>
T max (const T& a, const T& b, const T& c)
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

template <typename T>
T median (const T& a, const T& b, const T& c)
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

template <typename T>
T sum (const T& a, const T& b, const T& c)
{
  return a+b+c;
}

template <typename T>
T max (const T array[], unsigned int count)
{
  T largest;
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

template <typename T>
T sum (const T array[], unsigned int count)
{
  T sum = array[0];
  assert(array!=nullptr && count >= 1);
  for(int i = 1 ; i < count ; i++)
    {
      sum = sum + array[i];
    }
  return sum;
}