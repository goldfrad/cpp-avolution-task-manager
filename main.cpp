// main.cpp

#include "src/Task.h"
#include "src/TaskRepository.h"
#include "src/TaskService.h"    
#include "src/ConsoleUI.h"
#include "src/Debug.h"

int main()
{
    DEBUG_ALWAYS("Start Application");
    
    TaskRepository repo;
    TaskService service(repo);
    ConsoleUI ui(service);
    ui.run();

    DEBUG_ALWAYS("End Application");   
    return 0;
}