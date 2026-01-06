// Task.cpp
#include "Task.h"

Task::Task(int id, const std::string& title, const std::string& desc)
    : id(id), title(title), description(desc), status(Pending) {}

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