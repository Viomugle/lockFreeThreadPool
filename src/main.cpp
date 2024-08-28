#include <iostream>
#include <functional>
#include "scsp.hpp"
#include <thread>
#include <cstdlib>
#include <atomic>
#include "worker.hpp"
#include "threadpool.hpp"
constexpr int MAX=100000;
using namespace std;





void task(int i)
{
    printf("task %d: %.3f%%\n",i,100.0f*i/MAX);
    fflush(stdout);
}



void add(threadpool& p)
{
    for(int i=0;i<MAX;i++)
    {
        p.addTask(bind(task,i));
    }
    p.close();
}


int main(int argc, char** argv)

{
    threadpool p(8);
    thread t1(add,ref(p));
    t1.join();
    cout<<"main exit: "<<this_thread::get_id()<<endl;
    return 0;
}
