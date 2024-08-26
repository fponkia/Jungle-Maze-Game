//
//  TestObstructedNode6.cpp
//
//  A test program for the ObstructedNode module.
//
//  This program is to be used with Assignment 6: Part B for
//    CS115, 202210.
//
//

#include "ObstructedNode.h"
#include "ObstructedNode.h"  // repeated to test for #include errors

#include <cassert>
#include <climits>
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <typeinfo>  // for typeid

#include "TestHelper.h"

#include "Location.h"
#include "Node.h"

using namespace std;
namespace
{
	struct CheckResult
	{
		bool is_initialized;
		bool is_description_correct;
		bool is_north_correct;
		bool is_south_correct;
		bool is_east_correct;
		bool is_west_correct;
		bool is_death_correct;
		bool is_obstructed_correct;
		bool is_required_correct;
		bool is_failure_correct;
		bool is_success_correct;
	};

	struct PrintResult
	{
		bool is_anything;
		bool is_newline_correct;
		bool is_token_count_correct;
		bool is_node_type_correct;
		bool is_description_correct;
		bool is_north_correct;
		bool is_south_correct;
		bool is_east_correct;
		bool is_west_correct;
		bool is_required_correct;
		bool is_failure_correct;
		bool is_success_correct;
	};

}  // end on anonymous namespace



int main ();

unsigned int extractField (const Location& location);
CheckResult checkNode (const Node& node,
                       unsigned int correct_description,
                       unsigned int correct_north,
                       unsigned int correct_south,
                       unsigned int correct_east,
                       unsigned int correct_west,
                       char correct_required_item,
                       unsigned int correct_failure,
                       unsigned int correct_success,
                       bool is_print_correct);
CheckResult combine (const CheckResult& result1,
                     const CheckResult& result2);
unsigned int countCheckResult (const CheckResult& result);
double scoreCheckResult (const CheckResult& result);

void debugPrintCorrect (char node_type,
                        unsigned int description,
                        unsigned int north,
                        unsigned int south,
                        unsigned int east,
                        unsigned int west,
                        char required,
                        unsigned int failure,
                        unsigned int success);
PrintResult checkPrinted (const string& printed,
                          unsigned int correct_description,
                          unsigned int correct_north,
                          unsigned int correct_south,
                          unsigned int correct_east,
                          unsigned int correct_west,
                          char correct_required,
                          unsigned int correct_failure,
                          unsigned int correct_success,
                          bool is_print_correct);
string tabsToSpaces (const string& str);
unsigned int countInString (const string& str, char search_for);
unsigned int countPrintResult (const PrintResult& result);
double scorePrintResult (const PrintResult& result);

const int COMPILE_AND_START_MARKS     = 3;
const int DID_NOT_CRASH_RUNNING_MARKS = 4;
const int COMPILE_AND_NOT_CRASH_MARKS = COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS         = 13;
const int TOTAL_MARKS                 = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

const unsigned int COUNT_CHECK_RESULT_MAX = 10;
const unsigned int COUNT_PRINT_RESULT_MAX = 12;

const unsigned int PRINT_TOKEN_COUNT_CORRECT = 9;

const unsigned int TEST_DESCRIPTION_1 = 1;
const unsigned int TEST_NORTH_1       = 2;
const unsigned int TEST_SOUTH_1       = 3;
const unsigned int TEST_EAST_1        = 4;
const unsigned int TEST_WEST_1        = 5;
const char         TEST_NODE_TYPE_1   = 'O';
const char         TEST_REQUIRED_1    = '6';
const unsigned int TEST_FAILURE_1     = 7;
const unsigned int TEST_SUCCESS_1     = 8;

