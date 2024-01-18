// # Program name: squarethethird.cpp v1.03
// # Author: Bruce Nebergall
// # Date last updated: 1/16/2024
// # Purpose: To collect and store dimensions and colors of a cube, and display them alongside calculated volume. Allows for change of values after initial input.

#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <sstream>

// Prototypes
void QuickClear();
int GetUserSelection(const std::string& menuText, int minOption, int maxOption);
int DisplayMenu();
int PropertySelect();
bool ValidateInteger(int& value);
bool ValidateString(std::string& input);

class Cube {
public:
    // constructor using PropertySet method
    Cube() {
        PropertySet();
    }
    // accessor methods - declare colWidth here to use methods to output in easily readible table
    int colWidth = 10;
    void getLength() {std::cout << std::setw(colWidth) << length;}
    void getWidth()  {std::cout << std::setw(colWidth) << width;}    
    void getHeight() {std::cout << std::setw(colWidth) << height;}
    void getColor()  {std::cout << std::setw(colWidth) << color << std::endl;}

    // mutator methods
    void setLength() {std::cout << "Enter cube length: "; ValidateInteger(length); }
    void setWidth()  {std::cout << "Enter cube width: ";  ValidateInteger(width); }    
    void setHeight() {std::cout << "Enter cube height: "; ValidateInteger(height); }
    void setColor()  {std::cout << "Enter cube color: "; 
        while (!ValidateString(color)) {}
    }
    
    // Combined function to alter properties with mutator methods
    void PropertySet() {
        setLength();setWidth();setHeight();setColor(); 
    }

    // Calculates the volume with present present cube data at time of display
    void CalculateVolume() {
        double volume = length * width * height;
        std::cout << "\nThe Volume of the " + color + " cube is " << volume << " units^3\n"; 
    }

    // Displays Properties of Current Cube
    void DisplayProperties() {
        std::cout << "\nYour current cube...\n";
        // Header
        std::cout << std::left << std::setw(colWidth) << "Property";
        std::cout << std::setw(colWidth) << "Length";
        std::cout << std::setw(colWidth) << "Width";
        std::cout << std::setw(colWidth) << "Height";
        std::cout << std::setw(colWidth) << "Color" << std::endl;
        // Values
        std::cout << std::setw(colWidth) << "Value";
        getLength();
        getWidth();
        getHeight();
        getColor();
        // Volume Calculation
        CalculateVolume();
        
    }
    // switch for property change selection to invoke appropriate mutator function    
    void PropertyChanger(int x) {
        switch (x){
        case 1:
            setLength();
            break;
        case 2:
            setWidth();
            break;
        case 3:
            setHeight();
            break;
        case 4:
            setColor();
            break;
        default:
            break;
        }
    }
private:
    int length;
    int width;
    int height;
    std::string color;
};

// program start
int main() {
    int menuChoice = 0;
    int changeChoice;

    // initial prompt and create original cube
    std::cout << "Welcome to Square III\nEnter the properties of your cube to begin\n\n";
    Cube activeCube;
    activeCube.DisplayProperties();
    
    // main program loop
    while (menuChoice != 3){
    menuChoice = DisplayMenu();
    switch (menuChoice){
    case 1:  // Change Property
        changeChoice = PropertySelect();
        activeCube.PropertyChanger(changeChoice);
        activeCube.DisplayProperties();
        break;
    case 2:  // Restart Cube
        std::cout << "\nYour cube has been eliminated.\nEnter the properties of your new cube.\n";
        activeCube.PropertySet();
        activeCube.DisplayProperties();
        break;
    default: // End Program
        std::cout << "Program Complete.\nThanks for using Square III" << std::endl;
        std::string confirm; std::getline(std::cin, confirm);
        return 0;
        break;
        } 
    }   
}


void QuickClear() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Function for prompting user for and validating menu navigation options.
int GetUserSelection(const std::string& menuText, int minOption, int maxOption) {
    int selection;
    do {
        std::cout << menuText;
        std::cin >> selection;
        if (std::cin.fail() || selection < minOption || selection > maxOption) {
            std::cout << "Invalid Selection. Please enter an Integer between " << minOption << " and " << maxOption << ".\n";
            QuickClear();
        } else {
            QuickClear();  // Clear the stream to remove any leftover characters, especially newline
            return selection;  // Valid input
        }
    } while (true);
}

// Perameters for main program menu
int DisplayMenu() {
    std::string menuText = "\nWhat would you like to do next?"
                           "\n1 - Change a Property"
                           "\n2 - Start Over"
                           "\n3 - Quit Program\n";
    return GetUserSelection(menuText, 1, 3);  // Menu with options 1 to 3
}

// Perameters for property change menu
int PropertySelect() {
    std::string propertyMenuText = "\nWhat would you like to change"
                                   "\n1 - Length"
                                   "\n2 - Width"
                                   "\n3 - Height"
                                   "\n4 - Color\n";
    return GetUserSelection(propertyMenuText, 1, 4);  // Menu with options 1 to 4
}

// Function for Integer Validation
bool ValidateInteger(int& value) {
    std::string input;
    while (true) {
        std::getline(std::cin, input);
        std::stringstream input_stream(input);

        // Check if the input can be converted to an integer and nothing else follows it (was having an issue when doubles were entered)
        if (input_stream >> value && input_stream.eof()) {
            if (value >= 0) {  // Check for non-negative value
                return true;  
            } else {
                std::cout << "Invalid input. Please enter a non-negative integer: ";
            }
        } else {
            std::cout << "Invalid input. Please enter an integer: ";
        }
    }
}

// Function for String Validation
bool ValidateString(std::string& input) {
    getline(std::cin, input);
    if (input.empty()) {
        std::cout << "Input cannot be empty. Please enter a value: ";
        return false;
    }
    return true;
}
