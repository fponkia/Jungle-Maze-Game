//
//  TestWorld6.cpp
//
//  A test program for the World module.
//
//  This program was based on TestWorld4.cpp.  It has been
//    adapted to load the jungle world and test the new
//    functions.
//
//  This program is to be used with Assignment 6: Part C for
//    CS115, 202210.
//
//
//  2022-04-08: Corrected NODE_COUNT_CORRECT to have value 20
//

#include "World.h"
#include "World.h" // repeated to test for #include errors

#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo> // for typeid
#include <vector>

#include "TestHelper.h"

#include "Location.h"

using namespace std;

int main();

bool operator!=(const Location &location1, const Location &location2);
bool testGetStartNode(const World &world, const Location &desired);
bool testMessagePrint(const string &printed, const string &correct);
bool testCopiedCorrectly(const World &world, bool is_blizzard);

const int COMPILE_AND_START_MARKS = 5;
const int DID_NOT_CRASH_RUNNING_MARKS = 7;
const int COMPILE_AND_NOT_CRASH_MARKS =
    COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS = 18;
const int TOTAL_MARKS = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

const unsigned int MAX_NODE_COUNT_CORRECT = 1000;
const unsigned int MAX_DESCRIPTION_COUNT_CORRECT = 1000;
const unsigned int START_MESSAGE_CORRECT = 1;
const unsigned int END_MESSAGE_CORRECT = 2;
const Location NO_SUCH_VALUE_CORRECT(-1);

const int NODE_COUNT_CORRECT = 20;

const Location LOCATION_DEATH(7); // one of several
const Location LOCATION_START(1);
const Location LOCATION_VICTORY(16);

const unsigned int TEST_LOCATION_COUNT = 5;
const unsigned int TEST_LOCATION_DEATH_INDEX = 1;
const unsigned int TEST_LOCATION_VICTORY_INDEX = 3;
const Location TEST_LOCATIONS[TEST_LOCATION_COUNT] = {
    Location(0), // inaccessible
    LOCATION_DEATH, LOCATION_START, LOCATION_VICTORY,
    Location(10), // ordinary node
};

const int INVALID_CHECK_BORDER = 5;
const int INVALID_START = -INVALID_CHECK_BORDER;
const int INVALID_END = NODE_COUNT_CORRECT + INVALID_CHECK_BORDER;
const int INVALID_NODE_COUNT = INVALID_CHECK_BORDER * 2;

const unsigned int TEST_DIRECTION_COUNT = 4;
const string A_DIRECTION_NAME[TEST_DIRECTION_COUNT] = {
    "north",
    "south",
    "east",
    "west",
};

// pointers to member functions (thoroughly weird)
//  -> allows them to be called in a loop using array syntax
//  -> don't do this unless you know what you're doing
//    -> if you are taking CS 115, you don't
typedef bool (World::*pCanGoDirectionMemberFunction)(const Location &) const;
const pCanGoDirectionMemberFunction
    AP_CAN_GO_DIRECTION_FUNCTION[TEST_DIRECTION_COUNT] = {
        &World::canGoNorth,
        &World::canGoSouth,
        &World::canGoEast,
        &World::canGoWest,
};
typedef Location (World::*pGetDirectionMemberFunction)(const Location &) const;
const pGetDirectionMemberFunction
    AP_GET_DIRECTION_FUNCTION[TEST_DIRECTION_COUNT] = {
        &World::getNorth,
        &World::getSouth,
        &World::getEast,
        &World::getWest,
};

const Location A_TEST_CAN_GO_INACCESSIBLE[TEST_DIRECTION_COUNT] = {
    Location(17),
    Location(4),
    Location(12),
    Location(1),
};

const Location A_TEST_CAN_GO_OPEN[TEST_DIRECTION_COUNT] = {
    Location(3),
    Location(14),
    Location(9),
    Location(2),
};

const Location A_LOCATION_AFTER_GO_OPEN[TEST_DIRECTION_COUNT] = {
    Location(6),
    Location(12),
    Location(8),
    Location(1),
};

