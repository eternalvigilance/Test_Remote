#pragma once
#include<mutex>
template<class T>
class circular_queue
{
public:
    circular_queue(size_t num = 1024):_head(0),_end(0),_capacity(num),_isoverflow(false),_isempty(false)
    {_p = new T[num]{};}
    circular_queue(const circular_queue&) = delete;
    circular_queue& operator=(const circular_queue&) = delete;
    ~circular_queue()
    {
        delete[] _p;
        _p = nullptr;
    }
    void insert(const int&& num)
    {
        _wm.lock();
        _p[_end] = num;
        _end = (_end + 1)%_capacity;
        if(_end == _head)_isoverflow = true;
        _wm.unlock();
    }
    T& pop()
    {
        _rm.lock();
        size_t re = _p[_head];
        _head = (_head + 1)%_capacity;
        if(_head==_end)_isempty = true;
        _rm.unlock();
        return re;
    }
    void reserve(size_t&& num)
    {
        if(num <= _capaciti)
        {
            throw "You can only expand capacity";
            return;
        }
        if(_p != nullptr)
        {
            if(isempty())
            {
                delete _p;
                _p = new T[num]{};
            }
            else
            {
                throw "The queue is not empty";
            }
        }
    }
    size_t size()
    {
        if(_end >= _head)return (_end - _head);
        else return (_capacity - _head + _end);
    }
    bool isoverflow() const { return _isoverflow; }
    bool isempty() const { return _isempty; }
    void notempty() {_isempty = false;}
    void notoverflow() {_isoverflow = false;}
private:
    volatile size_t _head;
    volatile size_t _end;
    T* _p;
    size_t _capacity;
    bool _isoverflow;
    bool _isempty;
    std::mutex _wm;
    std::mutex _rm;
};