// TaskService.cpp
#include "TaskService.h"
#include <memory>

TaskService::TaskService(TaskRepository& repository) : repo(repository) {}

Task TaskService::createTask(const std::string& title, const std::string& desc) {
    int id = repo.getNextId();
    auto newTask = std::make_unique<Task>(id, title, desc);
    Task taskCopy = *newTask;
    repo.add(std::move(newTask));
    return taskCopy;
}

bool TaskService::completeTask(int id) {
    if (auto taskOpt = repo.findById(id); taskOpt.has_value()) {
        taskOpt.value()->setStatus(Completed);
        return true;
    }
    return false;
}

bool TaskService::setDeadline(int id, std::chrono::system_clock::time_point deadline) {
    if (auto taskOpt = repo.findById(id); taskOpt.has_value()) {
        taskOpt.value()->setDeadline(deadline);
        return true;
    }
    return false;
}

std::chrono::system_clock::time_point TaskService::createDeadline(int days, int hours, int minutes) const {
    auto now = std::chrono::system_clock::now();
    auto now_t = std::chrono::system_clock::to_time_t(now);
    std::tm* tm = std::localtime(&now_t);
    
    // Set to midnight
    tm->tm_hour = 0;
    tm->tm_min = 0;
    tm->tm_sec = 0;
    
    auto today = std::chrono::system_clock::from_time_t(std::mktime(tm));
    return today + std::chrono::hours(24 * days + hours) + std::chrono::minutes(minutes);
}

std::vector<Task> TaskService::listAll() const {
    return repo.listAll();
}