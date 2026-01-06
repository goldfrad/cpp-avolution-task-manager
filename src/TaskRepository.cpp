// TaskRepository.cpp
#include "TaskRepository.h"
#include <algorithm>

void TaskRepository::add(const Task& task) {
    tasks.push_back(task);
}

bool TaskRepository::remove(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [id](const Task& task) { return task.getId() == id; });
    
    if (it != tasks.end()) {
        tasks.erase(it);
        return true;
    }
    return false;
}

Task* TaskRepository::findById(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [id](const Task& task) { return task.getId() == id; });
    
    return (it != tasks.end()) ? &(*it) : nullptr;
}

Task* TaskRepository::findByStatus(Status status) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [status](const Task& task) { return task.getStatus() == status; });
    
    return (it != tasks.end()) ? &(*it) : nullptr;
}

std::vector<Task> TaskRepository::getAllTasks() const {
    return tasks;
}

std::vector<Task> TaskRepository::listAll() const {
    return tasks;
}