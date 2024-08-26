//
//  TestUnrelatedFloat6.cpp
//
//  A test program for the unrelated non-templated functions.
//
//  This program is to be used with Assignment 6: Part E for
//    CS115, 202210.
//
//

#include "UnrelatedFloat.h"
#include "UnrelatedFloat.h"  // repeated to test for #include errors

#include <cassert>
#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <typeinfo>  // for typeid

#include "TestHelper.h"

using namespace std;


const unsigned int TRIPLE_COUNT = 3;
const unsigned int ORDERING_COUNT = 6;
const unsigned int ORDERINGS[ORDERING_COUNT][TRIPLE_COUNT] =
{
	{	0,	1,	2,	},
	{	0,	2,	1,	},
	{	1,	0,	2,	},
	{	1,	2,	0,	},
	{	2,	0,	1,	},
	{	2,	1,	0,	},
};

typedef float pTripleFloatFunction (const float&, const float&, const float&);
typedef float pArrayFloatFunction (const float[], unsigned int);
unsigned int testTripleFloat (pTripleFloatFunction pf_function, const string& function_name,
                              const float values[], float correct_result, int spacing);
bool testArrayFloat (pArrayFloatFunction pf_function, const string& function_name,
                    const float values[], float correct_result, int spacing);

int calculateMark (double correct_float_max_t_fraction,
                   double correct_float_median_t_fraction,
                   double correct_float_sum_t_fraction,
                   bool correct_float_max_a,
                   bool correct_float_sum_a,
                   bool is_finished);

const int COMPILE_AND_START_MARKS     = 1;
const int DID_NOT_CRASH_RUNNING_MARKS = 1;
const int COMPILE_AND_NOT_CRASH_MARKS = COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS         = 18;
const int TOTAL_MARKS                 = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;
const int HIGHEST_POSSIBLE_MARK       = 7;

const float FLOAT_TOLERANCE = 0.0001f;  // for rounding errors

const float FLOAT_TRIPLE_VALUES[TRIPLE_COUNT] = { 3.1415926536f, 2.718281828f, 1.618033988f, };
const float FLOAT_TRIPLE_MAX    = 3.1415926536f;
const float FLOAT_TRIPLE_MEDIAN = 2.7182818284f;
const float FLOAT_TRIPLE_SUM    = 7.4779084610f;

const unsigned int FLOAT_ARRAY_SIZE = 20;
const float FLOAT_ARRAY_VALUES[FLOAT_ARRAY_SIZE] =
{	0.0f,       	1.0f,       	1.41421356f,	1.73205081f,
	2.0f,       	2.23606798f,	2.44948974f,	2.645751311f,
	2.82842712f,	3.0f,       	3.16227766f,	3.316624790f,
	3.46410162f,	3.60555128f,	3.74165739f,	3.872983346f,
	4.0f,       	4.12310563f,	4.24264069f,	4.358898944f,
};  // square roots
const float FLOAT_ARRAY_MAX =  4.358898944f;
const float FLOAT_ARRAY_SUM = 57.1938400f;



int main ()
{
	testHelperStartup("TestUnrelatedFloat6", COMPILE_AND_START_MARKS, TOTAL_MARKS);


	//
	//  Test "Float" functions
	//

	cout << endl;
	cout << "Testing *Float functions:" << endl;
	cout << "-------------------------" << endl;
	cout << endl;
	unsigned int correct_float_max_t    = testTripleFloat(&maxFloat,    "maxFloat",    FLOAT_TRIPLE_VALUES, FLOAT_TRIPLE_MAX,    4);
	unsigned int correct_float_median_t = testTripleFloat(&medianFloat, "medianFloat", FLOAT_TRIPLE_VALUES, FLOAT_TRIPLE_MEDIAN, 4);
	unsigned int correct_float_sum_t    = testTripleFloat(&sumFloat,    "sumFloat",    FLOAT_TRIPLE_VALUES, FLOAT_TRIPLE_SUM,    4);
	bool correct_float_max_a = testArrayFloat(&maxFloat, "maxFloat", FLOAT_ARRAY_VALUES, FLOAT_ARRAY_MAX, 4);
	cout << endl;
	bool correct_float_sum_a = testArrayFloat(&sumFloat, "sumFloat", FLOAT_ARRAY_VALUES, FLOAT_ARRAY_SUM, 4);
	cout << endl;

	cout << endl;
	cout << endl;


	//
	//  Print results
	//

	double correct_float_max_t_fraction    = (double)(correct_float_max_t   ) / ORDERING_COUNT;
	double correct_float_median_t_fraction = (double)(correct_float_median_t) / ORDERING_COUNT;
	double correct_float_sum_t_fraction    = (double)(correct_float_sum_t   ) / ORDERING_COUNT;

	testHelperPrintSummaryHeaderPartial(26, 2, COMPILE_AND_START_MARKS);
	testHelperPrintSummaryLine("maxFloat   (a, b, c)",   correct_float_max_t,    ORDERING_COUNT);
	testHelperPrintSummaryLine("medianFloat(a, b, c)",   correct_float_median_t, ORDERING_COUNT);
	testHelperPrintSummaryLine("sumFloat   (a, b, c)",   correct_float_sum_t,    ORDERING_COUNT);
	testHelperPrintSummaryLine("maxFloat(array, count)", correct_float_max_a);
	testHelperPrintSummaryLine("sumFloat(array, count)", correct_float_sum_a);

	unsigned int mark1 = calculateMark(correct_float_max_t_fraction, correct_float_median_t_fraction, correct_float_sum_t_fraction,
	                                   correct_float_max_a, correct_float_sum_a,
	                                   true);  // finished
	assert(mark1 <= TOTAL_MARKS);
	testHelperPrintMarkPartial(mark1, HIGHEST_POSSIBLE_MARK, TOTAL_MARKS);

	testHelperWaitForEnter();
	return 0;
}



