#pragma once
#include<iostream>
#include<pthread.h>
#include<exception>
#include<sys/types.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<stdio.h>
using std::cout;
static inline pid_t gettid(){return syscall(SYS_gettid);}
void* hander(void* arg)
{
    sleep(2);
    //pid_t tid = gettid();
    pthread_t tid = (pthread_t)arg;
    for(int i = 10; i  > 0;--i)
    {
        //cout << "This is a thread , and the thread ID is:" << tid << std::endl;
        printf("This is a thread , and the thread ID is:0x%x\n",tid);
        sleep(2);
    }
    return nullptr;
}
void test()
{
    pthread_t thread_id = 0;
    if(!pthread_create(&thread_id,nullptr,hander,(void*)&thread_id))
    {
        pthread_detach(thread_id);
        int i = 10;
        while(--i)
        {
            cout << "Successful creating,this is process" << std::endl;
            cout.flush();
            sleep(2);
            //int num = pthread_join(thread_id,nullptr);
            //if(!num)return;
        }
    }
    else throw "Creating thread fail";
}