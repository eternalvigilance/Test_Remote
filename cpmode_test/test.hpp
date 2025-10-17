#include<thread>
#include<iostream>
#include<mutex>
#include<random>
#include<condition_variable>
class circular_queue
{
public:
    circular_queue(size_t num = 1024):_head(0),_end(0),_capacity(num),_isoverflow(false),_isempty(false)
    {_p = new size_t[num]{};}
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
    size_t pop()
    {
        size_t re = _p[_head];
        _head = (_head + 1)%_capacity;
        if(_head==_end)_isempty = true;
        return re;
    }
    size_t size()
    {
        if(_end >= _head)return (_end - _head);
        else return (_capacity - _head + _end);
    }
    bool isoverflow() const { return _isoverflow; }
    bool isempty() const { return _isempty; }
private:
    volatile size_t _head;
    volatile size_t _end;
    size_t* _p;
    size_t _capacity;
    bool _isoverflow;
    bool _isempty;
    std::mutex _wm;
};
#define Max_rand 100
#define Min_rand 0
size_t myrand()
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(Min_rand,Max_rand);
    return dist(gen);
}
void twrite(circular_queue& cq)
{
    while(1)if(cq.isoverflow()==false)cq.insert(myrand());
}
static size_t times = 1;
static int turn = 0;
std::mutex mu;
std::condition_variable cv;
void tread(circular_queue& cq,int id)
{
    while(1)
    {
        std::unique_lock<std::mutex> lck(mu);
        cv.wait(lck,[id]{return (id==turn);});
        if(cq.isempty()==false)
        {
            std::cout << "Read thread" << id << "get the number:" << cq.pop() <<". And the time is" << times << std::endl;
            ++times;
            turn = (turn+1)%2;
            lck.unlock();
            cv.notify_all();
        }
    }
}
void test()
{
    //std::cout << rand() << std::endl;
    circular_queue cq;
    std::thread wt1(twrite,std::ref(cq));
    std::thread wt2(twrite,std::ref(cq));
    std::thread rt0(tread,std::ref(cq),(int)0);
    std::thread rt1(tread,std::ref(cq),(int)1);
    wt1.join();
    wt2.join();
    rt0.join();
    rt1.join();
}