// TaskService.cpp
#include "TaskService.h"
#include <memory>

TaskService::TaskService(TaskRepository& repository) : repo(repository) {}

Task TaskService::createTask(const std::string& title, const std::string& desc) {
    static int nextId = 1;
    auto newTask = std::unique_ptr<Task>(new Task(nextId++, title, desc));
    Task taskCopy = *newTask;  // Create copy to return
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