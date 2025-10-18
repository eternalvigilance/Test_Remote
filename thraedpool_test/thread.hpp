#pragma once
#include<thread>
#include<iostream>
#include<condition_variable>
#include<mutex>
class threadpool
{
public:
    threadpool(size_t&& num):_thread_num(num)
    {
        for(num;num > 0;--num)
        {
            thread(task);
        }
    }
    thraedpool(threadpool&)=delete;
    threadpool& operator=(thraedpool&)=delete;

private:
    size_t _thraed_num;
};
