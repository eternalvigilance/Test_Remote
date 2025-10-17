#include"test.hpp"
int main()
{
    try
    {
        test();
    }
        catch(const char* str)
        {
            cout << *str << std::endl;
        }
        catch(...)
        {
            cout << "Unexcepted error" << std::endl;
        }
    return 0;
}