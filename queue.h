#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include <iostream>
#include<stdlib.h>

using namespace std;

const int MaxQSize = 1000;

template<class T>
class Queue
{
private:
    //queue array and its parameters
    int front,rear, count;
    T qlist[MaxQSize];

public:
    // constructor
    Queue(void);//initialize data members
    // some modification ops
    void QInsert(const T& item);
    T QDelete(void);
    void ClearQueue(void);
    // queue access
    T QFront(void) const;
    //queue test methods
    int QLength(void) const;
    int QEmpty(void) const;
    int QFull(void) const;
};

//queue constructor
// initialize front rear count
template<class T>

Queue<T>::Queue(void):front(0),rear(0),count(0)
{}

//Q ops
//q insert : insert them into the queue
template<class T>
void Queue<T>::QInsert(const T&item)
{
    //terminate is queue is full
    if(count==MaxQSize)
    {
        cerr<<"Queue Overflow"<<endl;
        exit(1);
    }
//increment count , assign item to qList and update rear
    count ++;
    qlist[rear] = item;
    rear = (rear +1)%MaxQSize;
}

//QDelete : delete element from the front
//of the queue and return its value
template<class T>
T Queue<T>::QDelete(void)
{
    T temp;
    // if qlist is empty, terminate the program
    if(count == 0)
    {
        cerr<<"Deleting from an empty queue..."<<endl;
    }

    //record value at the front of the queue
    temp = qlist[front];
    //decrement count, advance front and return former front
    count--;
    front = (front +1)%MaxQSize;
    return temp;
}
template<class T>
int Queue<T>::QEmpty(void) const
{
    if(count == 0)
        return 1;
    else return 0;
}

template<class T>
T Queue<T>::QFront(void) const
{
    return qlist[front];
}


#endif // QUEUE_H_INCLUDED
