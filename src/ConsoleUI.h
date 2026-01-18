// ConsoleUI.h

#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "TaskService.h"
#include <thread>
#include <atomic>

enum class MenuOption {
    Exit = 0,
    ListAll = 1,
    AddTask = 2,
    CompleteTask = 3,
    SearchTasks = 4,
    SetDeadline = 5,
    ShowOverdue = 6
};

class ConsoleUI
{
    private:
        TaskService& service;
        std::thread autoSaveThread;
        std::atomic<bool> running;
        
        void autoSaveWorker();
        
        // Menu handlers
        void handleListAll();
        void handleAddTask();
        void handleCompleteTask();
        void handleSearchTasks();
        void handleSetDeadline();
        void handleShowOverdue();
    
    public:
        ConsoleUI(TaskService& svc);
        ~ConsoleUI();
        void run(); 
        void printMenu();
        void handleInput(int choice);
}; 

#endif // CONSOLEUI_H