# Todo List Application in C++

A simple command-line Todo List application implemented in C++ demonstrating:

- Modern C++ features and STL usage (e.g., `std::vector`, `std::string`)
- Design pattern: Singleton (`Logger`)
- File handling with error checking
- Logging with log levels and timestamping
- Log filtering by severity (`INFO`, `WARNING`, `ERROR`)
- Exception handling and input validation

---

## Features

- Add, list, mark as done, delete, and save tasks
- Tasks are persisted in a text file (`tasks.txt`)
- Logs actions and errors to console and a log file (`log.txt`)
- Configurable logging verbosity (filter logs by level)
- Robust error handling with meaningful messages

---

## Project Structure

| File               | Description                                      |
|--------------------|-------------------------------------------------|
| `main.cpp`          | Main program loop and user interface            |
| `Task.h`            | Definition of `Task` struct                      |
| `TaskManager.h/cpp` | Functions for task operations (add, delete, etc.) |
| `Logger.h`          | Singleton Logger class with log levels and filtering |

---

## Prerequisites

- C++ compiler supporting C++11 or higher (tested with MSVC in Visual Studio Professional)
- C++ Standard Library

---

## How to Build and Run

1. Clone the repository:
   ```bash
   git clone https://github.com/chYashwanth/TodoListApp.git
   cd TodoListApp