const unsigned int TEST_DESCRIPTION_2 = 100;
const unsigned int TEST_NORTH_2       = 86;
const unsigned int TEST_SOUTH_2       = 73;
const unsigned int TEST_EAST_2        = 61;
const unsigned int TEST_WEST_2        = 50;
const char         TEST_NODE_TYPE_2   = 'O';
const char         TEST_REQUIRED_2    = 'm';
const unsigned int TEST_FAILURE_2     = 160;
const unsigned int TEST_SUCCESS_2     = 256;



int main ()
{
	testHelperStartup("TestObstructedNode6", COMPILE_AND_START_MARKS, TOTAL_MARKS);

	//
	//  Test ObstructedNode class
	//

	cout << "Checking inheritance" << endl;
	Node base_node;
	ObstructedNode* p_base_node = (ObstructedNode*)(&base_node);  // forced cast
	bool correct_inheritance = static_cast<Node*>(p_base_node) != NULL;
	if(correct_inheritance)
		cout << "* Correct" << endl;
	else
		cout << "* Incorrect: ObstructedNode contains unnecessary data" << endl;
	cout << endl;

	cout << "Checking ObstructedNode size in bytes" << endl;
	size_t node_bytes                    = sizeof(Node);
	size_t obstructed_node_bytes         = sizeof(ObstructedNode);
	size_t obstructed_node_bytes_correct = sizeof(Node) + sizeof(char) + sizeof(unsigned int) * 2;
	bool correct_node_bytes = false;
	if(obstructed_node_bytes <= node_bytes)
		cout << "* Incorrect: ObstructedNode should contain more data" << endl;
	else if(obstructed_node_bytes > obstructed_node_bytes_correct * 2)
		cout << "* Incorrect: ObstructedNode contains unnecessary data" << endl;
	else
	{
		cout << "* Correct" << endl;
		correct_node_bytes = true;
	}
	cout << endl;


	//
	//  Test initializing constructor
	//

	cout << "Testing initializing constructor (#1)" << endl;
	ObstructedNode* p_node_init1 = new ObstructedNode(TEST_DESCRIPTION_1,
	                                                  TEST_NORTH_1, TEST_SOUTH_1, TEST_EAST_1, TEST_WEST_1,
	                                                  TEST_REQUIRED_1, TEST_FAILURE_1, TEST_SUCCESS_1);
	CheckResult result_init1 = checkNode(*p_node_init1, TEST_DESCRIPTION_1,
	                                     TEST_NORTH_1, TEST_SOUTH_1, TEST_EAST_1, TEST_WEST_1,
		                                 TEST_REQUIRED_1, TEST_FAILURE_1, TEST_SUCCESS_1,
		                                 true);
	cout << endl;

	cout << "Testing debugPrint" << endl;
	debugPrintCorrect(TEST_NODE_TYPE_1, TEST_DESCRIPTION_1,
	                  TEST_NORTH_1, TEST_SOUTH_1, TEST_EAST_1, TEST_WEST_1,
		              TEST_REQUIRED_1, TEST_FAILURE_1, TEST_SUCCESS_1);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_node_init1->debugPrint();
	string captured_init1 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	PrintResult print_result_init1 = checkPrinted(captured_init1, TEST_DESCRIPTION_1,
		                                          TEST_NORTH_1, TEST_SOUTH_1, TEST_EAST_1, TEST_WEST_1,
	                                              TEST_REQUIRED_1, TEST_FAILURE_1, TEST_SUCCESS_1,
	                                              true);
	cout << endl;

	cout << "Testing initializing constructor (#2)" << endl;
	ObstructedNode* p_node_init2 = new ObstructedNode(TEST_DESCRIPTION_2,
	                                                  TEST_NORTH_2, TEST_SOUTH_2, TEST_EAST_2, TEST_WEST_2,
	                                                  TEST_REQUIRED_2, TEST_FAILURE_2, TEST_SUCCESS_2);
	CheckResult result_init2 = checkNode(*p_node_init2, TEST_DESCRIPTION_2,
	                                     TEST_NORTH_2, TEST_SOUTH_2, TEST_EAST_2, TEST_WEST_2,
	                                     TEST_REQUIRED_2, TEST_FAILURE_2, TEST_SUCCESS_2,
		                                 true);
	cout << endl;

	cout << "Testing debugPrint" << endl;
	debugPrintCorrect(TEST_NODE_TYPE_2, TEST_DESCRIPTION_2,
	                  TEST_NORTH_2, TEST_SOUTH_2, TEST_EAST_2, TEST_WEST_2,
		              TEST_REQUIRED_2, TEST_FAILURE_2, TEST_SUCCESS_2);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_node_init2->debugPrint();
	string captured_init2 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	PrintResult print_result_init2 = checkPrinted(captured_init2, TEST_DESCRIPTION_2,
		                                          TEST_NORTH_2, TEST_SOUTH_2, TEST_EAST_2, TEST_WEST_2,
	                                              TEST_REQUIRED_2, TEST_FAILURE_2, TEST_SUCCESS_2,
	                                              true);
	cout << endl;


	//
	//  Test copy constructor, assignment operator
	//

	cout << "Testing copying" << endl;
	ObstructedNode* p_node_copy = new ObstructedNode(*p_node_init1);
	CheckResult result_copy = checkNode(*p_node_copy, TEST_DESCRIPTION_1,
	                                    TEST_NORTH_1, TEST_SOUTH_1, TEST_EAST_1, TEST_WEST_1,
	                                    TEST_REQUIRED_1, TEST_FAILURE_1, TEST_SUCCESS_1,
		                                true);
	cout << endl;

	cout << "Testing assignment operator (normal use)" << endl;
	*p_node_copy = *p_node_init2;
	CheckResult result_assign = checkNode(*p_node_copy, TEST_DESCRIPTION_2,
	                                      TEST_NORTH_2, TEST_SOUTH_2, TEST_EAST_2, TEST_WEST_2,
	                                      TEST_REQUIRED_2, TEST_FAILURE_2, TEST_SUCCESS_2,
		                                  true);
	cout << endl;

	cout << "Testing self-assignment" << endl;
	*p_node_copy = *p_node_copy;
	CheckResult result_self = checkNode(*p_node_copy, TEST_DESCRIPTION_2,
	                                    TEST_NORTH_2, TEST_SOUTH_2, TEST_EAST_2, TEST_WEST_2,
	                                    TEST_REQUIRED_2, TEST_FAILURE_2, TEST_SUCCESS_2,
		                                true);
	cout << endl;

	cout << "Testing chained assignment" << endl;
	*p_node_copy = *p_node_init2 = *p_node_init1;
	CheckResult result_chained1 = checkNode(*p_node_copy, TEST_DESCRIPTION_1,
	                                        TEST_NORTH_1, TEST_SOUTH_1, TEST_EAST_1, TEST_WEST_1,
	                                        TEST_REQUIRED_1, TEST_FAILURE_1, TEST_SUCCESS_1,
		                                    false);
	CheckResult result_chained2 = checkNode(*p_node_init2, TEST_DESCRIPTION_1,
	                                        TEST_NORTH_1, TEST_SOUTH_1, TEST_EAST_1, TEST_WEST_1,
	                                        TEST_REQUIRED_1, TEST_FAILURE_1, TEST_SUCCESS_1,
		                                    false);
	if(countCheckResult(result_chained1) == COUNT_CHECK_RESULT_MAX &&
	   countCheckResult(result_chained2) == COUNT_CHECK_RESULT_MAX)
	{
		cout << "* Correct" << endl;
	}
	cout << endl;

	cout << "Destroying Nodes" << endl;
	delete p_node_init1;
	delete p_node_init2;
	delete p_node_copy;
	p_node_init1 = NULL;
	p_node_init2 = NULL;
	p_node_copy  = NULL;
	cout << "* Completed without crashing" << endl;
	cout << endl;


	//
	//  Print results
	//

	unsigned int init_result_count = countCheckResult(result_init1) +
	                                 countCheckResult(result_init2);

	unsigned int construct_print_count = countPrintResult(print_result_init1) +
	                                     countPrintResult(print_result_init2);

	unsigned int copy_result_count    = countCheckResult(result_copy);
	unsigned int assign_result_count  = countCheckResult(result_assign);
	unsigned int self_result_count    = countCheckResult(result_self);
	unsigned int chained_result_count = countCheckResult(result_chained1) +
	                                    countCheckResult(result_chained2);

	CheckResult result_init_combined = combine(result_init1, result_init2);
	CheckResult result_assign_combined = combine(result_assign, result_self);
	result_assign_combined = combine(result_assign_combined, result_chained1);
	result_assign_combined = combine(result_assign_combined, result_chained2);

	testHelperPrintSummaryHeader(24, 2, DID_NOT_CRASH_RUNNING_MARKS);
	testHelperPrintSummaryLine("Inheritance",         correct_inheritance);
	testHelperPrintSummaryLine("Class declaration",   correct_node_bytes);
	testHelperPrintSummaryLine("Init. constructor",   init_result_count,     COUNT_CHECK_RESULT_MAX * 2);
	testHelperPrintSummaryLine("debugPrint",          construct_print_count, COUNT_PRINT_RESULT_MAX * 2);
	testHelperPrintSummaryLine("Copy constructor",    copy_result_count,     COUNT_CHECK_RESULT_MAX);
	testHelperPrintSummaryLine("Assignment operator", assign_result_count,   COUNT_CHECK_RESULT_MAX);
	testHelperPrintSummaryLine("Self-assignment",     self_result_count,     COUNT_CHECK_RESULT_MAX);
	testHelperPrintSummaryLine("Chained assignment",  chained_result_count,  COUNT_CHECK_RESULT_MAX * 2);

	unsigned int mark = COMPILE_AND_NOT_CRASH_MARKS;

	if(correct_inheritance && correct_node_bytes)
		mark += 1;
	mark += (int)(scoreCheckResult(result_init_combined) * 2.0);
	mark += (int)((scorePrintResult(print_result_init1) +
	               scorePrintResult(print_result_init2)) * 2.0);
	mark += (int)(scoreCheckResult(result_copy) * 2.0);
	mark += (int)(scoreCheckResult(result_assign_combined) * 4.0);

	assert(mark <= TOTAL_MARKS);
	testHelperPrintMark(mark, TOTAL_MARKS);

	testHelperWaitForEnter();
	return 0;
}



