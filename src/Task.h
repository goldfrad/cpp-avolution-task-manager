// Task.h
#ifndef TASK_H
#define TASK_H 
#include <string>

enum Status { Pending, InProgress, Completed };

class Task
{
    private:
        int id;
        std::string title;
        std::string description;
        Status status;
        
    public:
        Task(int id, const std::string& title, const std::string& desc);
        
        // Rule of 5 - Move semantics
        Task(Task&& other) noexcept;
        Task& operator=(Task&& other) noexcept;
        Task(const Task& other) = default;
        Task& operator=(const Task& other) = default;
        ~Task() = default;
        
        int getId() const;
        std::string getTitle() const;
        std::string getDescription() const;
        Status getStatus() const;
        void setTitle(const std::string& newTitle);
        void setDescription(const std::string& newDesc);
        void setStatus(Status newStatus);
}; 

#endif // TASK_H
