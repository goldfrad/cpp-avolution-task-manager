// TaskRepository.h

#ifndef TASKREPOSITORY_H
#define TASKREPOSITORY_H

#include <vector>
#include <memory>
#include <string>
#include <optional>
#include "Task.h"

class TaskRepository {
private:
    std::vector<std::unique_ptr<Task>> tasks;
    std::string filename;
    int nextId;
    
    void load();

public:
    TaskRepository(const std::string& file = "tasks.txt");
    void save() const;
    void add(std::unique_ptr<Task> task);
    bool remove(int id);
    std::optional<Task*> findById(int id);
    Task* findByStatus(Status status);
    const std::vector<std::unique_ptr<Task>>& getAllTasks() const;
    std::vector<Task> listAll() const;
    int getNextId();
};

#endif // TASKREPOSITORY_H