unsigned int extractField (const Location& location)
{
	unsigned int size = sizeof(Location);
	if(size == 0)  // doesn't seem to happen on my computer, always at least 1
		return 0;

	assert(size > 0);
	if(size > sizeof(unsigned int))
		size = sizeof(unsigned int);

	unsigned int result = 0;
	const unsigned char* location_as_chars = reinterpret_cast<const unsigned char*>(&location);
	      unsigned char*   result_as_chars = reinterpret_cast<      unsigned char*>(&result);
	memcpy(result_as_chars, location_as_chars, size);
	return result;
}

CheckResult checkNode (const Node& node,
                       unsigned int correct_description,
                       unsigned int correct_north,
                       unsigned int correct_south,
                       unsigned int correct_east,
                       unsigned int correct_west,
                       char correct_required_item,
                       unsigned int correct_failure,
                       unsigned int correct_success,
                       bool is_print_correct)
{
	CheckResult result;

	unsigned int description   = node.getDescription();
	unsigned int north         = extractField(node.getNorth());
	unsigned int south         = extractField(node.getSouth());
	unsigned int east          = extractField(node.getEast ());
	unsigned int west          = extractField(node.getWest ());
	bool         is_death      = node.isDeath();
	bool         is_obstructed = node.isObstructed();
	char         required_item = node.getRequiredItem();
	unsigned int failure;
	unsigned int success;

	result.is_description_correct = description   == correct_description;
	result.is_north_correct       = north         == correct_north;
	result.is_south_correct       = south         == correct_south;
	result.is_east_correct        = east          == correct_east;
	result.is_west_correct        = west          == correct_west;
	result.is_death_correct       = is_death      == false;
	result.is_obstructed_correct  = is_obstructed == true;
	result.is_required_correct    = required_item == correct_required_item;

	if(is_obstructed)
	{
		failure = node.getDescriptionFailure();
		success = node.getDescriptionSuccess();

		result.is_failure_correct = failure == correct_failure;
		result.is_success_correct = success == correct_success;
	}
	else
	{
		result.is_failure_correct = false;
		result.is_success_correct = false;
	}

	if(!result.is_description_correct)
		cout << "* Incorrect: Description is " << description << ", but should be " << correct_description << endl;
	else if(!result.is_north_correct)
		cout << "* Incorrect: North node index is " << north << ", but should be " << correct_north << endl;
	else if(!result.is_south_correct)
		cout << "* Incorrect: South node index is " << south << ", but should be " << correct_south << endl;
	else if(!result.is_east_correct)
		cout << "* Incorrect: East node index is " << east << ", but should be " << correct_east << endl;
	else if(!result.is_west_correct)
		cout << "* Incorrect: West node index is " << west << ", but should be " << correct_west << endl;
	else if(!result.is_death_correct)
	{
		if(is_death)
			cout << "* Incorrect: This is a death node but it shouldn't be" << endl;
		else
			cout << "* Incorrect: This is not a death node but it should be" << endl;
	}
	else if(!result.is_obstructed_correct)
		cout << "* Incorrect: This node is not obstructed but it should be" << endl;
	else if(!result.is_required_correct)
		cout << "* Incorrect: Required item is '" << required_item << "', but should be '" << correct_required_item << "'" << endl;
	else if(!result.is_failure_correct)
		cout << "* Incorrect: Failure description is " << failure << ", but should be " << correct_failure << endl;
	else if(!result.is_success_correct)
		cout << "* Incorrect: Failure description is " << success << ", but should be " << correct_success << endl;
	else if(is_print_correct)
		cout << "* Correct" << endl;

	return result;
}

