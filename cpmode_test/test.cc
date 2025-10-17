#include "test.hpp"
int main()
{
    try
    {
        test();
    }
    catch(const char* str)
    {std::cout << str << std::endl;}
    //catch(...)
    //{std::cout << "Unexcepted error" << std::endl;}
    return 0;
}