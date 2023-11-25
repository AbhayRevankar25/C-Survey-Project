#include <iostream>
#include <limits>

class Welcome {
public:
    static void greetUser() {
        std::cout << "Welcome to the Survey Management System!" << std::endl;
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "1. Create a new survey" << std::endl;
        std::cout << "2. Answer a survey" << std::endl;
        std::cout << "3. Exit" << std::endl;
    }

    static int getUserChoice() {
        int choice;

        while (true) {
            std::cout << "Enter your choice: ";

            try {
                std::cin >> choice;

                if (std::cin.fail()) {
                    throw std::invalid_argument("Invalid input. Please enter a number.");
                }

                if (choice < 1 || choice > 3) {
                    throw std::out_of_range("Invalid choice!!!");
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                break;
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        return choice;
    }
};