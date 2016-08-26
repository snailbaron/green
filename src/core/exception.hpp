#pragma once

#include <string>
#include <sstream>

class Exception
{
public:
    Exception(const std::string &file, const unsigned long line, const std::string &message = "")
        : _file(file)
        , _line(line)
        , _message(message)
    { }

    const std::string Msg() const
    {
        std::ostringstream os;
        os << "[" << _file << ":" << _line << "] ";
        if (!_message.empty()) {
            os << _message;
        }
        else {
            os << "Unknown exception";
        }
        return os.str();
    }

private:
    std::string _file;
    unsigned long _line;
    std::string _message;
};

#define THROW(EXCEPTION, ...) throw EXCEPTION(__FILE__, __LINE__, __VA_ARGS__)
