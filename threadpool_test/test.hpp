#include "thread.hpp"
void test()
{
    threadpool p(2);
    p.start();
}