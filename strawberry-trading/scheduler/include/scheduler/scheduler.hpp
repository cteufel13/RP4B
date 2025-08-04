#pragma once
#include <chrono>
#include <functional>
#include <vector>
#include <atomic>

struct Task
{
    std::function<void()> func;
    std::chrono::seconds interval;
    std::chrono::time_point<std::chrono::system_clock> nextRun;

    Task(std::function<void()> f, std::chrono::seconds i)
        : func(f), interval(i), nextRun(std::chrono::system_clock::now() + i) {}
};

class Scheduler
{
public:
    Scheduler();
    void addTask(std::function<void()> func, std::chrono::seconds interval);
    void run();
    void stop();

private:
    std::vector<Task> tasks;
    std::atomic<bool> running;
};