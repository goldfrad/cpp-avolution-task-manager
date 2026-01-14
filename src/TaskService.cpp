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
    Task* task = repo.findById(id);
    if (task) {
        task->setStatus(Completed);
        return true;
    }
    return false;
}

std::vector<Task> TaskService::listAll() const {
    return repo.listAll();
}