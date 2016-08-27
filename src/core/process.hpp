#pragma once

#include <memory>
#include <list>
#include <functional>

/**
    Process

    Process lifecycle:

     +---------------+ start +---------+ finish +----------+
     | Uninitialized | ----> | Running | -----> | Finished |
     +---------------+       +---------+        +----------+

    |                                   |      |            |
    +-----------------------------------+      +------------+
               result is None                   result is set
                                             (Success or Failure)
*/

class Process {
public:
    enum class State {
        Uninitialized,
        Running,
        Finished,
    };

    enum class Result {
        None,
        Success,
        Failure,
    };

    Process()
        : _state(Process::State::Uninitialized)
        , _result(Process::Result::None)
    { }

    virtual void start();
    virtual void update(double delta_sec);

    void finish(Result result = Result::None);
    std::shared_ptr<Process> and(std::shared_ptr<Process> next);
    std::shared_ptr<Process> or(std::shared_ptr<Process> next);
    
    State state() const { return _state; }
    Result result() const { return _result; }

    std::shared_ptr<Process> remove_success_child();
    std::shared_ptr<Process> remove_failure_child();

private:
    State _state;
    Result _result;

    std::shared_ptr<Process> _next_on_success;
    std::shared_ptr<Process> _next_on_failure;
};


/**
    ProcessManager
*/

class ProcessManager {
public:
    void update(double deltaSec);

    std::shared_ptr<Process> attach_process(std::shared_ptr<Process> process);

    bool is_active() const { return !_processes.empty(); }

    void roll();

private:
    std::list<std::shared_ptr<Process>> _processes;
};
