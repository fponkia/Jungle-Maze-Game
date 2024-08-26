//
//  TestUnrelated6.cpp
//
//  A test program for the unrelated templated functions.  It
//    includes all the tests from TestUnrelatedFloat6.cpp.
//
//  This program is to be used with Assignment 6: Part F for
//    CS115, 202210.
//
//

#include "UnrelatedFloat.h"
#include "UnrelatedFloat.h"  // repeated to test for #include errors
#include "Unrelated.h"
#include "Unrelated.h"  // repeated to test for #include errors

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
const unsigned int DATA_TYPE_COUNT = 6;
const unsigned int TRIPLE_SUM = DATA_TYPE_COUNT * ORDERING_COUNT;

typedef float pTripleFloatFunction (const float&, const float&, const float&);
typedef float pArrayFloatFunction (const float[], unsigned int);
unsigned int testTripleFloat (pTripleFloatFunction pf_function, const string& function_name,
                              const float values[], float correct_result, int spacing);
bool testArrayFloat (pArrayFloatFunction pf_function, const string& function_name,
                    const float values[], float correct_result, int spacing);

template <typename T>
unsigned int testMaxTriple (const string& type_name, const string& type_quote,
                            const T values[], const T& correct_result, int spacing);
template <typename T>
unsigned int testMedianTriple (const string& type_name, const string& type_quote,
                               const T values[], const T& correct_result, int spacing);
template <typename T>
unsigned int testSumTriple (const string& type_name, const string& type_quote,
                            const T values[], const T& correct_result, int spacing);
unsigned int testSumTriple (const string& type_name, const string& type_quote,
                            const string values[], const string correct_results[ORDERING_COUNT], int spacing);

template <typename T>
bool testMaxArray (const string& type_name, const string& type_quote,
                   const T values[], const T& correct_result, int spacing);
template <typename T>
bool testSumArray (const string& type_name, const string& type_quote,
                   const T values[], const T& correct_result, int spacing);
bool testSumArray (const string& type_name, const string& type_quote,
                   const string values[], const string& correct_result, int spacing);

int calculateMark (double correct_float_max_t_fraction,
                   double correct_float_median_t_fraction,
                   double correct_float_sum_t_fraction,
                   bool correct_float_max_a,
                   bool correct_float_sum_a,
                   double correct_max_t_fraction,
                   double correct_median_t_fraction,
                   double correct_sum_t_fraction,
                   double correct_max_a_fraction,
                   double correct_sum_a_fraction,
                   bool is_finished);

const int COMPILE_AND_START_MARKS     = 3;
const int DID_NOT_CRASH_RUNNING_MARKS = 3;
const int COMPILE_AND_NOT_CRASH_MARKS = COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS         = 14;
const int TOTAL_MARKS                 = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

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

const int          TRIPLE_0[TRIPLE_COUNT] = { -2,        0,           3, };
const short        TRIPLE_1[TRIPLE_COUNT] = { -400,     -900,        -100, };
const unsigned int TRIPLE_2[TRIPLE_COUNT] = {  20u,      4000000000u, 50000u, };
const float        TRIPLE_3[TRIPLE_COUNT] = { -459.67f, -273.15f,     0.0f, };
const char         TRIPLE_4[TRIPLE_COUNT] = { 'z',      'x',         'y', };
const string       TRIPLE_5[TRIPLE_COUNT] = { "brawn",  "bravado",   "brain", };

const int          TRIPLE_MAX_0 =  3;
const short        TRIPLE_MAX_1 = -100;
const unsigned int TRIPLE_MAX_2 =  4000000000u;
const float        TRIPLE_MAX_3 =  0.0f;
const char         TRIPLE_MAX_4 = 'z';
const string       TRIPLE_MAX_5 = "brawn";

const int          TRIPLE_MEDIAN_0 =  0;
const short        TRIPLE_MEDIAN_1 = -400;
const unsigned int TRIPLE_MEDIAN_2 =  50000u;
const float        TRIPLE_MEDIAN_3 = -273.15f;
const char         TRIPLE_MEDIAN_4 = 'y';
const string       TRIPLE_MEDIAN_5 = "bravado";

