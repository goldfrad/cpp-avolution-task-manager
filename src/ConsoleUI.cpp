// ConsoleUI.cpp
#include "ConsoleUI.h"
#include <iostream>
#include <string>
#include <limits>
#include <chrono>

ConsoleUI::ConsoleUI(TaskService& svc) : service(svc), running(false) {}

ConsoleUI::~ConsoleUI() {
    if (running) {
        running = false;
        if (autoSaveThread.joinable()) {
            autoSaveThread.join();
        }
    }
}

void ConsoleUI::autoSaveWorker() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::minutes(1));
        if (running) {
            service.save();
            std::cout << "\n[Auto-saved]" << std::endl;
        }
    }
}

// Helper function to safely read an integer
int readInt() {
    int value;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter a number: ";
    }
    return value;
}

void ConsoleUI::run() {
    std::cout << "=== Task Manager Started ===" << std::endl;
    std::cout << "[Auto-save enabled - every 1 minute]" << std::endl;
    
    // Start auto-save thread
    running = true;
    autoSaveThread = std::thread(&ConsoleUI::autoSaveWorker, this);
    
    int choice;
    do {
        printMenu();
        std::cout << "Enter your choice: ";
        choice = readInt();
        handleInput(choice);
    } while (choice != 0);
    
    // Stop auto-save thread
    running = false;
    if (autoSaveThread.joinable()) {
        autoSaveThread.join();
    }
    
    service.save();
    std::cout << "=== Task Manager Ended ===" << std::endl;
}

