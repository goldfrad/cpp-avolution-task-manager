// ConsoleUI.h

#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "TaskService.h"
#include <thread>
#include <atomic>

class ConsoleUI
{
    private:
        TaskService& service;
        std::thread autoSaveThread;
        std::atomic<bool> running;
        
        void autoSaveWorker();
    
    public:
        ConsoleUI(TaskService& svc);
        ~ConsoleUI();
        void run(); 
        void printMenu();
        void handleInput(int choice);
}; 

#endif // CONSOLEUI_H