CheckResult combine (const CheckResult& result1,
                     const CheckResult& result2)
{
	CheckResult combined;
	combined.is_description_correct = result1.is_description_correct && result2.is_description_correct;
	combined.is_north_correct       = result1.is_north_correct       && result2.is_north_correct;
	combined.is_south_correct       = result1.is_south_correct       && result2.is_south_correct;
	combined.is_east_correct        = result1.is_east_correct        && result2.is_east_correct;
	combined.is_west_correct        = result1.is_west_correct        && result2.is_west_correct;
	combined.is_death_correct       = result1.is_death_correct       && result2.is_death_correct;
	combined.is_obstructed_correct  = result1.is_obstructed_correct  && result2.is_obstructed_correct;
	combined.is_required_correct    = result1.is_required_correct    && result2.is_required_correct;
	combined.is_failure_correct     = result1.is_failure_correct     && result2.is_failure_correct;
	combined.is_success_correct     = result1.is_success_correct     && result2.is_success_correct;
	return combined;
}

unsigned int countCheckResult (const CheckResult& result)
{
	unsigned int total = 0;
	if(result.is_description_correct)
		total++;
	if(result.is_north_correct)
		total++;
	if(result.is_south_correct)
		total++;
	if(result.is_east_correct)
		total++;
	if(result.is_west_correct)
		total++;
	if(result.is_death_correct)
		total++;
	if(result.is_obstructed_correct)
		total++;
	if(result.is_required_correct)
		total++;
	if(result.is_failure_correct)
		total++;
	if(result.is_success_correct)
		total++;
	return total;
}

