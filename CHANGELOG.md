# Changelog

All notable changes to the C++ Evolution Task Manager project will be documented in this file.

## [Unreleased]

### Planned
- Lambda functions integration in UI layer
- Unit testing framework
- File-based persistence
- GUI interface
- C++14 features (make_unique, generic lambdas)
- C++17 features (structured bindings, optional)

## [0.2.0] - 2026-01-12

### Added - C++11 Modern Features
- **Smart Pointers Implementation**
  - Migrated from raw object storage to `std::unique_ptr<Task>` in TaskRepository
  - Automatic memory management with RAII principles
  - Clear ownership semantics - repository owns all tasks

- **Move Semantics Integration**
  - `std::move()` usage in TaskRepository::add() for efficient ownership transfer
  - Eliminated unnecessary object copying during task creation
  - Performance improvement through move operations instead of copy operations

- **Enhanced Memory Management**
  - Tasks now allocated on heap instead of stack storage
  - Automatic cleanup when tasks are removed or repository is destroyed
  - Exception-safe memory handling

### Changed
- **TaskRepository Architecture**
  - `std::vector<Task>` → `std::vector<std::unique_ptr<Task>>`
  - `add(const Task&)` → `add(std::unique_ptr<Task>)`
  - Updated all internal algorithms to work with smart pointers
  - Modified lambda functions to dereference unique_ptr objects

- **Task Creation Process**
  - TaskService::createTask() now uses heap allocation
  - Ownership transfer pattern: create → copy for return → move to repository
  - Maintains same public API while improving internal efficiency

- **Compilation Requirements**
  - Updated from C++98 to C++11 standard
  - Added `#include <memory>` for smart pointer support

### Technical Improvements
- **Algorithm Updates**: All `std::find_if` operations updated for unique_ptr compatibility
- **Pointer Access**: Safe raw pointer access using `.get()` method
- **Copy Operations**: Explicit copying in listAll() method for safe data access
- **Move Operations**: Efficient ownership transfer without object duplication

## [0.1.0] - 2026-01-08

### Added
- **Core Task Management System**
  - `Task` class with ID, title, description, and status tracking
  - Support for Pending and Completed task states
  - Unique task ID generation system

- **Data Layer Architecture**
  - `TaskRepository` class for data storage and retrieval
  - In-memory task storage using STL containers
  - CRUD operations (Create, Read, Update, Delete)
  - Task lookup by ID functionality

- **Business Logic Layer**
  - `TaskService` class implementing business rules
  - Task creation with automatic ID assignment
  - Task completion functionality
  - List all tasks feature

- **User Interface Layer**
  - `ConsoleUI` class providing interactive menu system
  - Menu-driven interface with clear options
  - User input validation and error handling
  - Formatted task display with ID, title, status, and description

- **Application Structure**
  - Clean separation of concerns with modular design
  - Object-oriented architecture following SOLID principles
  - Header and implementation file organization
  - Main application entry point with dependency injection

### Technical Details
- **Language Standard**: C++98 foundation
- **Architecture Pattern**: Layered architecture (UI → Service → Repository → Model)
- **Memory Management**: Stack-based objects with automatic cleanup
- **Data Structures**: STL vector for task storage
- **Compilation**: Compatible with standard C++98 compilers

### Project Setup
- Repository initialization and structure
- Source code organization in `src/` directory
- Main application file (`main.cpp`)
- Professional README documentation
- Git repository with clean file structure

### Development Environment
- Windows development setup
- Command-line compilation support
- Executable generation and testing
- Git version control integration

---

## Development Notes

This changelog tracks the evolution from C programming background to modern C++ development. Each version introduces new C++ features while maintaining backward compatibility and clean architecture.

**Version 0.2.0 Highlights:**
- Successfully migrated from C++98 to C++11
- Implemented automatic memory management with smart pointers
- Introduced move semantics for better performance
- Maintained clean API while improving internal efficiency

**Current Status**: ✅ C++11 Smart Pointers Complete  
**Next Milestone**: C++14 Enhanced Features (make_unique, generic lambdas)