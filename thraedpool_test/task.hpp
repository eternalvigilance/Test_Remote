#pragma once
#include "circular_queue.hpp"
#include<unordered_map>
#include<functional>
#include<string>
#include<tuple>
class task_queue
{
public:
    task_queue(size_t&& task_num){queue.reserve(task_num);}
    task_queue(){}
    void reserve(size_t&& num){queue.reserve(num);}
    task_queue(task_queue&)=delete;
    task_queue& operator=(task_queue&)=delete;
    void insert(std::string& task_name){queue.insert(task_name);}
    std::string& pop(){return queue.pop();}
private:
    circular_queue<std::string> queue;
};
class task
{
public:
    bool istask(std::string& task_name)
    {
        if(map.find(task_name)!= map.end())return true;;
        else return false;
    }
    void terminal(const std::string& command)
    {

    }
    int calculate(const char& op,const int left,const int right)
    {

    }
    task()=delete;
    task(task&)=delete;
    task operator=(task&)=delete;
    template<class... Arg>
    task(std::string& task_name)
    {
        map[terminal]=true;
        map[calculate]=true;
    }
    template<class... Args>
    auto call(const std::string& task_name,Args&&... args)->
    typename std::resulte_of<decltype(&task::terminal(std::string))(task,Args...)>::type
    {
        if(istask())
        {
            if(task_name=="terminal")return terminal(std::forward<Args>(args)...);
            if(task_name=="calculate")return calculate(std::forward<Args>(args)...);
        }
        else std::cout << task_name << ": task not found" << std::endl;
    }
    template<class F,class... Args>
    void add_f(F&& f,Args... args)
    {
        auto new_f = std::function<void()>
        (std::bind(std::forward<F>(f),std::forward<Args>(args)...));
        auto arg = std::make_tuple(args...);
        table[get<1>(arg)] = new_f;
    }
    void map(std::string& task_name)
    {
        (*table[task_name])();
    }
private:
    std::unordered_map<std::string,bool> map;
    std::unordered_map<std::string,std::function<void()>> table;
};