const unsigned int TEST_DESCRIPTION_COUNT = 5;
const unsigned int A_TEST_DESCRIPTION_NUMBER[TEST_DESCRIPTION_COUNT] = {
    1, 17, 4, 6, 13,
};
const string A_TEST_DESCRIPTION_NAME[TEST_DESCRIPTION_COUNT] = {
    "Start node", "Victory node", "Inside tent", "Swampy jungle", "Steep slope",
};
const Location A_TEST_DESCRIPTION_LOCATION[TEST_DESCRIPTION_COUNT] = {
    LOCATION_START, LOCATION_VICTORY, 2, 4, 11,
};
const string A_TEST_DESCRIPTION_CORRECT[TEST_DESCRIPTION_COUNT] = {
    "You are in your campsite in the Congo Rainforest.  Your tent is\n"
    "to the east and your jeep is to the south, at the end a broken\n"
    "track through the trees.  The jungle to the north looks thin\n"
    "enough to push through.\n",

    "In time, you reach a road, then a highway, then a city.  It's\n"
    "good to be back.\n",

    "You are in your tent.  It is hot here.  The exit is to the west.\n",

    "You are in a swampy part of the jungle.  You would be able to go\n"
    "north, east, or west from here.\n",

    "You are part way up a steep slope, climbing an improvised vine\n"
    "rope.  The top of the slope is to the east and the bottom is to\n"
    "the west.\n",
};

const string INACCESSIBLE_DESCRIPTION_CORRECT = "Invalid node.\n";
const string START_MESSAGE_DESCRIPTION_CORRECT =
    "Welcome to Jungle Quest!\n"
    "You recently obtained an old treasure map in mysterious\n"
    "circumstances.  It showed the location of the Lost Jewel of\n"
    "Leopold II, evil king of the Congo Free State.  And since you\n"
    "have always wanted to be more like Indiana Jones, you have\n"
    "mounted an expedition to find it.\n";
const string END_MESSAGE_DESCRIPTION_CORRECT =
    "Thank you for playing Jungle Quest!\n";

const unsigned int TEST_OBSTRUCTED_COUNT = 7;
const unsigned int IS_OBSTRUCTED_COUNT = 4;
const Location A_TEST_OBSTRUCTED_LOCATION[TEST_OBSTRUCTED_COUNT] = {
    Location(2),  Location(4),  Location(6),  Location(8),
    Location(10), Location(12), Location(14),
};
const bool A_TEST_IS_OBSTRUCTED[TEST_OBSTRUCTED_COUNT] = {
    false, true, true, false, true, false, true,
};
const char A_TEST_REQUIRED_ITEM[TEST_OBSTRUCTED_COUNT] = {
    '\0', 'n', 'd', '\0', 'p', '\0', 'b',
};
const string A_TEST_DESCRIPTION_FAILURE[TEST_OBSTRUCTED_COUNT] = {
    "",

    "Ahead of you is a swarm of buzzing mosquitoes.  You don't want\n"
    "to get malaria and die, so you return the way you came.\n",

    "The water looks very murky, so you don't want to swim in it.\n"
    "There could be a whole school of piranhas waiting just out of\n"
    "sight!\n",

    "",

    "Suddenly an elephant crashes through the undergrowth and flares\n"
    "its ears at you.  Afraid that it is going to charge you, you\n"
    "clamber up a nearby tree.  After a while, the elephant wanders\n"
    "away and you climb back down the tree and retreat to the south.\n",

    "",

    "The tree is full of bonabos.  Several of the the large ones\n"
    "(the males?) approach you, screeching.  You quickly retreat back\n"
    "to the south.\n",
};
const string A_TEST_DESCRIPTION_SUCCESS[TEST_OBSTRUCTED_COUNT] = {
    "",

    "Ahead of you is a swarm of buzzing mosquitoes.  You pull your\n"
    "mosquito nets tightly around you.  That's sure to protect you,\n"
    "right?\n",

    "You push your dugout canoe into the water and climb in.\n",

    "",

    "Suddenly an elephant crashes through the undergrowth and flares\n"
    "its ears at you.  Then it gets a smell of your chili peppers and\n"
    "turns to wander somewhere else.\n",

    "",

    "The tree is full of bonabos.  Several of the the large ones\n"
    "(the males?) approach you, screeching.  You hurriedly toss them\n"
    "a number of you bananas, and they calm down.\n",
};

