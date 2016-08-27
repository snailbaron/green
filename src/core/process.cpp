#include "process.hpp"
#include <chrono>

/**
    Process implementation
*/

std::shared_ptr<Process> Process::remove_success_child()
{
    std::shared_ptr<Process> ps;
    ps.swap(_next_on_success);
    return ps;    
}

std::shared_ptr<Process> Process::remove_failure_child()
{
    std::shared_ptr<Process> ps;
    ps.swap(_next_on_failure);
    return ps;
}

void Process::start()
{
    _state = State::Running;
}

void Process::finish(Result result)
{
    _result = result;
    _state = State::Finished;
}

std::shared_ptr<Process> Process::next(std::shared_ptr<Process> next)
{
    _next_on_success = next;
    return next;
}

void Process::attach_on_failure(std::shared_ptr<Process> next)
{
    _next_on_failure = next;
}



/**
    ProcessManager implementation
*/

void ProcessManager::update(double deltaSec)
{
    auto it = _processes.begin();
    while (it != _processes.end()) {
        std::shared_ptr<Process> current_process = (*it);

        auto save = it;
        ++it;

        if (current_process->state() == Process::State::Uninitialized) {
            current_process->start();
        }

        if (current_process->state() == Process::State::Running) {
            current_process->update(deltaSec);
        }

        if (current_process->state() == Process::State::Finished) {
            if (current_process->result() == Process::Result::Success) {
                std::shared_ptr<Process> child = current_process->remove_success_child();
                if (child) {
                    attach_process(child);
                }
            }
            else if (current_process->result() == Process::Result::Failure) {
                std::shared_ptr<Process> child = current_process->remove_failure_child();
                if (child) {
                    attach_process(child);
                }
            }
            _processes.erase(save);
        }
    }
}

std::shared_ptr<Process> ProcessManager::attach_process(std::shared_ptr<Process> process)
{
    _processes.push_back(process);
    return process;
}

void ProcessManager::roll()
{
    auto prev_time = std::chrono::system_clock::now();
    while (is_active()) {
        auto time = std::chrono::system_clock::now();
        std::chrono::duration<double> delta = time - prev_time;
        prev_time = time;

        update(delta.count());
    }
}