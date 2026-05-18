// TaskService.cpp
#include "TaskService.h"
#include <memory>

#include "Debug.h"

TaskService::TaskService(TaskRepository& repository) : repo(repository) {}

Task TaskService::createTask(const std::string& title, const std::string& desc) {
    int id = repo.getNextId();
    auto newTask = std::make_unique<Task>(id, title, desc);
    Task taskCopy = *newTask;
    repo.add(std::move(newTask));
    DEBUG_LOGF("Task created with ID: {} Title {}", id, title);   
    return taskCopy;
}

std::pair<bool, std::string> TaskService::validateAndCreateTask(const std::string& title, const std::string& desc) {
    // Validation
    if (title.empty()) {
        return {false, "Title cannot be empty"};
    }
    
    if (title.length() > Task::MAX_TITLE_LENGTH) {
        return {false, "Title too long (max " + std::to_string(Task::MAX_TITLE_LENGTH) + " chars)"};
    }
    
    if (desc.length() > Task::MAX_DESCRIPTION_LENGTH) {
        return {false, "Description too long (max " + std::to_string(Task::MAX_DESCRIPTION_LENGTH) + " chars)"};
    }
    
    // Create task
    createTask(title, desc);
    return {true, "Task created successfully"};
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
    // Get current time
    auto now = std::chrono::system_clock::now();
    auto now_t = std::chrono::system_clock::to_time_t(now);
    std::tm* tm = std::localtime(&now_t);
    
    // Set time to midnight (00:00:00) to start from beginning of day
    tm->tm_hour = 0;
    tm->tm_min = 0;
    tm->tm_sec = 0;
    
    // Convert back to time_point
    auto today = std::chrono::system_clock::from_time_t(std::mktime(tm));
    
    // Add the specified days, hours, and minutes
    return today + std::chrono::hours(24 * days + hours) + std::chrono::minutes(minutes);
}

std::vector<Task> TaskService::listAll() const {
    return repo.listAll();
}

// C++20 Ranges: Get task titles by status
std::vector<std::string> TaskService::getTaskTitlesByStatus(Status status) const {
    const auto& tasks = repo.getAllTasks();
    
    // Use ranges to filter by status and transform to titles
    auto titleView = tasks 
        | std::views::filter([status](const auto& task) { return task->getStatus() == status; })
        | std::views::transform([](const auto& task) { return task->getTitle(); });
    
    // Convert view to vector
    return std::vector<std::string>(titleView.begin(), titleView.end());
}

// C++20 Ranges: Count tasks by status
size_t TaskService::countByStatus(Status status) const {
    const auto& tasks = repo.getAllTasks();
    
    // Use ranges to filter and count
    auto filtered = tasks | std::views::filter([status](const auto& task) { 
        return task->getStatus() == status; 
    });
    
    return std::ranges::distance(filtered);
}

// C++20 Ranges: Get all overdue task titles
std::vector<std::string> TaskService::getOverdueTitles() const {
    const auto& tasks = repo.getAllTasks();
    
    // Use ranges to filter overdue tasks and get their titles
    auto overdueView = tasks
        | std::views::filter([](const auto& task) { return task->isOverdue(); })
        | std::views::transform([](const auto& task) { return task->getTitle(); });
    
    // Convert view to vector
    return std::vector<std::string>(overdueView.begin(), overdueView.end());
}