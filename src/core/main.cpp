#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <string>

#include "process.hpp"

class DelayProcess : public Process {
public:
    DelayProcess(double delay_sec)
        : _delay(delay_sec)
        , _passed(0.0)
    { }

    virtual void update(double delta_sec);

private:
    double _delay;
    double _passed;
};

void DelayProcess::update(double delta_sec)
{
    _passed += delta_sec;
    if (_passed >= _delay) {
        finish(Result::Success);
    }
}


class PrintProcess : public Process {
public:
    PrintProcess(const std::string &msg)
        : _msg(msg)
    { }

    virtual void update(double delta_sec);

private:
    std::string _msg;
};

void PrintProcess::update(double delta_sec)
{
    std::cout << _msg << std::endl;
    finish(Result::Success);
}


int main()
{
    ProcessManager mgr;
    {
        std::shared_ptr<Process> delay(new DelayProcess(2.0));
        mgr.attach_process(delay)->attach_on_success(std::make_shared<PrintProcess>("onetwo"));
        
        //delay->attach_on_success(std::make_shared<PrintProcess>("onetwo"));
    }

    auto prev_time = std::chrono::system_clock::now();
    while (mgr.is_active()) {
        auto time = std::chrono::system_clock::now();
        std::chrono::duration<double> delta = time - prev_time;
        prev_time = time;

        mgr.update(delta.count());
    }
}