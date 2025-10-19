#pragma once
#include<thread>
#include<iostream>
#include<condition_variable>
#include<mutex>
#include<vector>
class threadpool
{
public:
    threadpool(size_t&& num):_thread_num(num){_statu_array.reserve(num){};}
    thraedpool(threadpool&)=delete;
    threadpool& operator=(thraedpool&)=delete;
    size_t size(){return _thread_num;}
    void start()
    {
        std::thread fg(foreground);
        for(int i = 0;i < _thread_num;++i)
        {
            //pool.push_back(std::move(std::thread(task_pool)));
            _pool.emplace.back(std::thread(task_pool,i));
        }
    }
    void foreground()
    {
        std::string str;
        while(1)
        {
            std::cout << "Choose a task:";
            std::cin >> str;
            tq.insert(str);
        }
    }
    void taskpool(size_t thraed_id)
    {
        
    }
private:
    size_t _thraed_num;
    std::vector<bool> _statu_array;
    std::vector<std::thread> _pool
    task_queue tq;
    task t;
};
