#pragma once
#include "circular_queue.hpp"
#include<unordered_map>
#include<functional>
#include<string>
#include<tuple>
#include<cstdio>
#include<iostream>
#include<vector>
class task_queue
{
public:
    task_queue(size_t&& task_num){queue.reserve(std::forward<size_t>(task_num));}
    task_queue(){}
    void reserve(size_t&& num){queue.reserve(std::forward<size_t>(num));}
    task_queue(task_queue&)=delete;
    task_queue& operator=(task_queue&)=delete;
    void insert(std::string&& task_name){queue.insert(std::forward<std::string>(task_name));}
    std::string&& pop(){return queue.pop();}
    bool isempty(){return queue.isempty();}
    bool isoverflow(){return queue.isoverflow();}
    void notempty(){return queue.notempty();}
private:
    circular_queue<std::string> queue;
};
class task
{
public:
    bool istask(const std::string& task_name)
    {
        if(_boolmap.find(task_name)!= _boolmap.end())return true;
        else return false;
    }
    int terminal()
    {
        std::string command;
        std::cin >> command;
        std::string full = "bash -c\""+ command + "\"";
        FILE* fp = popen(full.c_str(),"r");
        if(!fp)throw "Popen error in task::terminal";
        char buff[256];
        while(fgets(buff,sizeof(buff),fp))std::cout << buff << std::endl;
        int re = pclose(fp);
        if(re==-1)throw "Pclose error in task::terminal";
        return 1;
    }
    int calculate()
    {
        char op;
        int left,right;
        if (!(std::cin >> left >> op >> right)) throw "Invalid input for calculate";
        if(op=='+')return (left+right);
        else if(op=='-')return (left-right);
        else if(op=='*')return (left*right);
        else if(op=='/' )
        {
            if(right==0)throw "Division by zero error";
            else return (left/right);
        }
        else if(op=='%')return (left%right);
        else if(op=='&')return (left&right);
        else if(op=='^')return (left^right);
        else if(op=='|')return (left|right);
        else throw "Not an operator";
    }
    task()
    {
        _boolmap["terminal"]=true;
        _boolmap["calculate"]=true;
        _name.push_back("terminal");
        _name.push_back("calculate");
    }
    task(const task&)=delete;
    task operator=(const task&)=delete;
    // template<class... Args>
    // int call(const std::string& task_name,Args&&... args)
    // {
    //     if(istask(task_name))
    //     {
    //         if(task_name=="terminal")return terminal(std::forward<Args>(args)...);
    //         if(task_name=="calculate")return calculate(std::forward<Args>(args)...);
    //     }
    //     else std::cout << task_name << ": task not found" << std::endl;
    // }
    int call(const std::string& task_name)
    {
        if(istask(task_name))
        {
            if(task_name=="terminal")return terminal();
            if(task_name=="calculate")return calculate();
        }
        else std::cout << task_name << ": task not found" << std::endl;
    }
    // template<class F,class... Args>
    // void add_f(F&& f,Args... args)
    // {
    //     auto new_f = std::function<void()>
    //     (std::bind(std::forward<F>(f),std::forward<Args>(args)...));
    //     auto arg = std::make_tuple(args...);
    //     _table[std::get<1>(arg)] = new_f;
    //     _boolmap[std::get<1>(arg)]=true;
    //     _name.push_back(std::get<1>(arg));
    // }
    void excute(std::string& task_name)
    {
        _table[task_name]();
    }
    void view()
    {
        for(auto& v:_name)std::cout << v << "    ";
        std::cout << std::endl;
    }
private:
    std::unordered_map<std::string,bool> _boolmap;
    std::unordered_map<std::string,std::function<void()>> _table;
    std::vector<std::string> _name;
};