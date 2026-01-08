# C++ Evolution Task Manager

A task management system demonstrating the evolution from **C programming** to **modern C++** development.

## Overview

This project showcases my transition from **3 years of C programming experience** to **modern C++** development. It's a task management system built step by step, evolving from **C++98 basics** to the latest **C++23 features**. The goal is to demonstrate clean design, object-oriented programming, and the adoption of modern C++ best practices.

## Current Features

- **Console-based interface** for task management
- **Object-oriented design** with clean separation of concerns
- **CRUD operations** for tasks (Create, Read, Update, Delete)
- **Task status tracking** (Pending/Completed)
- **Modular architecture** with dedicated classes:
  - `Task` - Task data model
  - `TaskRepository` - Data storage and retrieval
  - `TaskService` - Business logic layer
  - `ConsoleUI` - User interface layer

## Project Structure

```
cpp-avolution-task-manager/
├── README.md
├── main.cpp                 # Application entry point
└── src/
    ├── Task.h              # Task class definition
    ├── Task.cpp            # Task implementation
    ├── TaskRepository.h    # Data layer interface
    ├── TaskRepository.cpp  # Data layer implementation
    ├── TaskService.h       # Business logic interface
    ├── TaskService.cpp     # Business logic implementation
    ├── ConsoleUI.h         # UI layer interface
    └── ConsoleUI.cpp       # UI layer implementation
```

## Evolution Roadmap

### C++98 Foundation
- Basic OOP design with classes
- STL containers usage
- Clean class interfaces

### Planned C++ Evolution Steps

**C++11 Features:**
- Smart pointers (`std::unique_ptr`, `std::shared_ptr`)
- Move semantics and rvalue references
- Lambda functions
- `auto` keyword usage

**C++14 Enhancements:**
- Generic lambdas
- `std::make_unique`
- Improved `constexpr`

**C++17 Modernization:**
- Structured bindings
- `std::optional` for safer null handling
- `std::variant` for type-safe unions
- Filesystem support

**C++20 Advanced Features:**
- Concepts for template constraints
- Ranges library
- Coroutines for async operations
- Modules for better code organization

**C++23 Latest Features:**
- `std::print` for modern output
- `std::expected` for error handling
- Stacktrace integration
- Enhanced ranges

## Why This Project?

- **Progressive Learning**: Shows ability to apply modern C++ features incrementally
- **Software Design Skills**: Demonstrates modular architecture, clean abstractions, and maintainability
- **C Background Leverage**: Highlights how C experience translates to efficient, safe, and modern C++ code
- **Portfolio Showcase**: Real-world example of professional C++ development practices

## How to Build and Run

```bash
# Compile the project
g++ -std=c++98 main.cpp src/*.cpp -o task_manager

# Run the application
./task_manager
```

## Usage Example

```
=== Task Manager Started ===

--- Task Manager Menu ---
1. List all tasks
2. Add new task
3. Complete task
0. Exit

Enter your choice: 2
Enter task title: Learn Modern C++
Enter task description: Study C++20 and C++23 features
Task created with ID: 1
```

## Future Work

- [ ] Add comprehensive unit tests for each module
- [ ] Implement async task scheduler with real-world integrations
- [ ] Add file-based persistence
- [ ] Create performance benchmarks comparing C++ versions
- [ ] Add GUI interface using modern C++ frameworks
- [ ] Implement advanced features (task priorities, deadlines, categories)

## Learning Journey

This repository is not just a task manager – it's a **learning journey** and a **portfolio project** to demonstrate readiness for professional C++ development. Each evolution step will be documented with explanations of the modern C++ features being introduced and their benefits.

---

**Status**: 🟢 Active Development | **Current Version**: C++98 Foundation