const int          TRIPLE_SUM_0 =  1;
const short        TRIPLE_SUM_1 = -1400;
const unsigned int TRIPLE_SUM_2 =  4000050020u;
const float        TRIPLE_SUM_3 = -732.82f;  // may vary due to floating point rounding erros
const char         TRIPLE_SUM_4 = char(107);  // wraparound has happened
const string       TRIPLE_SUM_5[ORDERING_COUNT] =
{
	"brawnbravadobrain",  //	0,	1,	2
	"brawnbrainbravado",  //	0,	2,	1
	"bravadobrawnbrain",  //	1,	0,	2
	"bravadobrainbrawn",  //	1,	2,	0
	"brainbrawnbravado",  //	2,	0,	1
	"brainbravadobrawn",  //	2,	1,	0
};

const unsigned int ARRAY_SIZE = 56;
const int ARRAY_0[ARRAY_SIZE] =
{	-7, -51, 4, -2, -5, 110, 15, -3, 3, 5,
	-7, -3, 19, 4, 5, -3, 430, 141, 4, 4,
	-2, 574, 3, 7, 1518, -3, 62, 84, -2, -10,
	11, -7, -13, -4, 4, -3, 45551, -5, 3, 3,
	2, -33, 4494, -8, -5, -6, 3, -2, 7, 2,
	9, -3, -4, -4, 3, -17, };  // https://oeis.org/A056581

const short ARRAY_1[ARRAY_SIZE] =
{	1, 2, 0, 3, 1, 2, 4, 3, 5, 2,
	4, 1, 3, 5, 2, 4, 7, 5, 6, 4,
	7, 2, 6, 8, 7, 9, 1, 6, 5, 7,
	4, 2, 5, 9, 4, 2, 7, 3, 12, 4,
	2, 1, 3, 8, 2, 1, 4, 8, 12, 9,
	10, 2, 11, 3, 1, 2, };	// https://oeis.org/A125940

const unsigned int ARRAY_2[ARRAY_SIZE] =
{	1u, 2u, 3u, 1u, 4u, 4u, 5u, 10u, 1u, 6u,
	20u, 6u, 7u, 35u, 21u, 1u, 8u, 56u, 56u, 8u,
	9u, 84u, 126u, 36u, 1u, 10u, 120u, 252u, 120u, 10u,
	11u, 165u, 462u, 330u, 55u, 1u, 12u, 220u, 792u, 792u,
	220u, 12u, 13u, 286u, 1287u, 1716u, 715u, 78u, 1u, 14u,
	364u, 2002u, 3432u, 2002u, 364u, 14u, };  // https://oeis.org/A034867

const float ARRAY_3[ARRAY_SIZE] =
{	793.78f, 986.43f, 261.11f, -24.71f, 28.26f,
	-725.64f, 879.62f, 57.37f, -250.36f, -173.96f,
	-635.61f, -562.16f, -836.40f, 266.00f, -574.77f,
	-874.22f, 247.96f, -269.73f, -159.71f, 169.75f,
	-724.28f, 346.21f, 200.21f, 571.59f, 999.80f,
	-141.60f, 184.95f, -136.01f, -176.31f, -156.12f,
	885.78f, -902.95f, 48.28f, -139.74f, -39.82f,
	-630.59f, 378.06f, -212.70f, -387.88f, -956.56f,
	-835.34f, 927.54f, -868.11f, -39.98f, -257.28f,
	465.77f, 501.29f, -613.47f, 295.61f, -140.13f,
	-884.01f, 692.68f, -286.43f, 373.94f, 975.21f,
	51.45f, };  // random

