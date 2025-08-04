#include <scheduler/scheduler.hpp>
#include <vector>
#include <chrono>
#include <iostream>
#include <thread>
#include <ctime>
#include <iomanip>


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
            std::time_t time_t_now = std::chrono::system_clock::to_time_t(now);
            std::cout << "Time: " << std::put_time(std::localtime(&time_t_now), "%Y-%m-%d %H:%M:%S");

            task.func();
            std::cout << std::endl;
            task.nextRun = now + task.interval;
        };
    };
}

void Scheduler::run()
{
    while (running)
    {
        auto now = std::chrono::system_clock::now();
        std::vector<Task>::iterator nextTask = std::min_element(tasks.begin(), tasks.end(), earlier_run); // finds next Task to work on
        if (nextTask == tasks.end())
        {
            break;
        }

        auto sleepTime = nextTask->nextRun - now;

        while (sleepTime > std::chrono::seconds(0) && running)
        {
            auto chunk = std::min(sleepTime, std::chrono::duration_cast<decltype(sleepTime)>(std::chrono::seconds(60))); // updates every min
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