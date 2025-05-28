#pragma once
// TaskManager.h
#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <vector>
#include <string>
#include "Task.h"

void addTask(std::vector<Task>& tasks, const std::string& description);
void listTasks(const std::vector<Task>& tasks);
void markTaskDone(std::vector<Task>& tasks, int id);
void deleteTask(std::vector<Task>& tasks, int id);
void saveTasks(const std::vector<Task>& tasks, const std::string& filename);
void loadTasks(std::vector<Task>& tasks, const std::string& filename);

#endif
