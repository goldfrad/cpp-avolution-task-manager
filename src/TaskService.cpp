// TaskService.cpp
#include "TaskService.h"

TaskService::TaskService(TaskRepository& repository) : repo(repository) {}

Task TaskService::createTask(const std::string& title, const std::string& desc) {
    static int nextId = 1;
    Task newTask(nextId++, title, desc);
    repo.add(newTask);
    return newTask;
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