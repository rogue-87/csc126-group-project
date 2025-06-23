// CSC126 Group Project
// Go-Kart Booking System

// IRFAN SHAH BIN MAIZUL HISHAM       (2025171523)  (RCDCS1101A) (shahxvi)
// SHAHRIN AREFF SHAH BIN SHAH RIZAL  (2025151503)  (RCDCS1101A) (rinnnnnnn17)
// MUHAMMAD BIN ABDUL AZIZ            (2025507823)  (RCDCS1101B) (Kundoo)

// SUPERVISED BY MADAM NORA YANTI BINTI CHE JAN

// READ THIS BEFORE MAKING ANY CHANGES:
// Function Prototypes are defined at the top of the code after the headings.
// Each function should be defined below the main function.
// This ensures readability and maintainability of the code.
// Please update the comment line of the prototype function.

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <ostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

// for selection menus
enum Menu
{
  RegisterDriver = 1,
  ListDrivers,
  CalculatePrice,
  Exit,
};

enum CalculateSubMenu
{
  CalculateOne = 1,
  CalculateAll,
};

// for other stuff

// what is None? and what is enum class?
// first, I want to avoid null altogether, so I decided to use this as an empty value
// second, enum class, tbh I don't know myself
// all I know is that it's basically a scoped enum
// without it you cannot redefine things like None

//
enum class Booking
{
  None,
  Solo,
  Group,
};

enum class Environment
{
  None,
  Indoors,
  Outdoors,
};

enum class Mode
{
  None,
  Circuit,
  Sprint,
  TimeTrail,
  Drag,
  Elimination,
};

enum class TrackLayout
{
  None,
  SectionNineCircuit,
  ChronoPass,
  RushlineDash,
  TorqueStrip,
  BlackrockCircuit,
};

struct Track
{
  TrackLayout trackLayout;
  Mode mode;
  Environment environment;

  Track()
  {
    this->trackLayout = TrackLayout::None;
    this->mode = Mode::None;
    this->environment = Environment::None;
  };
};

struct Driver
{
  string name;
  int age;
  bool hasLicense;
  Booking booking;
  Track track;

  // instead of using null, we'll be using default values
  // dealing with null is a pain in the butt, so avoid it whenever possible
  Driver()
  {
    this->name = "";
    this->age = 0;
    this->hasLicense = false;
    this->booking = Booking::None;
    this->track = Track();
  };

  Driver(string name, int age, bool hasLicense, Booking booking, Track track)  // probably not going to use this.
  {
    this->name = name;
    this->age = age;
    this->hasLicense = hasLicense;
    this->booking = booking;
    this->track = track;
  }

  string to_string()
  {
    return "Driver\n{name: " + this->name + ", age: " + std::to_string(this->age) +
           ", hasLicense: " + (this->hasLicense ? "yes" : "no")  // don't mind if I use ternary operator?
           + "\n}";
  };

  // why no setters?
  // cuz everything is public...
};

/// NOTE: helper functions(these are only the function signatures/heads/whatever you wanna call them)

//
int prompt(const string &msg, int max, int min);
int prompt(const string &msg, int max);
string prompt(const string &msg);
bool ask(const string &msg);

string to_string(Booking booking);
string to_string(Environment env);
string to_string(Mode mode);
string to_string(TrackLayout tl);

// if you're on windows it will call cls for clearing out the console
// otherwise, it will call clear command on linux
void clear_console();

/// NOTE: functions that need to be implemented(again, signatures/heads/whatever...)

//
Driver register_driver();

// search by index
int calculate_price_for(int index);
// search by driver name
int calculate_price_for(const string &name);
int calculate_price_all();

int main()
{
  // print a welcome message
  std::cout << "Welcome to the Go-Kart Booking System!" << std::endl;

  // we used a vector here since it's very easy to add elements to it
  // and it grows dynamically unlike a regular array
  vector<Driver> drivers = {};

  while (true)
  {
    // spit out a menu for the user
    std::cout << "1. Register Driver" << std::endl;
    std::cout << "2. List Drivers" << std::endl;
    std::cout << "3. Calculate Price" << std::endl;
    std::cout << "4. Exit System" << std::endl;

    // give user a bunch of options
    auto selection = (Menu)prompt("Select Option(1 -4)", 4);
    switch (selection)
    {
      case RegisterDriver:
      {
        drivers.push_back(register_driver());
        break;
      }
      case ListDrivers:
      {
        for (auto &driver : drivers) std::cout << driver.to_string() << std::endl;
        break;
      }
      case CalculatePrice:
      {
        std::cout << "1. Calculate Price For a Specific Driver" << std::endl;
        std::cout << "2. Calculate Total Price For All Drivers" << std::endl;
        auto selection = (CalculateSubMenu)prompt("Select Option(1 - 2)", 2);
        switch (selection)
        {
          case CalculateOne:
          {
            std::cout << "Calculating price for ..." << std::endl;
            break;
          }
          case CalculateAll:
          {
            std::cout << "Calculating price for all drivers..." << std::endl;
            break;
          }
        }
        break;
      }
      case Exit:
      {
        std::cout << "Goodbye..." << std::endl;
        std::system("sleep 3s");
        std::exit(0);
      }
    }
  }
}

