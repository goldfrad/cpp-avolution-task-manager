// Task.cpp
#include "Task.h"

Task::Task(int id, const std::string& title, const std::string& desc)
    : id(id), title(title), description(desc), status(Pending) {}

// Move constructor
Task::Task(Task&& other) noexcept
    : id(other.id), 
      title(std::move(other.title)), 
      description(std::move(other.description)), 
      status(other.status) {}

// Move assignment operator
Task& Task::operator=(Task&& other) noexcept {
    if (this != &other) {
        id = other.id;
        title = std::move(other.title);
        description = std::move(other.description);
        status = other.status;
    }
    return *this;
}

int Task::getId() const {
    return id;
}

std::string Task::getTitle() const {
    return title;
}

std::string Task::getDescription() const {
    return description;
}

Status Task::getStatus() const {
    return status;
}

void Task::setTitle(const std::string& newTitle) {
    title = newTitle;
}

void Task::setDescription(const std::string& newDesc) {
    description = newDesc;
}

void Task::setStatus(Status newStatus) {
    status = newStatus;
}