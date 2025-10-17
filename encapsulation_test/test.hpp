#pragma once
#include<iostream>
#include<functional>
#include<utility>
#include<sys/types.h>
#include<pthread.h>
#include<unistd.h>
using std::cout;
using std::endl;
namespace mythread
{
class thread
{
    typedef pthread_t tid;
    public:
        thread()=delete;
        template<class F,class... Args>
        thread(F&& f,Args&&... args):_status(true)
        {
            auto* fp = new std::function<void()>(std::bind(std::forward<F>(f),std::forward<Args>(args)...));
            auto pf = [](void* p) -> void* {
                auto* func = static_cast<std::function<void()>*>(p);
                (*func)();          
                delete func;        
                return nullptr;
                };
            if(!pthread_create(&_id,nullptr,pf,fp));
            else throw "Creating failed";
        }
        thread(thread&)=delete;
        thread& operator = (const thread&)=delete;
        void join()
        {
            if(!pthread_join(_id,nullptr))_status=false;
            else throw "Joining failed";
        }
        bool joinable(){return _status;}
        tid getid(){return _id;}
        void detach()
        {
            if(!pthread_detach(_id));
            else throw "Detaching failed";
        }
    private:  
        tid _id;
        bool _status;
    };
}
using namespace mythread;
static int sta = 0;
void test()
{
    auto task = []()->void
    {
        for(int i = 5; i > 0;)
        {
            if(!sta)
            {
                cout << "This is the new thread" << endl;
                cout.flush();
                sta=1;
                --i;
            }
            sleep(1);
        }
    };
    thread th(task);
    th.detach();
    sleep(1);
    for(int i = 5; i > 0;)
    {
        if(sta)
        {
            cout << "This is the main thread" << endl;
            cout.flush();
            sta=0;
            --i;
        }
        sleep(1);
    }
}
