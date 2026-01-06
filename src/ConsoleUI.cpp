// ConsoleUI.cpp
#include "ConsoleUI.h"
#include <iostream>
#include <string>

ConsoleUI::ConsoleUI(TaskService& svc) : service(svc) {}

void ConsoleUI::run() {
    std::cout << "=== Task Manager Started ===" << std::endl;
    
    int choice;
    do {
        printMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        handleInput(choice);
    } while (choice != 0);
    
    std::cout << "=== Task Manager Ended ===" << std::endl;
}

void ConsoleUI::printMenu() {
    std::cout << "\n--- Task Manager Menu ---" << std::endl;
    std::cout << "1. List all tasks" << std::endl;
    std::cout << "2. Add new task" << std::endl;
    std::cout << "3. Complete task" << std::endl;
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
                    std::cout << "ID: " << task.getId() 
                              << " | Title: " << task.getTitle()
                              << " | Status: " << statusStr << std::endl;
                    std::cout << "  Description: " << task.getDescription() << std::endl;
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
            break;
        }
        case 3: {
            std::cout << "\n=== Complete Task ===" << std::endl;
            int taskId;
            std::cout << "Enter task ID to complete: ";
            std::cin >> taskId;
            
            if (service.completeTask(taskId)) {
                std::cout << "Task " << taskId << " marked as completed!" << std::endl;
            } else {
                std::cout << "Task not found!" << std::endl;
            }
            break;
        }
        case 0:
            std::cout << "Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Invalid choice! Please try again." << std::endl;
            break;
    }
}