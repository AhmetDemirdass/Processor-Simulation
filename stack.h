#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <iostream>
#include<stdlib.h>

using namespace std;

const int MaxSize=2;
template <class T>
class Stack
{
private:
    T stacklist[MaxSize];
    int top;

public:
    Stack(void);//constructor to initialize top
    //some modification ops
    T pop(void);
    void push(const T& item);
    void clearStack(void);
    //so as to check top item copy it. By adding const, we cannot make any change on data members.
    T Peek(void) const;
    //to check stack state returns top element value without removal
    int StackEmpty(void) const;
    //returns true if the stack is empty
    int StackFull(void) const;
    //returns true if the stack is full

};

template <class T>
Stack<T>::Stack(void):top(-1)
{}//top is initialized as -1

template <class T>
T Stack<T>::pop(void)
{
    T temp;
    if(top==-1)// is stack empty nothing to pop
    {
        cerr<<"Stack empty"<<endl;
        exit(1);
    }
    //record the top element
    temp = stacklist[top];

    // decrement top and return the earlier top element
    top--;
    return temp;
}

template <class T>
void Stack<T>::push(const T& item)
{

    if(top == MaxSize-1)//can not push if stack has exceeded its limits
    {

        cout<<"Stack Overflow"<<endl;
        exit(1);
    }
    // increment top ptr and copy item into list
    top ++;
    stacklist[top] =item;
}

//void Stack::clearStack(void):top(-1)

template<class T>
int Stack<T>::StackEmpty(void) const
{
    if (top==-1) return(1);
    else return(0);

}
template<class T>
int Stack<T>::StackFull(void) const
{
    if (top==MaxSize-1) return(1);
    else return(0);

}

template<class T>
T Stack<T>::Peek(void) const
{
    return stacklist[top];
}


#endif // STACK_H_INCLUDED
