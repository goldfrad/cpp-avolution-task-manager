# Changelog

All notable changes to the C++ Evolution Task Manager project will be documented in this file.

## [Unreleased]

### Planned
- Unit testing framework
- GUI interface

## [0.8.3] - 2026-01-15

### Added - C++17 Structured Bindings & Inline Variables
- **Structured Bindings**
  - `auto [success, message] = validateAndCreateTask(...)`
  - Automatic unpacking of pairs/tuples
  - Cleaner code for multi-return functions

- **Inline Variables**
  - `static inline constexpr` for class constants
  - No need for separate .cpp definitions
  - Cleaner header-only constants

- **Task Validation**
  - New `validateAndCreateTask()` function
  - Returns {success, message} pair
  - Validates title and description length

### Technical Improvements
- More expressive multi-return values
- Better validation with clear error messages
- Modern C++17 syntax throughout

## [0.8.2] - 2026-01-15

### Added - C++17 Modern Syntax
- **if with initializer**
  - Declare variables directly in if statements
  - Cleaner scope management: `if (auto x = func(); x.has_value())`
  - Reduced variable lifetime and improved readability

- **std::string_view**
  - Non-owning string references for better performance
  - Used in Task constructor and setters
  - Eliminates unnecessary string copies

### Technical Improvements
- More expressive and concise code
- Better performance with string_view
- Tighter variable scoping with if initializers

## [0.8.1] - 2026-01-15

### Added - std::filesystem Backup System
- **Automatic Backup**
  - Creates backup before every save operation
  - Backups stored in `backups/` directory
  - Timestamped backup files: `tasks_backup_[timestamp].txt`
  
- **Filesystem Operations**
  - `fileExists()` - checks if tasks file exists
  - `createBackup()` - creates timestamped backup
  - Uses `std::filesystem` for file operations

### Technical Improvements
- Data safety with automatic backups
- C++17 filesystem library integration
- Backup directory auto-creation

## [0.8.0] - 2026-01-15

### Added - C++17 std::optional
- **Type-safe Optional Values**
  - `findById()` now returns `std::optional<Task*>`
  - Explicit handling of "not found" cases
  - Eliminates nullptr checks with `.has_value()` and `.value()`

### Changed
- Upgraded to C++17 standard
- Safer null handling throughout codebase
- More expressive API with optional return types

## [0.7.2] - 2026-01-15

### Changed - Code Cleanup & Separation of Concerns
- **Status to String Helper**
  - Added `statusToString()` function to eliminate duplicate code
  - Centralized Status enum to string conversion
  - Removed 3 duplicate switch statements from UI code

- **Business Logic Moved to Service Layer**
  - `createDeadline()` method in TaskService
  - Deadline calculation logic moved from UI to Service
  - Better separation between presentation and business logic

### Technical Improvements
- DRY principle - eliminated code duplication
- Cleaner UI layer - only presentation logic
- Service layer handles all business rules

## [0.7.1] - 2026-01-15

### Changed - Code Refactoring
- **ConsoleUI Modularization**
  - Extracted menu handlers into separate functions
  - `handleListAll()`, `handleAddTask()`, `handleCompleteTask()`
  - `handleSearchTasks()`, `handleSetDeadline()`, `handleShowOverdue()`
  
- **enum class MenuOption**
  - Replaced magic numbers with named enum values
  - Type-safe menu option handling
  - Better code readability

### Technical Improvements
- Reduced `handleInput()` complexity
- Single Responsibility Principle for each handler
- Improved maintainability and testability

## [0.7.0] - 2026-01-15

### Added - C++14 constexpr Constants
- **Compile-time Constants**
  - `MAX_TITLE_LENGTH` = 100 characters
  - `MAX_DESCRIPTION_LENGTH` = 500 characters
  - `MIN_ID` and `MAX_ID` for ID validation
  
- **constexpr Helper Functions**
  - `isValidId()` - compile-time ID validation
  - `getMaxTitleLength()` - accessor for max title length
  - `getMaxDescriptionLength()` - accessor for max description length

### Changed
- Upgraded to C++14 standard
- Title and description automatically truncated to max length
- UI shows character limits when creating tasks

## [0.6.0] - 2026-01-15

### Added - Multithreading with std::thread
- **Auto-Save Background Thread**
  - Automatic save every 1 minute
  - Runs in separate thread using `std::thread`
  - Thread-safe with `std::atomic<bool>`
  - Proper cleanup in destructor

- **Thread Management**
  - Background worker thread in ConsoleUI
  - Safe thread termination on exit
  - `std::this_thread::sleep_for` for timing

### Technical Improvements
- Added `-pthread` flag for compilation
- Proper RAII for thread lifecycle management
- Visual feedback with [Auto-saved] messages

## [0.5.0] - 2026-01-15

### Added - Time Management with std::chrono
- **Task Timestamps**
  - `createdAt` - automatically set when task is created
  - `deadline` - optional deadline with date and time
  - `isOverdue()` - checks if task is past deadline

- **New Menu Options**
  - Set deadline (days, hours, minutes)
  - Show overdue tasks
  - Option to set deadline when creating task

- **Display Enhancements**
  - Tasks show creation date and deadline
  - Overdue tasks marked with [OVERDUE]

### Changed
- File format now includes timestamps (backward compatible)
- Move semantics updated for new time fields

## [0.4.0] - 2026-01-14

### Added - File Persistence
- **File-based Storage**
  - Tasks saved to `tasks.txt` on exit
  - Tasks loaded automatically on startup
  - Plain text format: `ID|Title|Description|Status`

- **TaskRepository Enhancements**
  - Constructor accepts filename (default: "tasks.txt")
  - `load()` - reads tasks from file
  - `save()` - writes tasks to file
  - `getNextId()` - manages ID counter across sessions

### Changed
- Moved `nextId` from TaskService to TaskRepository
- Used `std::make_unique` instead of raw `new`
- Added `save()` method to TaskService (delegates to repo)

## [0.3.0] - 2026-01-13

### Added - Move Semantics & Lambda Filters
- **Move Semantics in Task Class (Rule of 5)**
  - Move constructor for efficient object transfer
  - Move assignment operator
  - Explicit copy constructor/assignment (= default)
  - Proper `noexcept` specification

- **Lambda-based Task Filtering**
  - New `filter()` template function in TaskService
  - Accepts any predicate (lambda/functor)
  - Returns `std::vector<const Task*>` for read-only access

- **Search Menu in ConsoleUI**
  - Filter by status (Pending/In Progress/Completed)
  - Search by keyword in title
  - Filter by ID range
  - Lambda capture demonstrations (`[keyword]`, `[minId, maxId]`)

- **Input Validation**
  - `readInt()` helper function for safe integer input
  - Handles non-numeric input gracefully
  - Clears cin error state and buffer

### Technical Improvements
- Template function in header (required for templates)
- `std::numeric_limits` for proper buffer clearing
- Consistent use of `const Task*` for read-only access

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

**Current Status**: C++11 Smart Pointers Complete  
**Next Milestone**: C++14 Enhanced Features (make_unique, generic lambdas)