const int NODE_COUNT_BLIZZARD = 40;
const string END_MESSAGE_DESCRIPTION_BLIZZARD =
    "Thank you for playing Blizzard Valley!\n";

int main() {
  testHelperStartup("TestWorld6", COMPILE_AND_START_MARKS, TOTAL_MARKS);

  //
  //  Test constants
  //

  cout << "Testing MAX_DESCRIPTION_COUNT" << endl;
  bool correct_max_description_count =
      testHelperConstant(MAX_DESCRIPTION_COUNT, MAX_DESCRIPTION_COUNT_CORRECT,
                         "MAX_DESCRIPTION_COUNT");
  cout << endl;

  cout << "Testing NO_SUCH_VALUE" << endl;
  bool correct_no_such_value =
      testHelperConstant(NO_SUCH_VALUE, NO_SUCH_VALUE_CORRECT, "NO_SUCH_VALUE");
  cout << endl;

  //
  //  Test World type and constructor
  //

  cout << "Checking World size in bytes" << endl;
  size_t world_bytes = sizeof(World);
  size_t world_bytes_node_pointer = sizeof(Node **);
  size_t world_bytes_nodes = sizeof(Node) * MAX_NODE_COUNT_CORRECT;
  size_t world_bytes_descriptions = sizeof(string) * MAX_DESCRIPTION_COUNT;
  size_t world_bytes_correct = sizeof(unsigned int) * 6 +
                               world_bytes_node_pointer +
                               world_bytes_descriptions;
  bool correct_world_bytes = false;
  if (world_bytes < world_bytes_descriptions)
    cout << "* Incorrect: World should contain a 1D array of descriptions"
         << endl;
  else if (world_bytes >= world_bytes_nodes + world_bytes_descriptions)
    cout << "* Incorrect: World should not contain statically allocated Nodes"
         << endl;
  else if (world_bytes >= world_bytes_correct * 2)
    cout << "* Incorrect: World contains far too much data" << endl;
  else {
    cout << "* Correct" << endl;
    correct_world_bytes = true;
  }
  cout << endl;

  cout << "Loading Jungle world with constructor" << endl;
  World *p_world = new World("jungle");
  cout << "* Completed without crashing" << endl;
  cout << endl;

  bool is_all_good_so_far = correct_max_description_count &&
                            correct_no_such_value && correct_world_bytes;
  cout << "Testing World::debugPrint" << endl;
  testHelperStartCapture();
  p_world->debugPrint();
  string captured = testHelperEndCapture(false);
  if (is_all_good_so_far) {
    cout << "--------------------------------------------------------" << endl;
    cout << captured;
    // blank line printed here is not a problem
    cout << "--------------------------------------------------------" << endl;
  } else
    cout << "* Skipped output because there are other errors above" << endl;
  cout << "* Completed without crashing" << endl;
  cout << endl;

  //
  //  Test isValid function
  //

  cout << "Testing if nodes inside the world are valid" << endl;
  unsigned int valid_inside_correct = 0;
  bool is_first_invalid = true;
  for (int i = 0; i < NODE_COUNT_CORRECT; i++) {
    bool is_valid = p_world->isValid(Location(i));
    if (is_valid)
      valid_inside_correct++;
    else if (is_first_invalid) {
      cout << "* Incorrect: Node " << i << " not is valid but should be"
           << endl;
      is_first_invalid = false;
    }
  }
  if (valid_inside_correct == NODE_COUNT_CORRECT)
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Testing if nodes outside the world are invalid" << endl;
  unsigned int valid_outside_correct = 0;
  bool is_first_valid = true;
  for (int i = INVALID_START; i < INVALID_END; i++) {
    if (i >= 0 && i < NODE_COUNT_CORRECT)
      continue; // already checked above

    bool is_valid = p_world->isValid(Location(i));
    if (!is_valid)
      valid_outside_correct++;
    else if (is_first_valid) {
      cout << "* Incorrect: Node " << i << " is valid but should not be"
           << endl;
      is_first_valid = false;
    }
  }
  if (valid_outside_correct == INVALID_NODE_COUNT)
    cout << "* Correct" << endl;
  cout << endl;

  //
  //  Test single-node queries
  //

  cout << "Testing World::isDeath" << endl;
  bool is_death_correct = true;
  for (int i = 0; i < TEST_LOCATION_COUNT; i++) {
    bool should_be_death = i == TEST_LOCATION_DEATH_INDEX;
    if (p_world->isDeath(TEST_LOCATIONS[i]) != should_be_death) {
      if (is_death_correct) // first time only
      {
        if (should_be_death)
          cout << "* Incorrect: Node " << TEST_LOCATIONS[i]
               << " reported as death node, shouldn't be" << endl;
        else
          cout << "* Incorrect: Node " << TEST_LOCATIONS[i]
               << " not reported as death node, should be" << endl;
      }
      is_death_correct = false;
    }
  }
  if (is_death_correct)
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Testing World::isVictory" << endl;
  bool is_victory_correct = true;
  for (int i = 0; i < TEST_LOCATION_COUNT; i++) {
    bool should_be_victory = i == TEST_LOCATION_VICTORY_INDEX;
    if (p_world->isVictory(TEST_LOCATIONS[i]) != should_be_victory) {
      if (is_victory_correct) // first time only
      {
        if (should_be_victory)
          cout << "* Incorrect: Node " << TEST_LOCATIONS[i]
               << " reported as victory node, shouldn't be" << endl;
        else
          cout << "* Incorrect: Node " << TEST_LOCATIONS[i]
               << " not reported as victory node, should be" << endl;
      }
      is_victory_correct = false;
    }
  }
  if (is_victory_correct)
    cout << "* Correct" << endl;
  cout << endl;

  //
  //  Test direction queries and getStart
  //

  cout << "Testing World::canGoNorth, etc. functions" << endl;
  bool can_go_direction_correct[TEST_DIRECTION_COUNT];
  unsigned int can_go_direction_correct_count = 0;
  for (int i = 0; i < TEST_DIRECTION_COUNT; i++) {
    can_go_direction_correct[i] = true;

    pCanGoDirectionMemberFunction pCanGoDirection =
        AP_CAN_GO_DIRECTION_FUNCTION[i];

    bool can_go_into_inaccessible =
        (p_world->*pCanGoDirection)(A_TEST_CAN_GO_INACCESSIBLE[i]);
    if (can_go_into_inaccessible) {
      cout << "* Incorrect: Returns true for going " << A_DIRECTION_NAME[i]
           << " into INACCESSIBLE" << endl;
      can_go_direction_correct[i] = false;
    }

    bool can_go_into_open = (p_world->*pCanGoDirection)(A_TEST_CAN_GO_OPEN[i]);
    if (!can_go_into_open) {
      cout << "* Incorrect: Returns false for going " << A_DIRECTION_NAME[i]
           << " into open node" << endl;
      can_go_direction_correct[i] = false;
    }

    if (can_go_direction_correct[i] == true)
      can_go_direction_correct_count++;
  }
  if (can_go_direction_correct_count == TEST_DIRECTION_COUNT)
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Testing World::getNorth, etc. functions" << endl;
  bool get_direction_correct[TEST_DIRECTION_COUNT];
  unsigned int get_direction_correct_count = 0;
  for (int i = 0; i < TEST_DIRECTION_COUNT; i++) {
    get_direction_correct[i] = false;

    pCanGoDirectionMemberFunction pCanGoDirection =
        AP_CAN_GO_DIRECTION_FUNCTION[i];
    pGetDirectionMemberFunction pGetDirection = AP_GET_DIRECTION_FUNCTION[i];

    bool can_go_into_open = (p_world->*pCanGoDirection)(A_TEST_CAN_GO_OPEN[i]);
    if (can_go_into_open) {
      Location after_move = (p_world->*pGetDirection)(A_TEST_CAN_GO_OPEN[i]);

      if (after_move == A_LOCATION_AFTER_GO_OPEN[i]) {
        get_direction_correct[i] = true;
        get_direction_correct_count++;
      } else
        cout << "* Incorrect: Going " << A_DIRECTION_NAME[i]
             << " into open node goes to wrong position" << endl;
    } else
      cout << "* Skipped: Cannot test going " << A_DIRECTION_NAME[i]
           << " into open node because cannot go that way" << endl;
  }
  if (get_direction_correct_count == TEST_DIRECTION_COUNT)
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Testing getStart" << endl;
  bool correct_get_start = testGetStartNode(*p_world, LOCATION_START);
  cout << endl;

  //
  //  Testing printing messages
  //

  cout << "Testing World::printStartMessage" << endl;
  cout << "--------------------------------------------------------" << endl;
  testHelperStartCapture();
  p_world->printStartMessage();
  string start_message_captured = testHelperEndCapture();
  cout << "--------------------------------------------------------" << endl;
  bool print_start_message_correct = testMessagePrint(
      start_message_captured, START_MESSAGE_DESCRIPTION_CORRECT);
  cout << endl;

  cout << "Testing World::printEndMessage" << endl;
  cout << "--------------------------------------------------------" << endl;
  testHelperStartCapture();
  p_world->printEndMessage();
  string end_message_captured = testHelperEndCapture();
  cout << "--------------------------------------------------------" << endl;
  bool print_end_message_correct =
      testMessagePrint(end_message_captured, END_MESSAGE_DESCRIPTION_CORRECT);
  cout << endl;

  unsigned int print_description_correct = 0;
  for (unsigned int i = 0; i < TEST_DESCRIPTION_COUNT; i++) {
    cout << "Testing message " << A_TEST_DESCRIPTION_NUMBER[i] << " ("
         << A_TEST_DESCRIPTION_NAME[i] << ")" << endl;
    cout << "--------------------------------------------------------" << endl;
    testHelperStartCapture();
    p_world->printDescription(A_TEST_DESCRIPTION_LOCATION[i]);
    string captured = testHelperEndCapture();
    cout << "--------------------------------------------------------" << endl;
    bool is_correct = testMessagePrint(captured, A_TEST_DESCRIPTION_CORRECT[i]);
    if (is_correct)
      print_description_correct++;
    cout << endl;
  }

  //
  //  Testing obstructed nodes
  //

  cout << "Testing isObstructed" << endl;
  unsigned int correct_is_obstructed = 0;
  for (unsigned int i = 0; i < TEST_OBSTRUCTED_COUNT; i++) {
    bool is_obstructed = p_world->isObstructed(A_TEST_OBSTRUCTED_LOCATION[i]);

    if (is_obstructed == A_TEST_IS_OBSTRUCTED[i])
      correct_is_obstructed++;
    else if (correct_is_obstructed == i) // first time only
    {
      if (is_obstructed)
        cout << "* Incorrect: Location " << A_TEST_OBSTRUCTED_LOCATION[i]
             << " shouldn't be obstructed but is" << endl;
      else
        cout << "* Incorrect: Location " << A_TEST_OBSTRUCTED_LOCATION[i]
             << " should be obstructed but isn't" << endl;
    }
  }
  if (correct_is_obstructed == TEST_OBSTRUCTED_COUNT)
    cout << "* Correct" << endl;
  else if (correct_is_obstructed + 1 < TEST_OBSTRUCTED_COUNT)
    cout << "* " << (TEST_OBSTRUCTED_COUNT - correct_is_obstructed - 1)
         << " more incorrect" << endl;
  cout << endl;

  cout << "Testing getRequiredItem" << endl;
  unsigned int correct_get_required = 0;
  for (unsigned int i = 0; i < TEST_OBSTRUCTED_COUNT; i++) {
    bool is_obstructed = p_world->isObstructed(A_TEST_OBSTRUCTED_LOCATION[i]);
    if (!A_TEST_IS_OBSTRUCTED[i])
      continue;
    if (!is_obstructed) {
      cout << "* Skipped " << A_TEST_OBSTRUCTED_LOCATION[i]
           << ": isObstructed returns false" << endl;
      continue;
    }

    char required_item =
        p_world->getRequiredItem(A_TEST_OBSTRUCTED_LOCATION[i]);
    if (required_item == A_TEST_REQUIRED_ITEM[i])
      correct_get_required++;
    else
      cout << "* Incorrect: Location " << A_TEST_OBSTRUCTED_LOCATION[i]
           << " should require item '" << A_TEST_REQUIRED_ITEM[i] << "'"
           << endl;
  }
  if (correct_get_required == IS_OBSTRUCTED_COUNT)
    cout << "* Correct" << endl;
  cout << endl;

  unsigned int correct_get_failure = 0;
  for (unsigned int i = 0; i < TEST_OBSTRUCTED_COUNT; i++) {
    bool is_obstructed = p_world->isObstructed(A_TEST_OBSTRUCTED_LOCATION[i]);
    if (!A_TEST_IS_OBSTRUCTED[i])
      continue;

    cout << "Testing printDescriptionFailure at "
         << A_TEST_OBSTRUCTED_LOCATION[i] << endl;
    if (!is_obstructed) {
      cout << "* Skipped: isObstructed returns false" << endl;
      continue;
    }

    cout << "--------------------------------------------------------" << endl;
    testHelperStartCapture();
    p_world->printDescriptionFailure(A_TEST_OBSTRUCTED_LOCATION[i]);
    string captured = testHelperEndCapture();
    cout << "--------------------------------------------------------" << endl;
    if (testMessagePrint(captured, A_TEST_DESCRIPTION_FAILURE[i]))
      correct_get_failure++;
    cout << endl;
  }

  unsigned int correct_get_success = 0;
  for (unsigned int i = 0; i < TEST_OBSTRUCTED_COUNT; i++) {
    bool is_obstructed = p_world->isObstructed(A_TEST_OBSTRUCTED_LOCATION[i]);
    if (!A_TEST_IS_OBSTRUCTED[i])
      continue;

    cout << "Testing printDescriptionSuccess at "
         << A_TEST_OBSTRUCTED_LOCATION[i] << endl;
    if (!is_obstructed) {
      cout << "* Skipped: isObstructed returns false" << endl;
      continue;
    }

    cout << "--------------------------------------------------------" << endl;
    testHelperStartCapture();
    p_world->printDescriptionSuccess(A_TEST_OBSTRUCTED_LOCATION[i]);
    string captured = testHelperEndCapture();
    cout << "--------------------------------------------------------" << endl;
    if (testMessagePrint(captured, A_TEST_DESCRIPTION_SUCCESS[i]))
      correct_get_success++;
    cout << endl;
  }

  //
  //  Testing canonical functions
  //

  cout << "Destroying original World" << endl;
  delete p_world;
  p_world = NULL;
  cout << "* Completed without crashing" << endl;
  cout << endl;

  cout << "Testing copy constructor (jungle map)" << endl;
  World *p_world_jungle = new World("jungle");
  cout << "* Loaded world to copy" << endl;
  World *p_world2 = new World(*p_world_jungle);
  cout << "* Completed copy without crashing" << endl;
  bool correct_copy1 = testCopiedCorrectly(*p_world2, false);
  cout << endl;

  cout << "Testing copy constructor (blizzard map)" << endl;
  World *p_world_blizzard = new World("blizzard");
  cout << "* Loaded world to copy" << endl;
  World *p_world3 = new World(*p_world_blizzard);
  cout << "* Completed copy without crashing" << endl;
  bool correct_copy2 = testCopiedCorrectly(*p_world3, true);
  cout << endl;

  cout << "Testing assignment operator" << endl;
  *p_world2 = *p_world_jungle;
  cout << "* Completed 1 without crashing" << endl;
  bool correct_assign1 = testCopiedCorrectly(*p_world2, false);
  *p_world3 = *p_world_blizzard;
  cout << "* Completed 2 without crashing" << endl;
  bool correct_assign2 = testCopiedCorrectly(*p_world3, true);
  *p_world2 = *p_world_blizzard;
  cout << "* Completed 3 without crashing" << endl;
  bool correct_assign3 = testCopiedCorrectly(*p_world2, true);
  *p_world3 = *p_world_jungle;
  cout << "* Completed 4 without crashing" << endl;
  bool correct_assign4 = testCopiedCorrectly(*p_world3, false);
  cout << endl;

  cout << "Testing self-assignment" << endl;
  *p_world2 = *p_world2;
  cout << "* Completed without crashing" << endl;
  bool correct_self = testCopiedCorrectly(*p_world2, true);
  cout << endl;

  cout << "Testing chained assignment" << endl;
  *p_world3 = *p_world2 = *p_world_jungle;
  cout << "* Completed without crashing" << endl;
  bool correct_chained1 = testCopiedCorrectly(*p_world2, false);
  bool correct_chained2 = testCopiedCorrectly(*p_world3, false);
  cout << endl;

  cout << "Destroying Worlds used in copying" << endl;
  delete p_world_jungle;
  delete p_world_blizzard;
  delete p_world2;
  delete p_world3;
  p_world_jungle = NULL;
  p_world_blizzard = NULL;
  p_world2 = NULL;
  p_world3 = NULL;
  cout << "* Completed without crashing" << endl;
  cout << endl;

  //
  //  Print results
  //

  unsigned int correct_constants =
      (correct_max_description_count ? 1 : 0) + (correct_no_such_value ? 1 : 0);

  double valid_inside_fraction_correct =
      (double)(valid_inside_correct) / (double)(NODE_COUNT_CORRECT);
  double valid_outside_fraction_correct =
      (double)(valid_outside_correct) / (double)(INVALID_NODE_COUNT);

  double is_obstructed_fraction_correct =
      (double)(correct_is_obstructed) / (double)(TEST_OBSTRUCTED_COUNT);

  unsigned int correct_copy_count =
      (correct_copy1 ? 1 : 0) + (correct_copy2 ? 1 : 0);

  unsigned int correct_assign_count =
      (correct_assign1 ? 1 : 0) + (correct_assign2 ? 1 : 0) +
      (correct_assign3 ? 1 : 0) + (correct_assign4 ? 1 : 0);

  unsigned int correct_chained_count =
      (correct_chained1 ? 1 : 0) + (correct_chained2 ? 1 : 0);

  testHelperPrintSummaryHeader(28, 1, DID_NOT_CRASH_RUNNING_MARKS);
  testHelperPrintSummaryLine("Constants", correct_constants, 2);
  testHelperPrintSummaryLine("World size in bytes", correct_world_bytes);
  testHelperPrintSummaryLine("World::isValid (inside)",
                             valid_inside_fraction_correct);
  testHelperPrintSummaryLine("World::isValid (outside)",
                             valid_outside_fraction_correct);
  testHelperPrintSummaryLine("World::isDeath", is_death_correct);
  testHelperPrintSummaryLine("World::isVictory", is_victory_correct);
  testHelperPrintSummaryLine("World::canGoNorth", can_go_direction_correct[0]);
  testHelperPrintSummaryLine("World::canGoSouth", can_go_direction_correct[1]);
  testHelperPrintSummaryLine("World::canGoEast", can_go_direction_correct[2]);
  testHelperPrintSummaryLine("World::canGoWest", can_go_direction_correct[3]);
  testHelperPrintSummaryLine("World::getNorth", get_direction_correct[0]);
  testHelperPrintSummaryLine("World::getSouth", get_direction_correct[1]);
  testHelperPrintSummaryLine("World::getEast", get_direction_correct[2]);
  testHelperPrintSummaryLine("World::getWest", get_direction_correct[3]);
  testHelperPrintSummaryLine("World::getStart", correct_get_start);
  testHelperPrintSummaryLine("World::printStartMessage",
                             print_start_message_correct);
  testHelperPrintSummaryLine("World::printEndMessage",
                             print_end_message_correct);
  testHelperPrintSummaryLine("World::printDescription",
                             print_description_correct, TEST_DESCRIPTION_COUNT);
  testHelperPrintSummaryLine("World::isObstructed", correct_is_obstructed,
                             TEST_OBSTRUCTED_COUNT);
  testHelperPrintSummaryLine("World::getRequiredItem", correct_get_required,
                             IS_OBSTRUCTED_COUNT);
  testHelperPrintSummaryLine("printDescriptionFailure", correct_get_failure,
                             IS_OBSTRUCTED_COUNT);
  testHelperPrintSummaryLine("printDescriptionSuccess", correct_get_success,
                             IS_OBSTRUCTED_COUNT);
  testHelperPrintSummaryLine("Copy constructor", correct_copy_count, 2);
  testHelperPrintSummaryLine("Assignment operator", correct_assign_count, 4);
  testHelperPrintSummaryLine("Self-assignment", correct_self);
  testHelperPrintSummaryLine("Chained assignment", correct_chained_count, 2);

  unsigned int mark = COMPILE_AND_NOT_CRASH_MARKS;

  if (correct_constants == 2 && correct_world_bytes)
    mark += 1;

  if (valid_inside_fraction_correct == 1.0 &&
      valid_outside_fraction_correct == 1.0)
    mark += 1;
  if (is_death_correct && is_victory_correct && correct_get_start)
    mark += 1;
  bool is_all_can_go_direction_correct = true;
  bool is_all_get_direction_correct = true;
  for (int i = 0; i < TEST_DIRECTION_COUNT; i++) {
    if (!can_go_direction_correct[i])
      is_all_can_go_direction_correct = false;
    if (!get_direction_correct[i])
      is_all_get_direction_correct = false;
  }
  if (is_all_can_go_direction_correct)
    mark += 1;
  if (is_all_get_direction_correct)
    mark += 1;

  if (print_start_message_correct && print_end_message_correct)
    mark += 1;
  if (print_description_correct == TEST_DESCRIPTION_COUNT)
    mark += 1;

  mark += (int)(is_obstructed_fraction_correct * 2.0);
  if (correct_get_required == IS_OBSTRUCTED_COUNT)
    mark += 1;
  if (correct_get_failure == IS_OBSTRUCTED_COUNT)
    mark += 1;
  if (correct_get_success == IS_OBSTRUCTED_COUNT)
    mark += 1;

  mark += correct_copy_count;
  mark += correct_assign_count / 2;
  if (correct_self)
    mark += 1;
  if (correct_chained_count == 2)
    mark += 1;

  assert(mark <= TOTAL_MARKS);
  testHelperPrintMark(mark, TOTAL_MARKS);

  testHelperWaitForEnter();
  return 0;
}

