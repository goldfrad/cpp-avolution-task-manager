// TaskService.h

#ifndef TASKSERVICE_H
#define TASKSERVICE_H

#include "TaskRepository.h"

class TaskService
{
    private:
        TaskRepository& repo;
        
    public:
        TaskService(TaskRepository& repository);
        Task createTask(const std::string& title, const std::string& desc);
        bool completeTask(int id);
        std::vector<Task> listAll() const;
}; 

#endif // TASKSERVICE_H

