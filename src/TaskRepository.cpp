// TaskRepository.cpp
#include "TaskRepository.h"
#include <algorithm>

void TaskRepository::add(std::unique_ptr<Task> task) {
    tasks.push_back(std::move(task));
}

bool TaskRepository::remove(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [id](const std::unique_ptr<Task>& task) { return task->getId() == id; });
    
    if (it != tasks.end()) {
        tasks.erase(it);
        return true;
    }
    return false;
}

Task* TaskRepository::findById(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [id](const std::unique_ptr<Task>& task) { return task->getId() == id; });
    
    return (it != tasks.end()) ? it->get() : nullptr;
}

Task* TaskRepository::findByStatus(Status status) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [status](const std::unique_ptr<Task>& task) { return task->getStatus() == status; });
    
    return (it != tasks.end()) ? it->get() : nullptr;
}

const std::vector<std::unique_ptr<Task>>& TaskRepository::getAllTasks() const {
    return tasks;
}

std::vector<Task> TaskRepository::listAll() const {
    std::vector<Task> result;
    for (const auto& task : tasks) {
        result.push_back(*task);
    }
    return result;
}