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
    mgr.attach_process(std::make_shared<PrintProcess>("before"))
        ->next(std::make_shared<DelayProcess>(1.0))
        ->next(std::make_shared<PrintProcess>("after"))
        ->next(std::make_shared<DelayProcess>(0.5));

    mgr.roll();
}