unsigned int testTripleFloat (pTripleFloatFunction pf_function, const string& function_name,
                              const float values[], float correct_result, int spacing)
{
	assert(pf_function   != NULL);
	assert(function_name != "");
	assert(values        != NULL);
	assert(spacing       >  0);

	cout << "Testing " << function_name << " with values "
	     << values[0] << ", "
	     << values[1] << ", and "
	     << values[2] << ":" << endl;

	unsigned int correct_count = 0;
	for(unsigned int i = 0; i < ORDERING_COUNT; i++)
	{
		unsigned int index0 = ORDERINGS[i][0];
		unsigned int index1 = ORDERINGS[i][1];
		unsigned int index2 = ORDERINGS[i][2];

		cout << "\t" << function_name << "("
		     << values[index0] << ", "
		     << values[index1] << ", "
		     << values[index2] << ") = ";
		float result = pf_function(values[index0], values[index1], values[index2]);
		cout << setw(spacing) << left << result;

		// allow for floating point rounding errors
		if(fabs((float)(result - correct_result)) <= FLOAT_TOLERANCE)
		{
			cout << " Correct" << endl;
			correct_count++;
		}
		else
			cout << " Incorrect" << endl;
	}

	if(correct_count == ORDERING_COUNT)
		cout << "* All correct" << endl;
	else
		cout << "* Incorrect: " << (ORDERING_COUNT - correct_count) << " returned wrong value" << endl;
	cout << endl;

	return correct_count;
}

bool testArrayFloat (pArrayFloatFunction pf_function, const string& function_name,
                     const float values[], float correct_result, int spacing)
{
	assert(pf_function   != NULL);
	assert(function_name != "");
	assert(values        != NULL);
	assert(spacing       >  0);

	cout << "Testing " << function_name << "(ARRAY, " << FLOAT_ARRAY_SIZE << ") = ";
	float result = pf_function(values, FLOAT_ARRAY_SIZE);
	cout << setw(spacing) << left << result << endl;

	// allow for floating point rounding errors
	if(fabs((float)(result - correct_result)) <= FLOAT_TOLERANCE)
	{
		cout << "* Correct" << endl;
		return true;
	}
	else
	{
		cout << "* Incorrect: Max should be " << correct_result << endl;
		return false;
	}
}

int calculateMark (double correct_float_max_t_fraction,
                   double correct_float_median_t_fraction,
                   double correct_float_sum_t_fraction,
                   bool correct_float_max_a,
                   bool correct_float_sum_a,
                   bool is_finished)
{
	unsigned int mark = 0;
	if(is_finished)
		mark = COMPILE_AND_NOT_CRASH_MARKS;
	else
		mark = COMPILE_AND_START_MARKS;

	if(correct_float_max_t_fraction == 1.0f &&
	   correct_float_sum_t_fraction == 1.0f)
	{
		mark += 1;
	}
	int median_mark = (int)(correct_float_median_t_fraction * 3.0 - 1.0);
	if(median_mark > 0)
		mark += median_mark;
	if(correct_float_max_a)
		mark += 1;
	if(correct_float_sum_a)
		mark += 1;

	assert(mark <= TOTAL_MARKS);
	assert(mark <= HIGHEST_POSSIBLE_MARK);
	return mark;
}