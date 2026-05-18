# C++ Evolution Task Manager

A task management system demonstrating the evolution from **C programming** to **modern C++** development.

## Overview

This project showcases my transition from **3 years of C programming experience** to **modern C++** development. It's a task management system built step by step, evolving from **C++98 basics** to the latest **C++23 features**. The goal is to demonstrate clean design, object-oriented programming, and the adoption of modern C++ best practices.

## Current Features

- **Console-based interface** for task management
- **Modern C++20 formatting** with `std::format` for clean, aligned output
- **Statistics display** with formatted tables showing task distribution
- **File persistence** - tasks saved/loaded automatically
- **Auto-save** - background thread saves every minute
- **Auto-backup** - timestamped backups before each save
- **Time management** with `std::chrono`:
  - Creation timestamps
  - Deadlines with date/time
  - Overdue detection
- **Object-oriented design** with clean separation of concerns
- **CRUD operations** for tasks (Create, Read, Update, Delete)
- **Task status tracking** (Pending/In Progress/Completed)
- **Search & Filter** with lambda predicates:
  - Filter by status
  - Search by keyword in title
  - Filter by ID range
  - Show overdue tasks
- **Move semantics** for efficient object handling
- **Input validation** for robust user interaction
- **Multithreading** with `std::thread` for background operations
- **Type-safe optional values** with `std::optional`
- **Filesystem operations** with `std::filesystem`
- **Modular architecture** with dedicated classes:
  - `Task` - Task data model with move semantics and timestamps
  - `TaskRepository` - Data storage with smart pointers, file I/O, and backups
  - `TaskService` - Business logic with lambda filtering
  - `ConsoleUI` - User interface with input validation and auto-save thread

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
    ├── ConsoleUI.cpp       # UI layer implementation
    └── Concepts.h          # C++20 Concepts definitions
```

## Evolution Roadmap

### C++98 Foundation (v0.1.0)
- Basic OOP design with classes
- STL containers usage
- Clean class interfaces

### C++11 Modern Features (v0.2.0 - v0.6.0)
- **Smart pointers** (`std::unique_ptr`) for automatic memory management
- **Move semantics** - Rule of 5 implementation in Task class
- **Auto keyword** usage in algorithms
- **Lambda functions** with captures for filtering and searching
- **Template functions** for generic predicates
- **Input validation** with `std::numeric_limits`
- **std::chrono** for time management (timestamps, deadlines)
- **std::thread** for background auto-save
- **std::atomic** for thread-safe operations

### Planned C++ Evolution Steps

### C++14 Enhanced Features (v0.7.0)
- **constexpr** constants and functions for compile-time evaluation
- Improved type safety with constexpr validation
- Character limits for task fields

### C++17 Modernization (v0.8.0 - v0.8.3)
- **std::optional** for safer null handling
- **std::filesystem** for file operations and backups
- **if with initializer** for cleaner scope management
- **std::string_view** for efficient string handling
- **Structured bindings** for multi-return values
- **Inline variables** for header-only constants
- Type-safe optional return values
- Automatic backup system
- Input validation with clear error messages

### C++20 Advanced Features (v0.9.0 - v0.9.3)
- **Concepts** for template constraints and type safety
- **Ranges** for functional-style data processing
- **std::format** for modern, type-safe string formatting
- **std::source_location** for automatic debug context capture
- Range views (`filter`, `transform`) for lazy evaluation
- Composable range pipelines with `|` operator
- Query functions using modern range operations
- Formatted output with alignment and precision control
- Professional table formatting for statistics
- Debug logging system with file/line/function tracking
- Compile-time validation of template arguments
- Self-documenting generic code

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
# Compile the project (C++20 required)
g++ -std=c++20 main.cpp src/*.cpp -o task_manager -pthread

# Run the application
./task_manager
```

**Requirements:**
- C++20 compatible compiler
- pthread support for multithreading

## Usage Example

```
=== Task Manager Started ===

--- Task Manager Menu ---
1. List all tasks
2. Add new task
3. Complete task
4. Search tasks
0. Exit

Enter your choice: 2
Enter task title: Learn Modern C++
Enter task description: Study C++20 and C++23 features
Task created with ID: 1

Enter your choice: 4
=== Search Tasks ===
1. By status (Pending)
2. By status (In Progress)
3. By status (Completed)
4. By keyword in title
5. By ID range
Choose search type: 4
Enter keyword: Modern
=== Search Results ===
ID: 1 | Title: Learn Modern C++ | Status: Pending
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

**Status**: 🟢 Active Development | **Current Version**: C++20 Debug Logging (v0.9.3)