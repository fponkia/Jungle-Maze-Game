//
//  TestNode6.cpp
//
//  A test program for the Node module.
//
//  This program was based on TestWorld4.cpp.  It has been
//    adapted to also test the new functions.
//
//  This program is to be used with Assignment 6: Part A for
//    CS115, 202210.
//
//

#include "Node.h"
#include "Node.h"  // repeated to test for #include errors

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
                       bool correct_is_death,
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
                        unsigned int west);
PrintResult checkPrinted (const string& printed,
                          unsigned int correct_description,
                          unsigned int correct_north,
                          unsigned int correct_south,
                          unsigned int correct_east,
                          unsigned int correct_west,
                          bool correct_is_death,
                          bool is_print_correct);
char getCorrectNodeType (bool correct_is_death);
string tabsToSpaces (const string& str);
unsigned int countInString (const string& str, char search_for);
unsigned int countPrintResult (const PrintResult& result);
double scorePrintResult (const PrintResult& result);

class DerivedNode : public Node
{
public:
	static bool is_called;

	DerivedNode ()
			: Node ()
	{ }

	~DerivedNode ()
	{
		is_called = true;
	}

	void debugPrint () const
	{
		is_called = true;
		Node::debugPrint();
	}

	Node* getClone () const
	{
		is_called = true;
		return new DerivedNode(*this);
	}

	bool isObstructed () const
	{
		is_called = true;
		return Node::isObstructed();
	}

	char getRequiredItem () const
	{
		is_called = true;
		return Node::getRequiredItem();
	}

	unsigned int getDescriptionFailure () const
	{
		is_called = true;
		return 0;
	}

	unsigned int getDescriptionSuccess () const
	{
		is_called = true;
		return 0;
	}
};

bool DerivedNode :: is_called = false;
// end of class DerivedNode

const int COMPILE_AND_START_MARKS     = 2;
const int DID_NOT_CRASH_RUNNING_MARKS = 2;
const int COMPILE_AND_NOT_CRASH_MARKS = COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS         = 6;
const int TOTAL_MARKS                 = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

const char NO_REQUIRED_ITEM_CORRECT = '\0';

const unsigned int PRINT_TOKEN_COUNT_CORRECT = 6;

const unsigned int COUNT_CHECK_RESULT_MAX = 8;
const unsigned int COUNT_PRINT_RESULT_MAX = 9;

const unsigned int TEST_DESCRIPTION_DEFAULT = 0;
const unsigned int TEST_NORTH_DEFAULT       = 0;
const unsigned int TEST_SOUTH_DEFAULT       = 0;
const unsigned int TEST_EAST_DEFAULT        = 0;
const unsigned int TEST_WEST_DEFAULT        = 0;
const bool         TEST_IS_DEATH_DEFAULT    = false;
const char         TEST_NODE_TYPE_DEFAULT   = getCorrectNodeType(TEST_IS_DEATH_DEFAULT);

const unsigned int TEST_DESCRIPTION_1 = 1;
const unsigned int TEST_NORTH_1       = 2;
const unsigned int TEST_SOUTH_1       = 3;
const unsigned int TEST_EAST_1        = 4;
const unsigned int TEST_WEST_1        = 5;
const bool         TEST_IS_DEATH_1    = false;
const char         TEST_NODE_TYPE_1   = getCorrectNodeType(TEST_IS_DEATH_1);

const unsigned int TEST_DESCRIPTION_2 = 100;
const unsigned int TEST_NORTH_2       = 86;
const unsigned int TEST_SOUTH_2       = 73;
const unsigned int TEST_EAST_2        = 61;
const unsigned int TEST_WEST_2        = 50;
const bool         TEST_IS_DEATH_2    = true;
const char         TEST_NODE_TYPE_2   = getCorrectNodeType(TEST_IS_DEATH_2);

const char TEST_NODE_TYPE_DERIVED = getCorrectNodeType(false);



