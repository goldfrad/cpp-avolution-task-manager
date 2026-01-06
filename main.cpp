// main.cpp

#include "src/Task.h"
#include "src/TaskRepository.h"
#include "src/TaskService.h"    
#include "src/ConsoleUI.h"

int main()
{
    TaskRepository repo;2
    TaskService service(repo);
    ConsoleUI ui(service);
    ui.run();   
    return 0;
}