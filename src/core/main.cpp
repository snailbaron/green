#include <iostream>
#include <string>
#include <sstream>

#include "singleton.hpp"

template <class T> class Nullable
{
private:
    
};



class Data : public Singleton<Data>
{
public:
    Data() {}
    Data(int data) : _data(data) {}

    int Get() const
    {
        return _data;
    }

private:
    int _data;
};


int main()
{
    try {
        //std::cout << "Data: " << Data::Instance().Get() << std::endl;
        Data::Initialize(21);
        std::cout << "Data: " << Data::Instance().Get() << std::endl;
        Data::Destroy();
        std::cout << "Data: " << Data::Instance().Get() << std::endl;
    } catch (Exception ex) {
        std::cerr << ex.Msg() << std::endl;
    }
}