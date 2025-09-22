#include <iostream>
#include <string>
#include <limits>

// Define an enum to represent the result of reading input
enum class ReadResult {
    Success,
    Stop
};
// Function to read a line of input from the user and handle EOF
ReadResult inputRead(std::string& input) {
    std::getline(std::cin, input);

    if (std::cin.eof()) {
        return ReadResult::Stop;
    }

    return ReadResult::Success;
}
// Function to check if the input string is valid (not empty)
void checkValidString(const std::string& targetString) {
	if (targetString.empty()) {
		throw std::invalid_argument("Input empty. Please try again.");
	}
}

// Enum to represent the result of input validation
enum class InputResult {
    Success,
    Exit
};
// Function to get validated input from the user. Contains parameters for the prompt message, the input string, and the exit key
InputResult getValidatedInput(const std::string& prompt, std::string& input, const std::string& exitKey) {
	// Loop until valid input is received
    while (true) {
        // Prompt the user for input
    	std::cout << prompt;
    	// Read the input and check for exit conditions
        if (inputRead(input) == ReadResult::Stop || input == exitKey) {
            std::cout << "Exiting.";
            return InputResult::Exit;
        }
        // Validate the input string
        try {
            checkValidString(input);
            return InputResult::Success;
        // If the input is invalid, catch the exception and display the error message
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << "\n";
            continue;
        }

    }
    // If valid input is received, return success enum
    return InputResult::Success;
}

// Function to concatenate two strings, a and b, and return the combined string
std::string concatenateStrings(const std::string& a, const std::string& b) {
    std::string combinedString = a + b;
    return combinedString;
}

int main(int argc, char **argv) {
	// Variables to hold the two input strings and the exit key
	std::string firstString;
	std::string secondString;
	const std::string exitKey = "5";
	// GIve the user instructions
	std::cout << "Enter two strings to concatenate or press 5 to exit:" << "\n";
	// Get the two strings from the user, validating input and checking for exit conditions
	if (getValidatedInput("First string: ", firstString, exitKey) == InputResult::Exit) {
        return 0;
    }

	if (getValidatedInput("Second string: ", secondString, exitKey) == InputResult::Exit) {
        return 0;
    }
	// Concatenate the strings and display the result
	std::cout << "\nThe concatenated string is: \n";
	std::cout << '\n' << concatenateStrings(firstString, secondString) << '\n';
	std::cout << "\nProgram completed. Exiting.";
	return 0;
}