double scoreCheckResult (const CheckResult& result)
{
	unsigned int total = 0;
	if(result.is_description_correct)
		total += 2;
	if(result.is_north_correct)
		total += 1;
	if(result.is_south_correct)
		total += 1;
	if(result.is_east_correct)
		total += 1;
	if(result.is_west_correct)
		total += 1;
	if(result.is_death_correct)
		total += 2;
	if(result.is_obstructed_correct)
		total += 1;
	if(result.is_required_correct)
		total += 2;
	if(result.is_failure_correct)
		total += 2;
	if(result.is_success_correct)
		total += 2;
	assert(total <= 15.0);
	return total / 15.0;
}



void debugPrintCorrect (char node_type,
                        unsigned int description,
                        unsigned int north,
                        unsigned int south,
                        unsigned int east,
                        unsigned int west,
                        char required,
                        unsigned int failure,
                        unsigned int success)
{
	cout << node_type << "\t"
	     << description << "\t"
	     << north << "\t"
	     << south << "\t"
	     << east << "\t"
	     << west << "\t"
	     << required << "\t"
	     << failure << "\t"
	     << success << "  // correct" << endl;
}

PrintResult checkPrinted (const string& printed,
                          unsigned int correct_description,
                          unsigned int correct_north,
                          unsigned int correct_south,
                          unsigned int correct_east,
                          unsigned int correct_west,
                          char correct_required,
                          unsigned int correct_failure,
                          unsigned int correct_success,
                          bool is_print_correct)
{
	PrintResult result;
	result.is_anything            = false;
	result.is_newline_correct     = false;
	result.is_token_count_correct = false;
	result.is_node_type_correct   = false;
	result.is_description_correct = false;
	result.is_north_correct       = false;
	result.is_south_correct       = false;
	result.is_east_correct        = false;
	result.is_west_correct        = false;
	result.is_required_correct    = false;
	result.is_failure_correct     = false;
	result.is_success_correct     = false;

	//  Check overall line structure

	if(printed.empty())
	{
		cout << "* Incorrect: Printed nothing" << endl;
		return result;
	}
	result.is_anything = true;

	if(printed[printed.size() - 1] != '\n')
	{
		cout << "* Incorrect: Printed data is missing a newline at the end" << endl;
		return result;
	}
	if(countInString(printed,'\n') > 1)
	{
		cout << "* Incorrect: Printed multiple newlines" << endl;
		return result;
	}
	result.is_newline_correct = true;

	//  Split up line into tokens

	string without_newline = printed.substr(0, printed.length() - 1);
	vector<string> tokens = testHelperSplitWithoutEmpty(tabsToSpaces(without_newline), ' ');
	if(tokens.size() != PRINT_TOKEN_COUNT_CORRECT)
	{
		cout << "* Incorrect: Printed " << tokens.size() << " tokens, should be " << PRINT_TOKEN_COUNT_CORRECT << endl;
		return result;
	}
	result.is_token_count_correct = true;

	//  Check node type
	
	assert(!tokens[0].empty());
	if(tokens[0].size() != 1)
		cout << "* Incorrect: Node type \"" << tokens[0] << "\" should be a single character" << endl;
	else
	{
		char correct_node_type = 'O';
		if(tokens[0][0] == correct_node_type)
			result.is_node_type_correct = true;
		else
			cout << "* Incorrect: Node type is '" << tokens[0] << "', but should be '" << correct_node_type << "'" << endl;
	}

	//  Check description
	
	stringstream description_ss;
	description_ss << correct_description;
	string description_string = description_ss.str();
	if(tokens[1] != description_string)
		cout << "* Incorrect: Description printed as " << tokens[1] << ", but should be " << description_string << endl;
	else
		result.is_description_correct = true;

	//  Check links to other nodes
	
	stringstream north_ss;
	north_ss << correct_north;
	string north_string = north_ss.str();
	if(tokens[2] != north_string)
		cout << "* Incorrect: Node index to the north is " << tokens[2] << ", but should be " << north_string << endl;
	else
		result.is_north_correct = true;

	stringstream south_ss;
	south_ss << correct_south;
	string south_string = south_ss.str();
	if(tokens[3] != south_string)
		cout << "* Incorrect: Node index to the south is " << tokens[3] << ", but should be " << south_string << endl;
	else
		result.is_south_correct = true;

	stringstream east_ss;
	east_ss << correct_east;
	string east_string = east_ss.str();
	if(tokens[4] != east_string)
		cout << "* Incorrect: Node index to the east is " << tokens[4] << ", but should be " << east_string << endl;
	else
		result.is_east_correct = true;

	stringstream west_ss;
	west_ss << correct_west;
	string west_string = west_ss.str();
	if(tokens[5] != west_string)
		cout << "* Incorrect: Node index to the west is " << tokens[5] << ", but should be " << west_string << endl;
	else
		result.is_west_correct = true;

	stringstream required_ss;
	required_ss << correct_required;
	string required_string = required_ss.str();
	if(tokens[6] != required_string)
		cout << "* Incorrect: Required item is '" << tokens[6] << "', but should be '" << required_string << "'" << endl;
	else
		result.is_required_correct = true;

	stringstream failure_ss;
	failure_ss << correct_failure;
	string failure_string = failure_ss.str();
	if(tokens[7] != failure_string)
		cout << "* Incorrect: Failure description is " << tokens[7] << ", but should be " << failure_string << endl;
	else
		result.is_failure_correct = true;

	stringstream success_ss;
	success_ss << correct_success;
	string success_string = success_ss.str();
	if(tokens[8] != success_string)
		cout << "* Incorrect: Success description is " << tokens[8] << ", but should be " << success_string << endl;
	else
		result.is_success_correct = true;

	//  Check if all correct
	
	if(countPrintResult(result) == COUNT_PRINT_RESULT_MAX && is_print_correct)
		cout << "* Correct" << endl;

	return result;
}

