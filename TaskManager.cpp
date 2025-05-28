#include "TaskManager.h"
#include "Logger.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

void addTask(std::vector<Task>& tasks, const std::string& description) {
    int newId = tasks.empty() ? 1 : tasks.back().id + 1;
    tasks.push_back({ newId, description, false });
    Logger::getInstance().log("Added task: " + description, LogLevel::INFO);
}

void listTasks(const std::vector<Task>& tasks) {
    Logger::getInstance().log("Listed tasks.", LogLevel::INFO);
    for (const auto& task : tasks) {
        std::cout << "[" << (task.completed ? "x" : " ") << "] "
            << task.id << ": " << task.description << "\n";
    }
}

void markTaskDone(std::vector<Task>& tasks, int id) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.completed = true;
            Logger::getInstance().log("Marked task as done: ID " + std::to_string(id), LogLevel::INFO);
            return;
        }
    }
    Logger::getInstance().log("Task ID " + std::to_string(id) + " not found to mark as done.", LogLevel::WARNING);
}

void deleteTask(std::vector<Task>& tasks, int id) {
    auto it = std::remove_if(tasks.begin(), tasks.end(),
        [id](const Task& t) { return t.id == id; });

    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        Logger::getInstance().log("Deleted task ID " + std::to_string(id), LogLevel::INFO);
    }
    else {
        Logger::getInstance().log("Failed to delete task ID " + std::to_string(id), LogLevel::WARNING);
    }
}

void saveTasks(const std::vector<Task>& tasks, const std::string& filename) {
    try {
        std::ofstream file(filename);
        if (!file) throw std::runtime_error("Unable to open file for writing.");
        for (const auto& task : tasks) {
            file << task.id << ";" << task.description << ";" << task.completed << "\n";
        }
        Logger::getInstance().log("Saved tasks to " + filename, LogLevel::INFO);
    }
    catch (const std::exception& e) {
        Logger::getInstance().log("Error saving tasks: " + std::string(e.what()), LogLevel::ERROR);
    }
}

void loadTasks(std::vector<Task>& tasks, const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file) throw std::runtime_error("Unable to open file for reading.");
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string idStr, desc, doneStr;
            std::getline(ss, idStr, ';');
            std::getline(ss, desc, ';');
            std::getline(ss, doneStr, ';');
            tasks.push_back({ std::stoi(idStr), desc, doneStr == "1" });
        }
        Logger::getInstance().log("Loaded tasks from " + filename, LogLevel::INFO);
    }
    catch (const std::exception& e) {
        Logger::getInstance().log("Error loading tasks: " + std::string(e.what()), LogLevel::ERROR);
    }
}