bool operator!=(const Location &location1, const Location &location2) {
  return !(location1 == location2);
}

bool testGetStartNode(const World &world, const Location &desired) {
  Location found = world.getStart();
  if (found == NO_SUCH_VALUE_CORRECT) {
    cout << "* Incorrect: Start node not found" << endl;
    return false;
  }

  if (found != desired) {
    cout << "* Incorrect: Start node reported at " << found << ", should be "
         << desired << endl;
    return false;
  }

  cout << "* Correct" << endl;
  return true;
}

bool testMessagePrint(const string &printed, const string &correct) {
  vector<string> printed_lines = testHelperSplitWithoutEmpty(printed, '\n');
  vector<string> correct_lines = testHelperSplitWithoutEmpty(correct, '\n');
  if (printed_lines.size() != correct_lines.size()) {
    cout << "* Incorrect: Printed " << printed_lines.size()
         << " lines, should be " << correct_lines.size() << endl;
    return false;
  }

  for (unsigned int i = 0; i < printed_lines.size(); i++) {
    if (printed_lines[i] != correct_lines[i]) {
      cout << "* Incorrect: Line " << i << " is:" << endl;
      cout << "    \"" << printed_lines[i] << "\"" << endl;
      cout << "  It should be:" << endl;
      cout << "    \"" << correct_lines[i] << "\"" << endl;
      return false;
    }
  }

  cout << "* Correct" << endl;
  return true;
}

