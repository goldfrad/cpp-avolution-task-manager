// TaskRepository.h

#ifndef TASKREPOSITORY_H
#define TASKREPOSITORY_H

#include <vector>
#include <memory>
#include "Task.h"

class TaskRepository {
private:
    std::vector<std::unique_ptr<Task>> tasks;

public:
    void add(std::unique_ptr<Task> task);
    bool remove(int id);
    Task* findById(int id);
    Task* findByStatus(Status status);
    const std::vector<std::unique_ptr<Task>>& getAllTasks() const;
    std::vector<Task> listAll() const;
};

#endif // TASKREPOSITORY_H