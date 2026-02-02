// Task.h
#ifndef TASK_H
#define TASK_H 
#include <string>
#include <string_view>
#include <chrono>

enum Status { Pending, InProgress, Completed };

// Helper function to convert Status to string
std::string statusToString(Status status);

class Task
{
    private:
        int id;
        std::string title;
        std::string description;
        Status status;
        std::chrono::system_clock::time_point createdAt;
        std::chrono::system_clock::time_point deadline;
        
    public:
        // C++17 inline variables - no need for .cpp definition
        static inline constexpr size_t MAX_TITLE_LENGTH = 100;
        static inline constexpr size_t MAX_DESCRIPTION_LENGTH = 500;
        static inline constexpr int MIN_ID = 1;
        static inline constexpr int MAX_ID = 999999;
        
        Task(int id, std::string_view title, std::string_view desc);
        
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
        std::chrono::system_clock::time_point getCreatedAt() const;
        std::chrono::system_clock::time_point getDeadline() const;
        
        void setTitle(std::string_view newTitle);
        void setDescription(std::string_view newDesc);
        void setStatus(Status newStatus);
        void setDeadline(std::chrono::system_clock::time_point dl);
        void setCreatedAt(std::chrono::system_clock::time_point ca);
        
        bool isOverdue() const;
        std::string getCreatedAtStr() const;
        std::string getDeadlineStr() const;
        
        // C++14 constexpr helper functions
        static constexpr bool isValidId(int id) {
            return id >= MIN_ID && id <= MAX_ID;
        }
        
        static constexpr size_t getMaxTitleLength() {
            return MAX_TITLE_LENGTH;
        }
        
        static constexpr size_t getMaxDescriptionLength() {
            return MAX_DESCRIPTION_LENGTH;
        }
}; 

#endif // TASK_H