const char ARRAY_4[ARRAY_SIZE] =
{	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
	'z', 'x', 'c', 'v', 'b', 'n', 'm',
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
	'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	'1', '2', '3', '4', };  // keyboard order

const string ARRAY_5[ARRAY_SIZE] =
{	"We ", "hold ", "these ", "truths ", "to ",
	"be ", "self-evident, ", "that ", "all ", "men ",
	"are ", "created ", "equal, ", "that ", "they ",
	"are ", "endowed ", "by ", "their ", "Creator ",
	"with ", "certain ", "unalienable ", "Rights, ", "that ",
	"among ", "these ", "are ", "Life, ", "Liberty ",
	"and ", "the ", "Pursuit ", "of ", "Happiness.  ",
	"That ", "to ", "secure ", "these ", "rights, ",
	"Governments ", "are ", "instituted ", "among ", "Men, ",
	"deriving ", "their ", "just ", "powers ", "from ",
	"from ", "the ", "consent ", "of ", "the ",
	"governed; ",	};  // U.S. Declaration of Independence

const int          ARRAY_MAX_0 = 45551;
const short        ARRAY_MAX_1 = 12;
const unsigned int ARRAY_MAX_2 = 3432u;
const float        ARRAY_MAX_3 = 999.80f;
const char         ARRAY_MAX_4 = 'z';
const string       ARRAY_MAX_5 = "with ";

const int          ARRAY_SUM_0 =  52872;
const short        ARRAY_SUM_1 =  253;
const unsigned int ARRAY_SUM_2 =  16383u;
const float        ARRAY_SUM_3 = -2027.93f;  // may vary due to floating point rounding erros
const char         ARRAY_SUM_4 = char(-56);  // wraparound
const string       ARRAY_SUM_5 =
	"We hold these truths to be self-evident, that all men "
	"are created equal, that they are endowed by their Creator "
	"with certain unalienable Rights, that among these are Life, Liberty "
	"and the Pursuit of Happiness.  That to secure these rights, "
	"Governments are instituted among Men, deriving their just powers from "
	"from the consent of the governed; ";



int main ()
{
	testHelperStartup("TestUnrelated6", COMPILE_AND_START_MARKS, TOTAL_MARKS);


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
	//  Print results (1)
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

	unsigned int highest1 = calculateMark(1.0f, 1.0f, 1.0f, true, true,
	                                      0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // template functions
	                                      false);                        // finished
	unsigned int mark1 = calculateMark(correct_float_max_t_fraction, correct_float_median_t_fraction, correct_float_sum_t_fraction,
	                                   correct_float_max_a, correct_float_sum_a,
	                                   0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // template functions
	                                   false);                        // finished
	assert(mark1 <= TOTAL_MARKS);
	testHelperPrintMarkPartial(mark1, highest1, TOTAL_MARKS);

	cout << endl;


	//
	//  Test 3-parameter functions
	//

	cout << endl;
	cout << "Testing max(a, b, c):" << endl;
	cout << "---------------------" << endl;
	cout << endl;
	unsigned int correct_max_t0 = testMaxTriple("int",          "",   TRIPLE_0, TRIPLE_MAX_0,  4);
	unsigned int correct_max_t1 = testMaxTriple("short",        "",   TRIPLE_1, TRIPLE_MAX_1,  6);
	unsigned int correct_max_t2 = testMaxTriple("unsigned int", "",   TRIPLE_2, TRIPLE_MAX_2, 12);
	unsigned int correct_max_t3 = testMaxTriple("float",        "",   TRIPLE_3, TRIPLE_MAX_3,  8);
	unsigned int correct_max_t4 = testMaxTriple("char",         "'",  TRIPLE_4, TRIPLE_MAX_4,  4);
	unsigned int correct_max_t5 = testMaxTriple("string",       "\"", TRIPLE_5, TRIPLE_MAX_5, 10);

	cout << endl;
	cout << "Testing median(a, b, c):" << endl;
	cout << "------------------------" << endl;
	cout << endl;
	unsigned int correct_median_t0 = testMedianTriple("int",          "",   TRIPLE_0, TRIPLE_MEDIAN_0,  4);
	unsigned int correct_median_t1 = testMedianTriple("short",        "",   TRIPLE_1, TRIPLE_MEDIAN_1,  6);
	unsigned int correct_median_t2 = testMedianTriple("unsigned int", "",   TRIPLE_2, TRIPLE_MEDIAN_2,  6);
	unsigned int correct_median_t3 = testMedianTriple("float",        "",   TRIPLE_3, TRIPLE_MEDIAN_3,  8);
	unsigned int correct_median_t4 = testMedianTriple("char",         "'",  TRIPLE_4, TRIPLE_MEDIAN_4,  4);
	unsigned int correct_median_t5 = testMedianTriple("string",       "\"", TRIPLE_5, TRIPLE_MEDIAN_5, 10);

	cout << endl;
	cout << "Testing sum(a, b, c):" << endl;
	cout << "---------------------" << endl;
	cout << endl;
	unsigned int correct_sum_t0 = testSumTriple("int",          "",   TRIPLE_0, TRIPLE_SUM_0,  4);
	unsigned int correct_sum_t1 = testSumTriple("short",        "",   TRIPLE_1, TRIPLE_SUM_1,  6);
	unsigned int correct_sum_t2 = testSumTriple("unsigned int", "",   TRIPLE_2, TRIPLE_SUM_2, 12);
	unsigned int correct_sum_t3 = testSumTriple("float",        "",   TRIPLE_3, TRIPLE_SUM_3,  8);
	unsigned int correct_sum_t4 = testSumTriple("char",         "'",  TRIPLE_4, TRIPLE_SUM_4,  4);
	unsigned int correct_sum_t5 = testSumTriple("string",       "\"", TRIPLE_5, TRIPLE_SUM_5, 20);


	//
	//  Test array-based functions
	//

	cout << endl;
	cout << "Testing max(array, count):" << endl;
	cout << "--------------------------" << endl;
	cout << endl;
	bool correct_max_a0 = testMaxArray("int",          "",   ARRAY_0, ARRAY_MAX_0, 8);
	bool correct_max_a1 = testMaxArray("short",        "",   ARRAY_1, ARRAY_MAX_1, 8);
	bool correct_max_a2 = testMaxArray("unsigned int", "",   ARRAY_2, ARRAY_MAX_2, 8);
	bool correct_max_a3 = testMaxArray("float",        "",   ARRAY_3, ARRAY_MAX_3, 8);
	bool correct_max_a4 = testMaxArray("char",         "'",  ARRAY_4, ARRAY_MAX_4, 8);
	bool correct_max_a5 = testMaxArray("string",       "\"", ARRAY_5, ARRAY_MAX_5, 8);

	unsigned int correct_max_a_count = (correct_max_a0 ? 1 : 0) +
	                                   (correct_max_a1 ? 1 : 0) +
	                                   (correct_max_a2 ? 1 : 0) +
	                                   (correct_max_a3 ? 1 : 0) +
	                                   (correct_max_a4 ? 1 : 0) +
	                                   (correct_max_a5 ? 1 : 0);
	if(correct_max_a_count == DATA_TYPE_COUNT)
		cout << "* Correct" << endl;
	else
		cout << "* Incorrect: " << (DATA_TYPE_COUNT - correct_max_a_count) << " returned wrong value" << endl;
	cout << endl;

	cout << endl;
	cout << "Testing sum(array, count):" << endl;
	cout << "--------------------------" << endl;
	cout << endl;
	bool correct_sum_a0 = testSumArray("int",          "",   ARRAY_0, ARRAY_SUM_0, 10);
	bool correct_sum_a1 = testSumArray("short",        "",   ARRAY_1, ARRAY_SUM_1, 10);
	bool correct_sum_a2 = testSumArray("unsigned int", "",   ARRAY_2, ARRAY_SUM_2, 10);
	bool correct_sum_a3 = testSumArray("float",        "",   ARRAY_3, ARRAY_SUM_3, 10);
	bool correct_sum_a4 = testSumArray("char",         "'",  ARRAY_4, ARRAY_SUM_4, 10);
	bool correct_sum_a5 = testSumArray("string",       "\"", ARRAY_5, ARRAY_SUM_5, 10);

	unsigned int correct_sum_a_count = (correct_sum_a0 ? 1 : 0) +
	                                   (correct_sum_a1 ? 1 : 0) +
	                                   (correct_sum_a2 ? 1 : 0) +
	                                   (correct_sum_a3 ? 1 : 0) +
	                                   (correct_sum_a4 ? 1 : 0) +
	                                   (correct_sum_a5 ? 1 : 0);
	if(correct_sum_a_count == DATA_TYPE_COUNT)
		cout << "* Correct" << endl;
	else
		cout << "* Incorrect: " << (DATA_TYPE_COUNT - correct_sum_a_count) << " returned wrong value" << endl;
	cout << endl;


	//
	//  Print results (2)
	//

	unsigned int correct_max_t_count = correct_max_t0 +
	                                   correct_max_t1 +
	                                   correct_max_t2 +
	                                   correct_max_t3 +
	                                   correct_max_t4 +
	                                   correct_max_t5;
	unsigned int correct_median_t_count = correct_median_t0 +
	                                      correct_median_t1 +
	                                      correct_median_t2 +
	                                      correct_median_t3 +
	                                      correct_median_t4 +
	                                      correct_median_t5;
	unsigned int correct_sum_t_count = correct_sum_t0 +
	                                   correct_sum_t1 +
	                                   correct_sum_t2 +
	                                   correct_sum_t3 +
	                                   correct_sum_t4 +
	                                   correct_sum_t5;

	double correct_max_t_fraction    = (double)(correct_max_t_count   ) / TRIPLE_SUM;
	double correct_median_t_fraction = (double)(correct_median_t_count) / TRIPLE_SUM;
	double correct_sum_t_fraction    = (double)(correct_sum_t_count   ) / TRIPLE_SUM;
	double correct_max_a_fraction    = (double)(correct_max_a_count   ) / DATA_TYPE_COUNT;
	double correct_sum_a_fraction    = (double)(correct_sum_a_count   ) / DATA_TYPE_COUNT;

	testHelperPrintSummaryHeader(26, 2, DID_NOT_CRASH_RUNNING_MARKS);
	testHelperPrintSummaryLine("maxFloat   (a, b, c)",   correct_float_max_t,    ORDERING_COUNT);
	testHelperPrintSummaryLine("medianFloat(a, b, c)",   correct_float_median_t, ORDERING_COUNT);
	testHelperPrintSummaryLine("sumFloat   (a, b, c)",   correct_float_sum_t,    ORDERING_COUNT);
	testHelperPrintSummaryLine("maxFloat(array, count)", correct_float_max_a);
	testHelperPrintSummaryLine("sumFloat(array, count)", correct_float_sum_a);
	testHelperPrintSummaryLine("max<>(a, b, c)",       correct_max_t_count,    TRIPLE_SUM);
	testHelperPrintSummaryLine("median<>(a, b, c)",    correct_median_t_count, TRIPLE_SUM);
	testHelperPrintSummaryLine("sum<>(a, b, c)",       correct_sum_t_count,    TRIPLE_SUM);
	testHelperPrintSummaryLine("max<>(array, count)",  correct_max_a_count,    DATA_TYPE_COUNT);
	testHelperPrintSummaryLine("sum<>(array, count)",  correct_sum_a_count,    DATA_TYPE_COUNT);

	unsigned int mark2 = calculateMark(correct_float_max_t_fraction, correct_float_median_t_fraction, correct_float_sum_t_fraction,
	                                   correct_float_max_a, correct_float_sum_a,
	                                   correct_max_t_fraction, correct_median_t_fraction, correct_sum_t_fraction,
	                                   correct_max_a_fraction, correct_sum_a_fraction,
	                                   true);
	assert(mark2 <= TOTAL_MARKS);
	testHelperPrintMark(mark2, TOTAL_MARKS);

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

template <typename T>
unsigned int testMaxTriple (const string& type_name, const string& type_quote,
                            const T values[], const T& correct_result, int spacing)
{
	assert(type_name != "");
	assert(values    != NULL);
	assert(spacing   >  0);

	cout << "Testing max<" << type_name << "> with values "
	     << type_quote << values[0] << type_quote << ", "
	     << type_quote << values[1] << type_quote << ", and "
	     << type_quote << values[2] << type_quote << ":" << endl;

	unsigned int correct_count = 0;
	for(unsigned int i = 0; i < ORDERING_COUNT; i++)
	{
		unsigned int index0 = ORDERINGS[i][0];
		unsigned int index1 = ORDERINGS[i][1];
		unsigned int index2 = ORDERINGS[i][2];

		cout << "\tmax<" << type_name << ">("
		     << type_quote << values[index0] << type_quote << ", "
		     << type_quote << values[index1] << type_quote << ", "
		     << type_quote << values[index2] << type_quote << ") = ";
		T result = max(values[index0], values[index1], values[index2]);
		stringstream ss;
		ss << type_quote << result << type_quote;
		cout << setw(spacing) << left << ss.str();

		if(result == correct_result)
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

template <typename T>
unsigned int testMedianTriple (const string& type_name, const string& type_quote,
                               const T values[], const T& correct_result, int spacing)
{
	assert(type_name != "");
	assert(values    != NULL);
	assert(spacing   >  0);

	cout << "Testing median<" << type_name << "> with values "
	     << type_quote << values[0] << type_quote << ", "
	     << type_quote << values[1] << type_quote << ", and "
	     << type_quote << values[2] << type_quote << ":" << endl;

	unsigned int correct_count = 0;
	for(unsigned int i = 0; i < ORDERING_COUNT; i++)
	{
		unsigned int index0 = ORDERINGS[i][0];
		unsigned int index1 = ORDERINGS[i][1];
		unsigned int index2 = ORDERINGS[i][2];

		cout << "\tmedian<" << type_name << ">("
		     << type_quote << values[index0] << type_quote << ", "
		     << type_quote << values[index1] << type_quote << ", "
		     << type_quote << values[index2] << type_quote << ") = ";
		T result = median(values[index0], values[index1], values[index2]);
		stringstream ss;
		ss << type_quote << result << type_quote;
		cout << setw(spacing) << left << ss.str();

		if(result == correct_result)
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

template <typename T>
unsigned int testSumTriple (const string& type_name, const string& type_quote,
                            const T values[], const T& correct_result, int spacing)
{
	assert(type_name != "");
	assert(values    != NULL);
	assert(spacing   >  0);

	cout << "Testing sum<" << type_name << "> with values "
	     << type_quote << values[0] << type_quote << ", "
	     << type_quote << values[1] << type_quote << ", and "
	     << type_quote << values[2] << type_quote << ":" << endl;

	unsigned int correct_count = 0;
	for(unsigned int i = 0; i < ORDERING_COUNT; i++)
	{
		unsigned int index0 = ORDERINGS[i][0];
		unsigned int index1 = ORDERINGS[i][1];
		unsigned int index2 = ORDERINGS[i][2];

		cout << "\tsum<" << type_name << ">("
		     << type_quote << values[index0] << type_quote << ", "
		     << type_quote << values[index1] << type_quote << ", "
		     << type_quote << values[index2] << type_quote << ") = ";
		T result = sum(values[index0], values[index1], values[index2]);
		stringstream ss;
		ss << type_quote << result << type_quote;
		cout << setw(spacing) << left << ss.str();

		bool is_correct = result == correct_result;
		if(typeid(T) == typeid(float))  // allow for floating point rounding errors
			is_correct = fabs((float)(result - correct_result)) <= 0.001f;
		if(is_correct)
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

unsigned int testSumTriple (const string& type_name, const string& type_quote,
                            const string values[], const string correct_results[ORDERING_COUNT], int spacing)
{
	assert(type_name != "");
	assert(values    != NULL);
	assert(spacing   >  0);

	cout << "Testing sum<" << type_name << "> with values "
	     << type_quote << values[0] << type_quote << ", "
	     << type_quote << values[1] << type_quote << ", and "
	     << type_quote << values[2] << type_quote << ":" << endl;

	unsigned int correct_count = 0;
	for(unsigned int i = 0; i < ORDERING_COUNT; i++)
	{
		unsigned int index0 = ORDERINGS[i][0];
		unsigned int index1 = ORDERINGS[i][1];
		unsigned int index2 = ORDERINGS[i][2];

		cout << "\tsum<" << type_name << ">("
		     << type_quote << values[index0] << type_quote << ", "
		     << type_quote << values[index1] << type_quote << ", "
		     << type_quote << values[index2] << type_quote << ") = ";
		string result = sum(values[index0], values[index1], values[index2]);
		stringstream ss;
		ss << type_quote << result << type_quote;
		cout << setw(spacing) << left << ss.str();

		if(result == correct_results[i])
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

template <typename T>
bool testMaxArray (const string& type_name, const string& type_quote,
                   const T values[], const T& correct_result, int spacing)
{
	assert(type_name != "");
	assert(values    != NULL);
	assert(spacing   >  0);

	stringstream ss1;
	ss1 << "<" << type_name << ">";
	cout << "Testing max" << setw(14) << ss1.str() << "(ARRAY, " << ARRAY_SIZE << ") = ";
	T result = max(values, ARRAY_SIZE);
	stringstream ss2;
	ss2 << type_quote << result << type_quote;
	cout << setw(spacing) << left << ss2.str();

	if(result == correct_result)
	{
		cout << " Correct" << endl;
		return true;
	}
	else
	{
		cout << " Incorrect" << endl;
		return false;
	}
}

template <typename T>
bool testSumArray (const string& type_name, const string& type_quote,
                   const T values[], const T& correct_result, int spacing)
{
	assert(type_name != "");
	assert(values    != NULL);
	assert(spacing   >  0);

	stringstream ss1;
	ss1 << "<" << type_name << ">";
	cout << "Testing sum" << setw(14) << ss1.str() << "(ARRAY, " << ARRAY_SIZE << ") = ";
	T result = sum(values, ARRAY_SIZE);
	stringstream ss2;
	ss2 << type_quote << result << type_quote;
	cout << setw(spacing) << left << ss2.str();

	bool is_correct = result == correct_result;
	if(typeid(T) == typeid(float))  // allow for floating point rounding errors
		is_correct = fabs((float)(result - correct_result)) <= 0.001f;
	if(is_correct)
	{
		cout << " Correct" << endl;
		return true;
	}
	else
	{
		cout << " Incorrect" << endl;
		return false;
	}
}

bool testSumArray (const string& type_name, const string& type_quote,
                   const string values[], const string& correct_result, int spacing)
{
	assert(type_name != "");
	assert(values    != NULL);
	assert(spacing   >  0);

	stringstream ss1;
	ss1 << "<" << type_name << ">";
	cout << "Testing sum" << setw(14) << ss1.str() << "(ARRAY, " << ARRAY_SIZE << ") =" << endl;
	string result = sum(values, ARRAY_SIZE);
	stringstream ss2;
	ss2 << type_quote << result << type_quote;
	cout << setw(spacing) << left << ss2.str() << endl;

	if(result == correct_result)
	{
		cout << "\tCorrect" << endl;
		return true;
	}
	else
	{
		cout << "\tIncorrect" << endl;
		return false;
	}
}

int calculateMark (double correct_float_max_t_fraction,
                   double correct_float_median_t_fraction,
                   double correct_float_sum_t_fraction,
                   bool correct_float_max_a,
                   bool correct_float_sum_a,
                   double correct_max_t_fraction,
                   double correct_median_t_fraction,
                   double correct_sum_t_fraction,
                   double correct_max_a_fraction,
                   double correct_sum_a_fraction,
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

	bool correct_any_t = correct_max_t_fraction    == 1.0 ||
	                     correct_median_t_fraction == 1.0 ||
	                     correct_sum_t_fraction    == 1.0;
	bool correct_either_a = correct_max_a_fraction == 1.0 ||
	                        correct_sum_a_fraction == 1.0;

	if(correct_any_t)
		mark += 2;
	if(correct_max_t_fraction == 1.0f)
		mark += 1;
	if(correct_median_t_fraction == 1.0f)
		mark += 1;
	if(correct_sum_t_fraction == 1.0f)
		mark += 1;
	if(correct_either_a)
		mark += 2;
	if(correct_max_a_fraction == 1.0f)
		mark += 1;
	if(correct_sum_a_fraction == 1.0f)
		mark += 1;

	assert(mark <= TOTAL_MARKS);
	return mark;
}