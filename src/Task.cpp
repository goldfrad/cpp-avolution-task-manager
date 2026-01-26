// Task.cpp
#include "Task.h"
#include <ctime>
#include <iomanip>
#include <sstream>

// Helper function implementation
std::string statusToString(Status status) {
    switch (status) {
        case Pending: return "Pending";
        case InProgress: return "In Progress";
        case Completed: return "Completed";
        default: return "Unknown";
    }
}

Task::Task(int id, const std::string& title, const std::string& desc)
    : id(id), 
      title(title.substr(0, MAX_TITLE_LENGTH)), 
      description(desc.substr(0, MAX_DESCRIPTION_LENGTH)), 
      status(Pending),
      createdAt(std::chrono::system_clock::now()),
      deadline(std::chrono::system_clock::time_point::max()) {}

// Move constructor
Task::Task(Task&& other) noexcept
    : id(other.id), 
      title(std::move(other.title)), 
      description(std::move(other.description)), 
      status(other.status),
      createdAt(other.createdAt),
      deadline(other.deadline) {}

// Move assignment operator
Task& Task::operator=(Task&& other) noexcept {
    if (this != &other) {
        id = other.id;
        title = std::move(other.title);
        description = std::move(other.description);
        status = other.status;
        createdAt = other.createdAt;
        deadline = other.deadline;
    }
    return *this;
}

int Task::getId() const { return id; }
std::string Task::getTitle() const { return title; }
std::string Task::getDescription() const { return description; }
Status Task::getStatus() const { return status; }

std::chrono::system_clock::time_point Task::getCreatedAt() const { 
    return createdAt; 
}

std::chrono::system_clock::time_point Task::getDeadline() const { 
    return deadline; 
}

void Task::setTitle(const std::string& newTitle) { 
    title = newTitle.substr(0, MAX_TITLE_LENGTH); 
}

void Task::setDescription(const std::string& newDesc) { 
    description = newDesc.substr(0, MAX_DESCRIPTION_LENGTH); 
}
void Task::setStatus(Status newStatus) { status = newStatus; }

void Task::setDeadline(std::chrono::system_clock::time_point dl) { 
    deadline = dl; 
}

void Task::setCreatedAt(std::chrono::system_clock::time_point ca) {
    createdAt = ca;
}

bool Task::isOverdue() const {
    if (status == Completed) return false;
    if (deadline == std::chrono::system_clock::time_point::max()) return false;
    return std::chrono::system_clock::now() > deadline;
}

std::string Task::getCreatedAtStr() const {
    auto time = std::chrono::system_clock::to_time_t(createdAt);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M");
    return ss.str();
}

std::string Task::getDeadlineStr() const {
    if (deadline == std::chrono::system_clock::time_point::max()) {
        return "No deadline";
    }
    auto time = std::chrono::system_clock::to_time_t(deadline);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M");
    return ss.str();
}
