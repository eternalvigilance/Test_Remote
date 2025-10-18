#pragma once
#include "circular_queue.hpp"
#include<unordered_map>
#include<functional>
#include<string>
class task_queue
{
public:
    task_queue(size_t&& task_num){queue.reserve(task_num);}
    task_queue(task_queue&)=delete;
    task_queue& operator=(task_queue&)=delete;
    void insert(string& task_name){queue.insert(task_name);}
    string& pop(){return queue.pop();}
private:
    circular_queue<std::string> queue;
};
class task
{
public:
    bool istask(string& task_name){return map[task_name];}
    void terminal(string& command)
    {

    }
    int calculate(char& op,int left,int right)
    {

    }
    task()=delete;
    task(task&)=delete;
    task operator=(task&)=delete;
    task(string& task_name)
    {
        map[terminal]=true;
        table[terminal]=terminal;
        map[calculate]=true;
        map[calculate]=calculate;
    }
    void call(string& task_name)
    {
        if(istask()){map(task_name);}
        else std::cout << task_name << ": task not found" << std::endl;
    }
    void map(string& task_name)
    {

    }
private:
    std::unordered_map<std::string,bool> map;
    std::unordered_map<std::string,std::function<void()>> table;
};