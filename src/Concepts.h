// Concepts.h - C++20 Concepts for Task Manager

#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>
#include <string>
#include "Task.h"

// Concept: Type must be convertible to string
template<typename T>
concept StringConvertible = requires(T t) {
    { std::to_string(t) } -> std::convertible_to<std::string>;
} || std::convertible_to<T, std::string>;

// Concept: Type must be comparable
template<typename T>
concept Comparable = requires(T a, T b) {
    { a == b } -> std::convertible_to<bool>;
    { a != b } -> std::convertible_to<bool>;
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
};

// Concept: Type must be a valid Task ID
template<typename T>
concept TaskId = std::integral<T> && requires(T id) {
    requires Task::isValidId(static_cast<int>(id));
};

// Concept: Predicate that works on Tasks
template<typename Pred>
concept TaskPredicate = requires(Pred pred, const Task& task) {
    { pred(task) } -> std::convertible_to<bool>;
};

// Concept: Type can be used as a task filter
template<typename F>
concept TaskFilter = std::invocable<F, const Task&> && 
                     std::convertible_to<std::invoke_result_t<F, const Task&>, bool>;

#endif // CONCEPTS_H
