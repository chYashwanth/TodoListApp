#include <iostream>
#include <vector>
#include <stdexcept>
#include "Task.h"
#include "TaskManager.h"
#include "Logger.h"

int main() {
    Logger& logger = Logger::getInstance();
    logger.setMinLogLevel(LogLevel::INFO);  // Change to WARNING to suppress info logs

    std::vector<Task> tasks;

    try {
        loadTasks(tasks, "tasks.txt");

        while (true) {
            std::cout << "\n1. Add\n2. List\n3. Done\n4. Delete\n5. Save & Exit\nChoice: ";
            int choice;
            std::cin >> choice;

            if (std::cin.fail()) {
                logger.log("Invalid input type detected", LogLevel::ERROR);
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            if (choice == 1) {
                std::string desc;
                std::cin.ignore();
                std::getline(std::cin, desc);
                addTask(tasks, desc);
            }
            else if (choice == 2) {
                listTasks(tasks);
            }
            else if (choice == 3) {
                int id;
                std::cin >> id;
                markTaskDone(tasks, id);
            }
            else if (choice == 4) {
                int id;
                std::cin >> id;
                deleteTask(tasks, id);
            }
            else if (choice == 5) {
                saveTasks(tasks, "tasks.txt");
                logger.log("User exited the application.", LogLevel::INFO);
                break;
            }
            else {
                logger.log("Invalid menu choice: " + std::to_string(choice), LogLevel::WARNING);
            }
        }
    }
    catch (const std::exception& e) {
        logger.log("Unhandled exception in main: " + std::string(e.what()), LogLevel::ERROR);
        return 1; // Indicate failure
    }
    catch (...) {
        logger.log("Unknown fatal error occurred in main.", LogLevel::ERROR);
        return 2;
    }

    return 0;
}