bool testCopiedCorrectly(const World &world, bool is_blizzard) {
  Location last_valid_location;
  Location first_invalid_location;
  string end_message_correct;

  if (is_blizzard) {
    last_valid_location = Location(NODE_COUNT_BLIZZARD - 1);
    first_invalid_location = Location(NODE_COUNT_BLIZZARD);
    end_message_correct = END_MESSAGE_DESCRIPTION_BLIZZARD;
  } else {
    last_valid_location = Location(NODE_COUNT_CORRECT - 1);
    first_invalid_location = Location(NODE_COUNT_CORRECT);
    end_message_correct = END_MESSAGE_DESCRIPTION_CORRECT;
  }

  if (!world.isValid(last_valid_location)) {
    cout << "* Incorrect: Node " << last_valid_location << " should be valid"
         << endl;
    return false;
  }
  if (world.isValid(first_invalid_location)) {
    cout << "* Incorrect: Node " << first_invalid_location
         << " should not be valid" << endl;
    return false;
  }

  testHelperStartCapture();
  world.printEndMessage();
  string end_message_captured = testHelperEndCapture(false);
  if (end_message_captured != end_message_correct) {
    cout << "* Incorrect: End message is incorrect" << endl;
    return false;
  }

  cout << "* Correct" << endl;
  return true;
}