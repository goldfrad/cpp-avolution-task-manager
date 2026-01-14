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
        void save() const { repo.save(); }
        
        // Filter with lambda predicate
        template<typename Predicate>
        std::vector<const Task*> filter(Predicate predicate) const {
            std::vector<const Task*> result;
            for (const auto& task : repo.getAllTasks()) {
                if (predicate(*task)) {
                    result.push_back(task.get());
                }
            }
            return result;
        }
}; 

#endif // TASKSERVICE_H