int main ()
{
	testHelperStartup("TestNode6", COMPILE_AND_START_MARKS, TOTAL_MARKS);

	//
	//  Test Node class
	//

	cout << "Testing NO_REQUIRED_ITEM" << endl;
	bool correct_no_required_item = testHelperConstant(NO_REQUIRED_ITEM, NO_REQUIRED_ITEM_CORRECT, "NO_REQUIRED_ITEM");
	cout << endl;

	cout << "Checking Node size in bytes" << endl;
	size_t node_bytes          = sizeof(Node);
	size_t node_bytes_correct1 = sizeof(unsigned int) * 5 + sizeof(bool);
	size_t node_bytes_correct2 = sizeof(Location)     * 5 + sizeof(bool);

	bool correct_node_bytes = false;
	if(node_bytes < node_bytes_correct1 && node_bytes < node_bytes_correct2)
		cout << "* Incorrect: Node should contain more data" << endl;
	else if(node_bytes > node_bytes_correct1 * 2 && node_bytes > node_bytes_correct2 * 2)
		cout << "* Incorrect: Node contains unnecessary data" << endl;
	else
	{
		cout << "* Correct" << endl;
		correct_node_bytes = true;
	}
	cout << endl;


	//
	//  Test default constructor
	//

	cout << "Testing default constructor" << endl;
	Node* p_node_default = new Node();
	CheckResult result_default = checkNode(*p_node_default, TEST_DESCRIPTION_DEFAULT,
	                                       TEST_NORTH_DEFAULT, TEST_SOUTH_DEFAULT, TEST_EAST_DEFAULT, TEST_WEST_DEFAULT,
	                                       TEST_IS_DEATH_DEFAULT, true);
	cout << endl;

	cout << "Testing debugPrint" << endl;
	debugPrintCorrect(TEST_NODE_TYPE_DEFAULT, TEST_DESCRIPTION_DEFAULT,
	                  TEST_NORTH_DEFAULT, TEST_SOUTH_DEFAULT, TEST_EAST_DEFAULT, TEST_WEST_DEFAULT);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_node_default->debugPrint();
	string captured = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	PrintResult print_result_default = checkPrinted(captured, TEST_DESCRIPTION_DEFAULT,
		                                            TEST_NORTH_DEFAULT, TEST_SOUTH_DEFAULT, TEST_EAST_DEFAULT, TEST_WEST_DEFAULT,
	                                                TEST_IS_DEATH_DEFAULT, true);
	cout << endl;

	cout << "Destroying Node" << endl;
	delete p_node_default;
	p_node_default = NULL;
	cout << "* Completed without crashing" << endl;
	cout << endl;


	//
	//  Test initializing constructor
	//

	cout << "Testing initializing constructor (#1)" << endl;
	Node* p_node_init1 = new Node(TEST_DESCRIPTION_1,
	                              TEST_NORTH_1, TEST_SOUTH_1, TEST_EAST_1, TEST_WEST_1,
	                              TEST_IS_DEATH_1);
	CheckResult result_init1 = checkNode(*p_node_init1, TEST_DESCRIPTION_1,
	                                     TEST_NORTH_1, TEST_SOUTH_1, TEST_EAST_1, TEST_WEST_1,
	                                     TEST_IS_DEATH_1, true);
	cout << endl;

	cout << "Testing debugPrint" << endl;
	debugPrintCorrect(TEST_NODE_TYPE_1, TEST_DESCRIPTION_1,
	                  TEST_NORTH_1, TEST_SOUTH_1, TEST_EAST_1, TEST_WEST_1);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_node_init1->debugPrint();
	string captured_init1 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	PrintResult print_result_init1 = checkPrinted(captured_init1, TEST_DESCRIPTION_1,
		                                          TEST_NORTH_1, TEST_SOUTH_1, TEST_EAST_1, TEST_WEST_1,
	                                              TEST_IS_DEATH_1, true);
	cout << endl;

	cout << "Testing initializing constructor (#2)" << endl;
	Node* p_node_init2 = new Node(TEST_DESCRIPTION_2,
	                              TEST_NORTH_2, TEST_SOUTH_2, TEST_EAST_2, TEST_WEST_2,
	                              TEST_IS_DEATH_2);
	CheckResult result_init2 = checkNode(*p_node_init2, TEST_DESCRIPTION_2,
	                                     TEST_NORTH_2, TEST_SOUTH_2, TEST_EAST_2, TEST_WEST_2,
	                                     TEST_IS_DEATH_2, true);
	cout << endl;

	cout << "Testing debugPrint" << endl;
	debugPrintCorrect(TEST_NODE_TYPE_2, TEST_DESCRIPTION_2,
	                  TEST_NORTH_2, TEST_SOUTH_2, TEST_EAST_2, TEST_WEST_2);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_node_init2->debugPrint();
	string captured_init2 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	PrintResult print_result_init2 = checkPrinted(captured_init2, TEST_DESCRIPTION_2,
		                                          TEST_NORTH_2, TEST_SOUTH_2, TEST_EAST_2, TEST_WEST_2,
	                                              TEST_IS_DEATH_2, true);
	cout << endl;


	//
	//  Test copy constructor, assignment operator
	//

	cout << "Testing copying default Node" << endl;
	Node* p_node_copy1 = new Node(Node());
	CheckResult result_copy1 = checkNode(*p_node_copy1, TEST_DESCRIPTION_DEFAULT,
	                                     TEST_NORTH_DEFAULT, TEST_SOUTH_DEFAULT, TEST_EAST_DEFAULT, TEST_WEST_DEFAULT,
	                                     TEST_IS_DEATH_DEFAULT, true);
	cout << endl;

	cout << "Testing copying inited Node" << endl;
	Node* p_node_copy2 = new Node(*p_node_init1);
	CheckResult result_copy2 = checkNode(*p_node_copy2, TEST_DESCRIPTION_1,
	                                     TEST_NORTH_1, TEST_SOUTH_1, TEST_EAST_1, TEST_WEST_1,
	                                     TEST_IS_DEATH_1, true);
	cout << endl;

	cout << "Testing assigning default to default" << endl;
	*p_node_copy1 = Node();
	CheckResult result_assign1 = checkNode(*p_node_copy1, TEST_DESCRIPTION_DEFAULT,
	                                       TEST_NORTH_DEFAULT, TEST_SOUTH_DEFAULT, TEST_EAST_DEFAULT, TEST_WEST_DEFAULT,
	                                       TEST_IS_DEATH_DEFAULT, true);
	cout << endl;

	cout << "Testing assigning default to inited" << endl;
	*p_node_copy1 = *p_node_init1;
	CheckResult result_assign2 = checkNode(*p_node_copy1, TEST_DESCRIPTION_1,
	                                       TEST_NORTH_1, TEST_SOUTH_1, TEST_EAST_1, TEST_WEST_1,
	                                       TEST_IS_DEATH_1, true);
	cout << endl;

	cout << "Testing assigning inited to default" << endl;
	*p_node_copy2 = Node();
	CheckResult result_assign3 = checkNode(*p_node_copy2, TEST_DESCRIPTION_DEFAULT,
	                                       TEST_NORTH_DEFAULT, TEST_SOUTH_DEFAULT, TEST_EAST_DEFAULT, TEST_WEST_DEFAULT,
	                                       TEST_IS_DEATH_DEFAULT, true);
	cout << endl;

	cout << "Testing assigning inited to inited" << endl;
	*p_node_copy1 = *p_node_init2;
	CheckResult result_assign4 = checkNode(*p_node_copy1, TEST_DESCRIPTION_2,
	                                       TEST_NORTH_2, TEST_SOUTH_2, TEST_EAST_2, TEST_WEST_2,
	                                       TEST_IS_DEATH_2, true);
	cout << endl;

	cout << "Testing self-assignment" << endl;
	*p_node_copy1 = *p_node_copy1;
	CheckResult result_self = checkNode(*p_node_copy1, TEST_DESCRIPTION_2,
	                                    TEST_NORTH_2, TEST_SOUTH_2, TEST_EAST_2, TEST_WEST_2,
	                                    TEST_IS_DEATH_2, true);
	cout << endl;

	cout << "Testing chained assignment" << endl;
	*p_node_copy1 = *p_node_copy2 = Node();
	CheckResult result_chained1 = checkNode(*p_node_copy1, TEST_DESCRIPTION_DEFAULT,
	                                        TEST_NORTH_DEFAULT, TEST_SOUTH_DEFAULT, TEST_EAST_DEFAULT, TEST_WEST_DEFAULT,
	                                        TEST_IS_DEATH_DEFAULT, false);
	CheckResult result_chained2 = checkNode(*p_node_copy2, TEST_DESCRIPTION_DEFAULT,
	                                        TEST_NORTH_DEFAULT, TEST_SOUTH_DEFAULT, TEST_EAST_DEFAULT, TEST_WEST_DEFAULT,
	                                        TEST_IS_DEATH_DEFAULT, false);
	if(countCheckResult(result_chained1) == COUNT_CHECK_RESULT_MAX &&
	   countCheckResult(result_chained2) == COUNT_CHECK_RESULT_MAX)
	{
		cout << "* Correct" << endl;
	}
	cout << endl;

	cout << "Destroying Nodes" << endl;
	delete p_node_init1;
	delete p_node_init2;
	delete p_node_copy1;
	delete p_node_copy2;
	p_node_init1 = NULL;
	p_node_init2 = NULL;
	p_node_copy1 = NULL;
	p_node_copy2 = NULL;
	cout << "* Completed without crashing" << endl;
	cout << endl;


	//
	//  Test virtual functions
	//

	cout << "Creating subclass object" << endl;
	DerivedNode* p_derived1 = new DerivedNode();
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << "Testing derived subclass" << endl;
	DerivedNode::is_called = false;
	CheckResult result_derived1 = checkNode(*p_derived1, TEST_DESCRIPTION_DEFAULT,
	                                        TEST_NORTH_DEFAULT, TEST_SOUTH_DEFAULT, TEST_EAST_DEFAULT, TEST_WEST_DEFAULT,
	                                        TEST_IS_DEATH_DEFAULT, false);
	unsigned int correct_virtual = 0;
	if(countCheckResult(result_derived1) == COUNT_CHECK_RESULT_MAX)
	{
		if(!DerivedNode::is_called)
			cout << "* Incorrect: isObstructed needs to be virtual" << endl;
		else
		{
			correct_virtual++;
			cout << "* Correct" << endl;
		}
	}
	cout << endl;

	cout << "Testing debugPrint directly and with superclass pointer" << endl;
	Node* p_superclass = p_derived1;
	debugPrintCorrect(TEST_NODE_TYPE_DERIVED, TEST_DESCRIPTION_DEFAULT,
	                  TEST_NORTH_DEFAULT, TEST_SOUTH_DEFAULT, TEST_EAST_DEFAULT, TEST_WEST_DEFAULT);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_derived1->debugPrint();
	string captured_open1 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	DerivedNode::is_called = false;
	p_superclass->debugPrint();
	string captured_open2 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	PrintResult print_result_open1 = checkPrinted(captured_open1, TEST_DESCRIPTION_DEFAULT,
		                                          TEST_NORTH_DEFAULT, TEST_SOUTH_DEFAULT, TEST_EAST_DEFAULT, TEST_WEST_DEFAULT,
	                                              TEST_IS_DEATH_DEFAULT, false);
	PrintResult print_result_open2;
	print_result_open2.is_anything = false;
	if(countPrintResult(print_result_open1) == COUNT_PRINT_RESULT_MAX)
	{
		if(!DerivedNode::is_called)
			cout << "* Incorrect: debugPrint needs to be virtual" << endl;
		else
		{
			print_result_open2 = checkPrinted(captured_open2, TEST_DESCRIPTION_DEFAULT,
				                              TEST_NORTH_DEFAULT, TEST_SOUTH_DEFAULT, TEST_EAST_DEFAULT, TEST_WEST_DEFAULT,
			                                  TEST_IS_DEATH_DEFAULT, true);
			correct_virtual++;
		}
	}
	cout << endl;

	cout << "Testing getClone" << endl;
	DerivedNode::is_called = false;
	Node* p_clone = p_superclass->getClone();
	if(p_clone == NULL || p_clone == p_superclass)
		cout << "* Incorrect: getClone should return a dynamically-allocated copy" << endl;
	else if(!DerivedNode::is_called)
		cout << "* Incorrect: getClone needs to be virtual" << endl;
	else
	{
		assert(dynamic_cast<DerivedNode*>(p_clone) != NULL);
		correct_virtual++;
		cout << "* Correct" << endl;
	}
	cout << endl;

	cout << "Testing if getRequiredItem is virtual" << endl;
	DerivedNode::is_called = false;
	char derived_required = p_superclass->getRequiredItem();
	if(!DerivedNode::is_called)
		cout << "* Incorrect: getRequiredItem needs to be declared virtual" << endl;
	else
	{
		correct_virtual++;
		cout << "* Correct" << endl;
	}
	cout << endl;

	cout << "Testing if getDescriptionFailure is virtual" << endl;
	DerivedNode::is_called = false;
	unsigned int derived_failure = p_superclass->getDescriptionFailure();
	if(!DerivedNode::is_called)
		cout << "* Incorrect: getDescriptionFailure needs to be declared virtual" << endl;
	else
	{
		correct_virtual++;
		cout << "* Correct" << endl;
	}
	cout << endl;

	cout << "Testing if getDescriptionSuccess is virtual" << endl;
	DerivedNode::is_called;
	unsigned int derived_success = p_superclass->getDescriptionSuccess();
	if(!DerivedNode::is_called)
		cout << "* Incorrect: getDescriptionSuccess needs to be declared virtual" << endl;
	else
	{
		correct_virtual++;
		cout << "* Correct" << endl;
	}
	cout << endl;

	cout << "Destroying subclass Node directly" << endl;
	if(p_clone == NULL)
		cout << "* Skipping: getClone returned NULL above" << endl;
	else
	{
		DerivedNode::is_called = false;
		delete p_clone;
		p_clone = NULL;
		cout << "* Completed without crashing" << endl;
		if(!DerivedNode::is_called)
			cout << "* Incorrect: Destructor needs to be virtual" << endl;
		else
			cout << "* Correct" << endl;
	}
	assert(p_clone == NULL);
	cout << endl;

	cout << "Destroying subclass Node via superclass pointer" << endl;
	assert(p_superclass != NULL);
	DerivedNode::is_called = false;
	delete p_superclass;
	p_derived1   = NULL;
	p_superclass = NULL;
	cout << "* Completed without crashing" << endl;
	if(!DerivedNode::is_called)
		cout << "* Incorrect: Destructor needs to be virtual" << endl;
	else
	{
		correct_virtual++;
		cout << "* Correct" << endl;
	}
	cout << endl;


	//
	//  Print results
	//

	unsigned int default_result_count = countCheckResult(result_default);
	unsigned int init_result_count    = countCheckResult(result_init1) +
	                                    countCheckResult(result_init2);

	unsigned int construct_print_count = countPrintResult(print_result_default) +
	                                     countPrintResult(print_result_init1) +
	                                     countPrintResult(print_result_init2);

	unsigned int copy_result_count    = countCheckResult(result_copy1) +
	                                    countCheckResult(result_copy2);
	unsigned int assign_result_count  = countCheckResult(result_assign1) +
	                                    countCheckResult(result_assign2) +
	                                    countCheckResult(result_assign3) +
	                                    countCheckResult(result_assign4);
	unsigned int self_result_count    = countCheckResult(result_self);
	unsigned int chained_result_count = countCheckResult(result_chained1) +
	                                    countCheckResult(result_chained2);

	CheckResult result_combined = result_default;
	result_combined = combine(result_combined, result_init1);
	result_combined = combine(result_combined, result_init2);
	result_combined = combine(result_combined, result_copy1);
	result_combined = combine(result_combined, result_copy2);
	result_combined = combine(result_combined, result_assign1);
	result_combined = combine(result_combined, result_assign2);
	result_combined = combine(result_combined, result_assign3);
	result_combined = combine(result_combined, result_assign4);
	result_combined = combine(result_combined, result_self);
	result_combined = combine(result_combined, result_chained1);
	result_combined = combine(result_combined, result_chained2);

	unsigned int derived_result_count = countCheckResult(result_derived1);
	unsigned int derived_print_count  = countPrintResult(print_result_open1) +
	                                    countPrintResult(print_result_open2);

	double correct_virtual_fraction = correct_virtual / 7.0;

	testHelperPrintSummaryHeader(24, 2, DID_NOT_CRASH_RUNNING_MARKS);
	testHelperPrintSummaryLine("NO_REQUIRED_ITEM",      correct_no_required_item);
	testHelperPrintSummaryLine("Node declaration",      correct_node_bytes);
	testHelperPrintSummaryLine("Default constructor",   default_result_count,  COUNT_CHECK_RESULT_MAX);
	testHelperPrintSummaryLine("Init. constructor",     init_result_count,     COUNT_CHECK_RESULT_MAX * 2);
	testHelperPrintSummaryLine("debugPrint",            construct_print_count, COUNT_PRINT_RESULT_MAX * 3);
	testHelperPrintSummaryLine("Copy constructor",      copy_result_count,     COUNT_CHECK_RESULT_MAX * 2);
	testHelperPrintSummaryLine("Assignment operator",   assign_result_count,   COUNT_CHECK_RESULT_MAX * 4);
	testHelperPrintSummaryLine("Self-assignment",       self_result_count,     COUNT_CHECK_RESULT_MAX);
	testHelperPrintSummaryLine("Chained assignment",    chained_result_count,  COUNT_CHECK_RESULT_MAX * 2);
	testHelperPrintSummaryLine("Unobstructed subclass", derived_result_count,  COUNT_CHECK_RESULT_MAX);
	testHelperPrintSummaryLine("Unobstructed print",    derived_print_count,   COUNT_PRINT_RESULT_MAX * 2);
	testHelperPrintSummaryLine("Virtual functions",     correct_virtual,       7);

	unsigned int mark = COMPILE_AND_NOT_CRASH_MARKS;

	if(correct_no_required_item &&
	   correct_node_bytes &&
	   construct_print_count == COUNT_PRINT_RESULT_MAX * 3)
	{
		mark += 1;
	}
	mark += (int)(scoreCheckResult(result_combined) * 4.0);
	// skipping results from derived pointers
	if(correct_virtual_fraction == 1.0)
		mark += 1;

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
                       bool correct_is_death,
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

	result.is_description_correct = description   == correct_description;
	result.is_north_correct       = north         == correct_north;
	result.is_south_correct       = south         == correct_south;
	result.is_east_correct        = east          == correct_east;
	result.is_west_correct        = west          == correct_west;
	result.is_death_correct       = is_death      == correct_is_death;
	result.is_obstructed_correct  = is_obstructed == false;
	result.is_required_correct    = required_item == NO_REQUIRED_ITEM_CORRECT;

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
		cout << "* Incorrect: This node is obstructed but it shouldn't be" << endl;
	else if(!result.is_required_correct)
		cout << "* Incorrect: This node has required item '" << required_item << "', but should have none" << endl;
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
		total += 2;
	if(result.is_required_correct)
		total += 2;
	assert(total <= 12.0);
	return total / 12.0;
}



void debugPrintCorrect (char node_type,
                        unsigned int description,
                        unsigned int north,
                        unsigned int south,
                        unsigned int east,
                        unsigned int west)
{
	cout << node_type << "\t"
	     << description << "\t"
	     << north << "\t"
	     << south << "\t"
	     << east << "\t"
	     << west << "  // correct" << endl;
}

PrintResult checkPrinted (const string& printed,
                          unsigned int correct_description,
                          unsigned int correct_north,
                          unsigned int correct_south,
                          unsigned int correct_east,
                          unsigned int correct_west,
                          bool correct_is_death,
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
		char correct_node_type = getCorrectNodeType(correct_is_death);
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

	//  Check if all correct
	
	if(countPrintResult(result) == COUNT_PRINT_RESULT_MAX && is_print_correct)
		cout << "* Correct" << endl;

	return result;
}

char getCorrectNodeType (bool correct_is_death)
{
	if(correct_is_death)
		return 'D';
	else
		return 'N';
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

	assert(total <= 10.0);
	return total / 10.0;
}