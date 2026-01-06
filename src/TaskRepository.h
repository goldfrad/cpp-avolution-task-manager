// TaskRepository.h

#ifndef TASKREPOSITORY_H
#define TASKREPOSITORY_H

#include <vector>
#include "Task.h"

class TaskRepository {
private:
    std::vector<Task> tasks;

public:
    void add(const Task& task);
    bool remove(int id);
    Task* findById(int id);
    Task* findByStatus(Status status);
    std::vector<Task> getAllTasks() const;
    std::vector<Task> listAll() const;
};

#endif // TASKREPOSITORY_H