// ConsoleUI.h

#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "TaskService.h"

class ConsoleUI
{
    private:
        TaskService& service;
    
    public:
        ConsoleUI(TaskService& svc);
        void run(); 
        void printMenu();
        void handleInput(int choice);
}; 

#endif // CONSOLEUI_H