void ConsoleUI::printMenu() {
    std::cout << "\n--- Task Manager Menu ---" << std::endl;
    std::cout << "1. List all tasks" << std::endl;
    std::cout << "2. Add new task" << std::endl;
    std::cout << "3. Complete task" << std::endl;
    std::cout << "4. Search tasks" << std::endl;
    std::cout << "5. Set deadline" << std::endl;
    std::cout << "6. Show overdue tasks" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

void ConsoleUI::handleInput(int choice) {
    switch (choice) {
        case 1: {
            std::cout << "\n=== All Tasks ===" << std::endl;
            auto tasks = service.listAll();
            if (tasks.empty()) {
                std::cout << "No tasks found." << std::endl;
            } else {
                for (const auto& task : tasks) {
                    std::string statusStr;
                    switch (task.getStatus()) {
                        case Pending: statusStr = "Pending"; break;
                        case InProgress: statusStr = "In Progress"; break;
                        case Completed: statusStr = "Completed"; break;
                    }
                    std::string overdueStr = task.isOverdue() ? " [OVERDUE]" : "";
                    std::cout << "ID: " << task.getId() 
                              << " | Title: " << task.getTitle()
                              << " | Status: " << statusStr << overdueStr << std::endl;
                    std::cout << "  Description: " << task.getDescription() << std::endl;
                    std::cout << "  Created: " << task.getCreatedAtStr() 
                              << " | Deadline: " << task.getDeadlineStr() << std::endl;
                }
            }
            break;
        }
        case 2: {
            std::cout << "\n=== Add New Task ===" << std::endl;
            std::cin.ignore(); // Clear input buffer
            std::string title, description;
            std::cout << "Enter task title: ";
            std::getline(std::cin, title);
            std::cout << "Enter task description: ";
            std::getline(std::cin, description);
            
            Task newTask = service.createTask(title, description);
            std::cout << "Task created with ID: " << newTask.getId() << std::endl;
            
            std::cout << "Set deadline? (1=Yes, 0=No): ";
            int setDl = readInt();
            if (setDl == 1) {
                std::cout << "Enter days from now (0 for today): ";
                int days = readInt();
                std::cout << "Enter hour (0-23): ";
                int hours = readInt();
                std::cout << "Enter minutes (0-59): ";
                int minutes = readInt();
                
                auto now = std::chrono::system_clock::now();
                auto today = std::chrono::floor<std::chrono::hours>(now) - 
                             std::chrono::hours(std::chrono::duration_cast<std::chrono::hours>(now.time_since_epoch()).count() % 24);
                auto deadline = today + std::chrono::hours(24 * days + hours) + std::chrono::minutes(minutes);
                
                service.setDeadline(newTask.getId(), deadline);
                std::cout << "Deadline set!" << std::endl;
            }
            break;
        }
        case 3: {
            std::cout << "\n=== Complete Task ===" << std::endl;
            std::cout << "Enter task ID to complete: ";
            int taskId = readInt();
            
            if (service.completeTask(taskId)) {
                std::cout << "Task " << taskId << " marked as completed!" << std::endl;
            } else {
                std::cout << "Task not found!" << std::endl;
            }
            break;
        }
        case 4: {
            std::cout << "\n=== Search Tasks ===" << std::endl;
            std::cout << "1. By status (Pending)" << std::endl;
            std::cout << "2. By status (In Progress)" << std::endl;
            std::cout << "3. By status (Completed)" << std::endl;
            std::cout << "4. By keyword in title" << std::endl;
            std::cout << "5. By ID range" << std::endl;
            std::cout << "Choose search type: ";
            
            int searchType = readInt();
            
            std::vector<const Task*> results;
            
            switch (searchType) {
                case 1:
                    results = service.filter([](const Task& t) { 
                        return t.getStatus() == Pending; 
                    });
                    break;
                case 2:
                    results = service.filter([](const Task& t) { 
                        return t.getStatus() == InProgress; 
                    });
                    break;
                case 3:
                    results = service.filter([](const Task& t) { 
                        return t.getStatus() == Completed; 
                    });
                    break;
                case 4: {
                    std::cin.ignore();
                    std::string keyword;
                    std::cout << "Enter keyword: ";
                    std::getline(std::cin, keyword);
                    results = service.filter([keyword](const Task& t) { 
                        return t.getTitle().find(keyword) != std::string::npos; 
                    });
                    break;
                }
                case 5: {
                    std::cout << "Enter min ID: ";
                    int minId = readInt();
                    std::cout << "Enter max ID: ";
                    int maxId = readInt();
                    results = service.filter([minId, maxId](const Task& t) { 
                        return t.getId() >= minId && t.getId() <= maxId; 
                    });
                    break;
                }
                default:
                    std::cout << "Invalid search type!" << std::endl;
                    break;
            }
            
            if (results.empty()) {
                std::cout << "No tasks found." << std::endl;
            } else {
                std::cout << "\n=== Search Results ===" << std::endl;
                for (const auto* task : results) {
                    std::string statusStr;
                    switch (task->getStatus()) {
                        case Pending: statusStr = "Pending"; break;
                        case InProgress: statusStr = "In Progress"; break;
                        case Completed: statusStr = "Completed"; break;
                    }
                    std::cout << "ID: " << task->getId() 
                              << " | Title: " << task->getTitle()
                              << " | Status: " << statusStr << std::endl;
                }
            }
            break;
        }
        case 0:
            std::cout << "Goodbye!" << std::endl;
            break;
        case 5: {
            std::cout << "\n=== Set Deadline ===" << std::endl;
            std::cout << "Enter task ID: ";
            int taskId = readInt();
            
            std::cout << "Enter days from now (0 for today): ";
            int days = readInt();
            std::cout << "Enter hour (0-23): ";
            int hours = readInt();
            std::cout << "Enter minutes (0-59): ";
            int minutes = readInt();
            
            // Get today at midnight
            auto now = std::chrono::system_clock::now();
            auto today = std::chrono::floor<std::chrono::hours>(now) - 
                         std::chrono::hours(std::chrono::duration_cast<std::chrono::hours>(now.time_since_epoch()).count() % 24);
            
            auto deadline = today + std::chrono::hours(24 * days + hours) + std::chrono::minutes(minutes);
            
            if (service.setDeadline(taskId, deadline)) {
                std::cout << "Deadline set successfully!" << std::endl;
            } else {
                std::cout << "Task not found!" << std::endl;
            }
            break;
        }
        case 6: {
            std::cout << "\n=== Overdue Tasks ===" << std::endl;
            auto results = service.filter([](const Task& t) { 
                return t.isOverdue(); 
            });
            
            if (results.empty()) {
                std::cout << "No overdue tasks." << std::endl;
            } else {
                for (const auto* task : results) {
                    std::cout << "ID: " << task->getId() 
                              << " | Title: " << task->getTitle()
                              << " | Deadline: " << task->getDeadlineStr() << std::endl;
                }
            }
            break;
        }
        default:
            std::cout << "Invalid choice! Please try again." << std::endl;
            break;
    }
}