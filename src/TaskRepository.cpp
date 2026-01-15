// TaskRepository.cpp
#include "TaskRepository.h"
#include <algorithm>
#include <fstream>
#include <sstream>

TaskRepository::TaskRepository(const std::string& file) 
    : filename(file), nextId(1) {
    load();
}

void TaskRepository::load() {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return; // No file yet, start fresh
    }
    
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        
        std::istringstream iss(line);
        std::string idStr, title, description, statusStr, createdStr, deadlineStr;
        
        std::getline(iss, idStr, '|');
        std::getline(iss, title, '|');
        std::getline(iss, description, '|');
        std::getline(iss, statusStr, '|');
        std::getline(iss, createdStr, '|');
        std::getline(iss, deadlineStr, '|');
        
        int id = std::stoi(idStr);
        Status status = static_cast<Status>(std::stoi(statusStr));
        
        auto task = std::make_unique<Task>(id, title, description);
        task->setStatus(status);
        
        // Load timestamps (support old format without timestamps)
        if (!createdStr.empty()) {
            try {
                auto createdTime = std::chrono::system_clock::from_time_t(std::stoll(createdStr));
                task->setCreatedAt(createdTime);
            } catch (...) {}
        }
        if (!deadlineStr.empty() && deadlineStr != "-1") {
            try {
                auto deadlineTime = std::chrono::system_clock::from_time_t(std::stoll(deadlineStr));
                task->setDeadline(deadlineTime);
            } catch (...) {}
        }
        
        tasks.push_back(std::move(task));
        
        if (id >= nextId) {
            nextId = id + 1;
        }
    }
}

void TaskRepository::save() const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        return;
    }
    
    for (const auto& task : tasks) {
        auto createdTime = std::chrono::system_clock::to_time_t(task->getCreatedAt());
        auto deadlineTime = std::chrono::system_clock::to_time_t(task->getDeadline());
        
        // Use -1 for no deadline
        std::string deadlineStr = (task->getDeadline() == std::chrono::system_clock::time_point::max()) 
            ? "-1" : std::to_string(deadlineTime);
        
        outFile << task->getId() << "|"
                << task->getTitle() << "|"
                << task->getDescription() << "|"
                << static_cast<int>(task->getStatus()) << "|"
                << createdTime << "|"
                << deadlineStr << "\n";
    }
}

int TaskRepository::getNextId() {
    return nextId++;
}

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
