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
    std::cout << "[Auto-backup enabled - backups saved before each save]" << std::endl;
    
    // Start auto-save thread
    running = true;
    autoSaveThread = std::thread(&ConsoleUI::autoSaveWorker, this);
    
    int choice;
    do {
        printMenu();
        std::cout << "Enter your choice: ";
        choice = readInt();
        handleInput(choice);
    } while (choice != static_cast<int>(MenuOption::Exit));
    
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
    std::cout << static_cast<int>(MenuOption::ListAll) << ". List all tasks" << std::endl;
    std::cout << static_cast<int>(MenuOption::AddTask) << ". Add new task" << std::endl;
    std::cout << static_cast<int>(MenuOption::CompleteTask) << ". Complete task" << std::endl;
    std::cout << static_cast<int>(MenuOption::SearchTasks) << ". Search tasks" << std::endl;
    std::cout << static_cast<int>(MenuOption::SetDeadline) << ". Set deadline" << std::endl;
    std::cout << static_cast<int>(MenuOption::ShowOverdue) << ". Show overdue tasks" << std::endl;
    std::cout << static_cast<int>(MenuOption::Exit) << ". Exit" << std::endl;
}

void ConsoleUI::handleInput(int choice) {
    MenuOption option = static_cast<MenuOption>(choice);
    
    switch (option) {
        case MenuOption::ListAll:
            handleListAll();
            break;
        case MenuOption::AddTask:
            handleAddTask();
            break;
        case MenuOption::CompleteTask:
            handleCompleteTask();
            break;
        case MenuOption::SearchTasks:
            handleSearchTasks();
            break;
        case MenuOption::SetDeadline:
            handleSetDeadline();
            break;
        case MenuOption::ShowOverdue:
            handleShowOverdue();
            break;
        case MenuOption::Exit:
            std::cout << "Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Invalid choice! Please try again." << std::endl;
            break;
    }
}

void ConsoleUI::handleListAll() {
    std::cout << "\n=== All Tasks ===" << std::endl;
    auto tasks = service.listAll();
    if (tasks.empty()) {
        std::cout << "No tasks found." << std::endl;
        return;
    }
    
    for (const auto& task : tasks) {
        std::string overdueStr = task.isOverdue() ? " [OVERDUE]" : "";
        std::cout << "ID: " << task.getId() 
                  << " | Title: " << task.getTitle()
                  << " | Status: " << statusToString(task.getStatus()) << overdueStr << std::endl;
        std::cout << "  Description: " << task.getDescription() << std::endl;
        std::cout << "  Created: " << task.getCreatedAtStr() 
                  << " | Deadline: " << task.getDeadlineStr() << std::endl;
    }
}

void ConsoleUI::handleAddTask() {
    std::cout << "\n=== Add New Task ===" << std::endl;
    std::cin.ignore();
    
    // Get task details from user
    std::string title, description;
    std::cout << "Enter task title (max " << Task::MAX_TITLE_LENGTH << " chars): ";
    std::getline(std::cin, title);
    std::cout << "Enter task description (max " << Task::MAX_DESCRIPTION_LENGTH << " chars): ";
    std::getline(std::cin, description);
    
    // C++17 Structured bindings - unpack validation result
    auto [success, message] = service.validateAndCreateTask(title, description);
    
    std::cout << message << std::endl;
    
    // If task created successfully, optionally set deadline
    if (success) {
        std::cout << "Set deadline? (1=Yes, 0=No): ";
        int setDl = readInt();
        if (setDl == 1) {
            // Get deadline details
            std::cout << "Enter days from now (0 for today): ";
            int days = readInt();
            std::cout << "Enter hour (0-23): ";
            int hours = readInt();
            std::cout << "Enter minutes (0-59): ";
            int minutes = readInt();
            
            // Create deadline timestamp
            auto deadline = service.createDeadline(days, hours, minutes);
            
            // Get the last created task ID and set its deadline
            auto tasks = service.listAll();
            if (!tasks.empty()) {
                service.setDeadline(tasks.back().getId(), deadline);
                std::cout << "Deadline set!" << std::endl;
            }
        }
    }
}

void ConsoleUI::handleCompleteTask() {
    std::cout << "\n=== Complete Task ===" << std::endl;
    std::cout << "Enter task ID to complete: ";
    int taskId = readInt();
    
    if (service.completeTask(taskId)) {
        std::cout << "Task " << taskId << " marked as completed!" << std::endl;
    } else {
        std::cout << "Task not found!" << std::endl;
    }
}

void ConsoleUI::handleSearchTasks() {
    std::cout << "\n=== Search Tasks ===" << std::endl;
    std::cout << "1. By status (Pending)" << std::endl;
    std::cout << "2. By status (In Progress)" << std::endl;
    std::cout << "3. By status (Completed)" << std::endl;
    std::cout << "4. By keyword in title" << std::endl;
    std::cout << "5. By ID range" << std::endl;
    std::cout << "Choose search type: ";
    
    int searchType = readInt();
    std::vector<const Task*> results;
    
    // Apply filter based on search type using lambda predicates
    switch (searchType) {
        case 1:
            // Filter for pending tasks
            results = service.filter([](const Task& t) { 
                return t.getStatus() == Pending; 
            });
            break;
        case 2:
            // Filter for in-progress tasks
            results = service.filter([](const Task& t) { 
                return t.getStatus() == InProgress; 
            });
            break;
        case 3:
            // Filter for completed tasks
            results = service.filter([](const Task& t) { 
                return t.getStatus() == Completed; 
            });
            break;
        case 4: {
            // Search by keyword in title
            std::cin.ignore();
            std::string keyword;
            std::cout << "Enter keyword: ";
            std::getline(std::cin, keyword);
            // Lambda captures keyword by value
            results = service.filter([keyword](const Task& t) { 
                return t.getTitle().find(keyword) != std::string::npos; 
            });
            break;
        }
        case 5: {
            // Filter by ID range (inclusive)
            std::cout << "Enter min ID: ";
            int minId = readInt();
            std::cout << "Enter max ID: ";
            int maxId = readInt();
            // Lambda captures both min and max IDs
            results = service.filter([minId, maxId](const Task& t) { 
                return t.getId() >= minId && t.getId() <= maxId; 
            });
            break;
        }
        default:
            std::cout << "Invalid search type!" << std::endl;
            return;
    }
    
    // Display results
    if (results.empty()) {
        std::cout << "No tasks found." << std::endl;
    } else {
        std::cout << "\n=== Search Results ===" << std::endl;
        for (const auto* task : results) {
            std::cout << "ID: " << task->getId() 
                      << " | Title: " << task->getTitle()
                      << " | Status: " << statusToString(task->getStatus()) << std::endl;
        }
    }
}

void ConsoleUI::handleSetDeadline() {
    std::cout << "\n=== Set Deadline ===" << std::endl;
    std::cout << "Enter task ID: ";
    int taskId = readInt();
    
    std::cout << "Enter days from now (0 for today): ";
    int days = readInt();
    std::cout << "Enter hour (0-23): ";
    int hours = readInt();
    std::cout << "Enter minutes (0-59): ";
    int minutes = readInt();
    
    auto deadline = service.createDeadline(days, hours, minutes);
    
    if (service.setDeadline(taskId, deadline)) {
        std::cout << "Deadline set successfully!" << std::endl;
    } else {
        std::cout << "Task not found!" << std::endl;
    }
}

void ConsoleUI::handleShowOverdue() {
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
}
