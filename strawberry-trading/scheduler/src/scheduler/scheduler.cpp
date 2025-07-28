#include <scheduler/scheduler.hpp>
#include <vector>
#include <chrono>
#include <iostream>
#include <thread>

Scheduler::Scheduler() : running(true) {};

void Scheduler::addTask(std::function<void()> func, std::chrono::seconds interval)
{
    tasks.emplace_back(func, interval); // creates new object at the end of tasks
}

bool earlier_run(const Task &task1, const Task &task2)
{
    return task1.nextRun < task2.nextRun;
}

void update_tasks(std::vector<Task> &tasks, const std::chrono::time_point<std::chrono::system_clock> &now)
{
    for (Task &task : tasks)
    {
        if (task.nextRun <= now)
        {
            task.func();
            task.nextRun = now + task.interval;
        };
    };
}

void Scheduler::run()
{
    while (running)
    {
        std::cout << "now1" << std::endl;
        auto now = std::chrono::system_clock::now();
        std::vector<Task>::iterator nextTask = std::min_element(tasks.begin(), tasks.end(), earlier_run); // finds next Task to work on

        if (nextTask == tasks.end())
        {
            break;
        }

        std::chrono::seconds sleepTime = std::chrono::duration_cast<std::chrono::seconds>(nextTask->nextRun - now);

        while (sleepTime > std::chrono::seconds(0) && running)
        {
            std::chrono::seconds chunk = std::min(sleepTime, std::chrono::seconds(10)); // updates every min
            std::cout << chunk << std::endl;

            std::this_thread::sleep_for(chunk);
            sleepTime -= chunk;
        }

        now = std::chrono::system_clock::now();
        update_tasks(tasks, now);
    }
};

void Scheduler::stop()
{
    running = false;
}