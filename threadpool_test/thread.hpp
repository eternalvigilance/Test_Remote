#pragma once
#include<thread>
#include<iostream>
#include<condition_variable>
#include<mutex>
#include<vector>
#include "task.hpp"
#include<unordered_map>
class threadpool
{
public:
    threadpool(size_t num):_thread_num(num),_turn(0),sta(true)
    {
        for(size_t i = 0;i < _thread_num;++i)
        {
            //pool.push_back(std::move(std::thread(task_pool)));
            _pool.emplace_back(&threadpool::task_pool,this,i);
        }
    }
    threadpool(const threadpool&)=delete;
    threadpool& operator=(const threadpool&)=delete;
    size_t size(){return _thread_num;}
    void start()
    {
        std::string str;
        while(1)
        {
            std::cout << "Choose a task:";
            std::string tmp;
            std::cin >> tmp;
            str = tmp;
            if(str=="view")_task.view();
            else if(_task.istask(str))
            {
                _tq.insert(std::move(str));
                _tq.notempty();
                cv.notify_all();
                sta = false;
            }
            else std::cout << str << ": task not found" << std::endl;

            while(!sta);
        }
    }
    void task_pool(size_t id)
    {
        while(1)
        {
            std::unique_lock<std::mutex> ulock(m);
            //std::cout << "Thread" << id << " has been loaded" << std::endl;
            cv.wait(ulock,[&id,this](){return (!_tq.isempty() && (id == _turn));});
            _task_map[id]=_tq.pop();
            _turn = (_turn+1)%_thread_num;
            int re = _task.call(_task_map[id]);
            std::cout << "Thread" << id << ':' << re << std::endl;
            cv.notify_all();
            sta = true;
            ulock.unlock();
        }
    }
    ~threadpool()
    {
        for(auto& t:_pool){if(t.joinable())t.join();}
    }
private:
    size_t _thread_num;
    volatile size_t _turn;
    std::vector<std::thread> _pool;
    std::unordered_map<size_t,std::string> _task_map;
    std::mutex m;
    std::condition_variable cv;
    task_queue _tq;
    task _task;
    volatile bool sta;
};
