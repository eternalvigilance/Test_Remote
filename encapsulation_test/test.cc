#include "test.hpp"
int main()
{
    try
    {
        test();
    }
    catch(const char* str)
    {
        cout << str << endl;
    }
    return 0;
}