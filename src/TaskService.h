// TaskService.h

#ifndef TASKSERVICE_H
#define TASKSERVICE_H

#include "TaskRepository.h"
#include "Concepts.h"

class TaskService
{
    private:
        TaskRepository& repo;
        
    public:
        TaskService(TaskRepository& repository);
        Task createTask(const std::string& title, const std::string& desc);
        bool completeTask(int id);
        bool setDeadline(int id, std::chrono::system_clock::time_point deadline);
        
        // Returns {success, message} using structured bindings
        std::pair<bool, std::string> validateAndCreateTask(const std::string& title, const std::string& desc);
        
        // Helper to create deadline from days/hours/minutes
        std::chrono::system_clock::time_point createDeadline(int days, int hours, int minutes) const;
        
        std::vector<Task> listAll() const;
        void save() const { repo.save(); }
        
        // C++20 Concept-constrained filter - only accepts valid predicates
        template<TaskPredicate Pred>
        std::vector<const Task*> filter(Pred predicate) const {
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