// NOTE: helper function implementations/bodies/whatever you wanna call them...

// prompts user for input.(useful for selection)
// range can be set between max and min
// Read user input (int) and ensure that it is within the required range.
// btw thank you tye :3

int prompt(const string &msg, int max, int min)
{
  // Write out given string
  std::cout << msg << "\n: ";

  int input;
  std::cin >> input;

  // Check if the input is valid & between "min" and "max" (inclusive)
  while (std::cin.fail() || (max < input) || (input < min))
  {
    // Clear the error state of cin
    std::cin.clear();

    // Ignore the invalid input in the buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Please enter a number (" << min << "-" << max << "): ";
    std::cin >> input;
  }

  return input;
}

int prompt(const string &msg, int max)
{
  return prompt(msg, max, 1);
}

// only for ease of use
// I don't like typing cout then cin for strings
string prompt(const string &msg)
{
  // I don't think it's necessary to validate input
  // when it comes to strings most of the time
  std::cout << msg << "\n:";
  string input;
  std::cin >> input;

  return input;
}

bool ask(const string &msg)  // same as prompt but returns bool(preferred for yes/no type of questions)
{
  std::cout << msg << " (y/n)\n:";

  while (true)
  {
    char input;
    std::cin >> input;
    // if user tries to type extra stuff, it would just get ignored
    // ,and only the first character will be picked
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // convert that input char to lowercase
    switch (std::tolower(input))
    {
      case 'y':
        return true;
      case 'n':
        return false;
      default:
      {
        std::cerr << "please, type 'y' for yes or 'n' for no" << std::endl;
      }
    }
  }
}

void clear_console()
{
  // clang-format off
  // for clearing out the console
  #ifdef _WIN32
    std::system("cls");
  #else
    std::system("clear");
  #endif
  // clang-format on
}

string to_string(Booking booking)
{
  switch (booking)
  {
    case Booking::None:
      return "None";
    case Booking::Solo:
      return "Solo";
    case Booking::Group:
      return "Group";
  }
}

string to_string(Environment env)
{
  switch (env)
  {
    case Environment::None:
      return "None";
    case Environment::Indoors:
      return "Indoors";
    case Environment::Outdoors:
      return "Outdoors";
  }
}

string to_string(Mode mode)
{
  switch (mode)
  {
    case Mode::None:
      return "None";
    case Mode::Circuit:
      return "Circuit";
    case Mode::Sprint:
      return "Sprint";
    case Mode::TimeTrail:
      return "TimeTrail";
    case Mode::Drag:
      return "Drag";
    case Mode::Elimination:
      return "Elimination";
  }
}

string to_string(TrackLayout tl)
{
  switch (tl)
  {
    case TrackLayout::None:
      return "None";
    case TrackLayout::SectionNineCircuit:
      return "SectionNineCircuit";
    case TrackLayout::ChronoPass:
      return "ChronoPass";
    case TrackLayout::RushlineDash:
      return "RushlineDash";
    case TrackLayout::TorqueStrip:
      return "TorqueStrip";
    case TrackLayout::BlackrockCircuit:
      return "BlackrockCircuit";
  }
}

// NOTE: other functions
Driver register_driver()
{
  auto d = Driver();
  d.name = prompt("What's your name?");
  d.age = prompt("How old are you?", 120);  // I don't expect old geezers to participate in something like this
  d.booking = (Booking)prompt("Booking Type.\n1. Solo\n2. Group", 2);  // I really have no idea what to do with this

  if (d.age < 13)
  {
    std::cout << "Since the driver is under the age of 13.\b They'll be driving indoors only\nThey also don't have a "
                 "driving license";
    d.hasLicense = false;
    d.track.environment = Environment::Indoors;
  }
  else
  {
    d.hasLicense = ask("Do you have a driving license?");
    d.track.environment = (Environment)prompt("Pick the environment:\n 1. Indoors\n2. Outdoors", 2);
  }

  // clang-format off
  d.track.trackLayout = (TrackLayout)prompt("Pick track layout;\n1. Section Nine Circuit\n2. Chrono Pass\n3. Rush Line Dash\n4. Torque Strip\n5. Blackrock Circuit", 5);
  // clang format on

  
    
  d.track.mode = (Mode)prompt("Pick Mode:\n1. Circuit\n2. Sprint\n3. Time Trail\n4. Drag\n5. Elimination", 5);
  return d;
}