string tabsToSpaces (const string& str)
{
	string result = str;
	for(unsigned int i = 0; i < str.size(); i++)
		if(result[i] == '\t')
			result[i] = ' ';
	return result;
}

unsigned int countInString (const string& str, char search_for)
{
	unsigned int count = 0;
	for(unsigned int i = 0; i < str.size(); i++)
		if(str[i] == search_for)
			count++;
	return count;
}

unsigned int countPrintResult (const PrintResult& result)
{
	if(!result.is_anything)
		return 0;
	if(!result.is_newline_correct)
		return 1;
	if(!result.is_token_count_correct)
		return 2;

	unsigned int total = 3;
	if(result.is_node_type_correct)
		total++;
	if(result.is_description_correct)
		total++;
	if(result.is_north_correct)
		total++;
	if(result.is_south_correct)
		total++;
	if(result.is_east_correct)
		total++;
	if(result.is_west_correct)
		total++;
	if(result.is_required_correct)
		total++;
	if(result.is_failure_correct)
		total++;
	if(result.is_success_correct)
		total++;
	return total;
}

double scorePrintResult (const PrintResult& result)
{
	if(!result.is_anything)
		return 0.0;

	unsigned int total = 0;
	if(result.is_newline_correct)
		total += 1;
	if(result.is_token_count_correct)
		total += 2;
	if(result.is_node_type_correct)
		total += 2;
	if(result.is_description_correct)
		total += 1;
	if(result.is_north_correct)
		total += 1;
	if(result.is_south_correct)
		total += 1;
	if(result.is_east_correct)
		total += 1;
	if(result.is_west_correct)
		total += 1;
	if(result.is_required_correct)
		total += 2;
	if(result.is_failure_correct)
		total += 1;
	if(result.is_success_correct)
		total += 1;

	assert(total <= 14.0);
	return total / 14.0;
}