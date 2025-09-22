#include <iostream>
#include <string>
#include <limits>

std::string concatenateStrings(const std::string& a, const std::string& b) {
    std::string combinedString = a + b;
    return combinedString;
}

enum class ReadResult {
    Success,
    Stop
};

ReadResult promptRead(const std::string& prompt, std::string& input, bool needsNewline) {
    if (needsNewline) std::cout << std::endl;
    std::cout << prompt;
    std::getline(std::cin, input);
    if (std::cin.eof()) {
        return ReadResult::Stop;
    }
    return ReadResult::Success;
}

void checkValidString(const std::string& targetString) {
	if (targetString.empty()) {
		throw std::invalid_argument("Input empty. Please try again.");
	}
}

// Helper function to get validated input with error handling and formatting
enum class InputResult {
    Success,
    Exit
};

InputResult getValidatedInput(const std::string& prompt, std::string& input, const std::string& exitKey) {
    bool showPrompt = true;
    while (true) {
        if (showPrompt) {
            std::cout << prompt;
            std::cout << std::flush;
        }
        if (promptRead(input) == ReadResult::Stop || input == exitKey) {
            std::cout << "Exiting.";
            return InputResult::Exit;
        }
        try {
            checkValidString(input);
            return InputResult::Success;
        } catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            std::cerr << std::flush;
            showPrompt = true;
            continue;
        }
        showPrompt = false;
    }
}

int main(int argc, char **argv) {

	std::string firstString;
	std::string secondString;
	const std::string exitKey = "5";

	std::cout << "Enter two strings to concatenate or press 5 to exit:" << std::endl;

	if (getValidatedInput("First string: ", firstString, exitKey) == InputResult::Exit) {
        return 0;
    }
	if (getValidatedInput("Second string: ", secondString, exitKey) == InputResult::Exit) {
        return 0;
    }

	std::cout << '\n' << concatenateStrings(firstString, secondString) << '\n';
	std::cout << "Exiting.";
	return 0;
}