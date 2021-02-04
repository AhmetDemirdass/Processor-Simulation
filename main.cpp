#include <iostream>
#include<stdlib.h>
#include"stack.h"
#include"queue.h"
#include <fstream> // file streams

using namespace std;

class Process
{
private:
    //The parameters ProcessID,RunTime,Priority, ArrivalTime are created as public to change their value in a member function.


public:
    int ProcessID;
    int RunTime;
    int Priority;
    int ArrivalTime;

    void ProcessInit(int ProcessID, int RunTime, int Priority, int ArrivalTime);//member function to assign values to the member variables
    Process(void);//constructor to handle the initializations
    //process will start to execute and runtime starts to decrease.
};

Process::Process(void)
{
    ProcessID = -1;//when no Running_Process the ID of the process is -1.
    RunTime = 0;
    Priority = 0;
    ArrivalTime = 0;
}


void Process::ProcessInit(int pID, int rTime, int priority, int ArTime)
{
    ProcessID=pID;
    RunTime=rTime;
    Priority=priority;
    ArrivalTime=ArTime;
}



int main()
{
    int pID, priority, arrTime, runTime,latency;//pID, priority, arrTime and runTime are the input variable to read from the input.txt. Latency will be calculated in the following parts.
    int i=0;
    int ID[50];//array to keep the values of object processes' ID
    int At[50];//array to keep the values of object processes' Arrival Time
    int Rt[50];//array to keep the values of object processes' Run Time
    int Pri[50];//array to keep the values of object processes' Priority
    int Cycle=0;//the counter having the value of the process time.
    Process Running_Process;//object of class Process showing the current process in execution
    Process Next_Proc;//object of class Process showing the following process in execution

    Stack<Process> S1; // Stack to store the preempted process
    Queue<Process> Q1; // Q1 to store the arriving process with Priority=1.
    Queue<Process> Q2; // Q2 to store the arriving process with Priority=2.
    Queue<Process> Q3; // Q3 to store the arriving process with Priority=3.

    ifstream infile; // input file stream
    ofstream outfile; // output file stream
    ofstream Latency; // output file stream showing the latencies of the processes in the finish order.

    infile.open("input.txt"); // input file is input.txt
    Latency.open("Latency.txt");
    outfile.open("output.txt");

    while(!infile.eof())//in this while loop all the process inputs are stored in the arrays specifically designated to each one.
    { // continue while input file has unread text
    infile >> pID >> priority >> arrTime >> runTime; // read input like cin
    ID[i]=pID;
    At[i]=arrTime;
    Rt[i]=runTime;
    Pri[i]= priority;
    //Proc[i].ProcessReg(pID,priority,arrTime,runTime);
    i++;
    }

    infile.close();
    i=0;


    while(Running_Process.ProcessID==-1)//in this while loop the processor is waiting for the first input
    {
        Running_Process.ProcessInit(ID[i],Rt[i],Pri[i],At[i]);//start the process of ID[0] with its parameters ID, RunTime,Priority,Arrival Time to record.
        outfile <<" at t="<<Cycle<<" P"<<Running_Process.ProcessID<<" starts to execute"<<endl;
        Cycle++;//cycle is incremented
        Running_Process.RunTime--; //RunTime is decremented
    }



    while(Running_Process.ProcessID != -1)//in this while loop system is in processing state.
    {
        if(Running_Process.RunTime>0&&Next_Proc.ProcessID==-1)//if next process has not come yet, Run Time of the running process is decremented and cycle is incremented
        {
            Running_Process.RunTime--;

            Cycle++;
        }
        if(Running_Process.RunTime>0&&At[i+1]==Cycle)//if next input comes, i is incremented to construct the next process.
        {

            i++;

            Next_Proc.ProcessInit(ID[i],Rt[i],Pri[i],At[i]);

            if((Running_Process.Priority<=Next_Proc.Priority)||(!Q1.QEmpty())||(!Q2.QEmpty()&&Next_Proc.Priority>=2)||(!Q3.QEmpty()&&Next_Proc.Priority==3))
                //here it is controlled whether any process is stored in queue or stack.
                //If there are any processes in the system (in the queues, on the stack or in execution) with a higher or equal priority, Pi is inserted in Qi.
            {
                switch(Next_Proc.Priority)
                {
                case 1:
                    Q1.QInsert(Next_Proc);
                    outfile<<" at t="<<Cycle<<" P"<<Next_Proc.ProcessID<<" "<<"inserted to Q1"<<endl;
                    Next_Proc.ProcessInit(-1,0,0,0);
                    break;
                case 2:
                    Q2.QInsert(Next_Proc);
                    outfile<<" at t="<<Cycle<<" P"<<Next_Proc.ProcessID<<" "<<"inserted to Q2"<<endl;
                    Next_Proc.ProcessInit(-1,0,0,0);
                    break;
                case 3:
                    Q3.QInsert(Next_Proc);
                    outfile<<" at t="<<Cycle<<" P"<<Next_Proc.ProcessID<<" "<<"inserted to Q3"<<endl;
                    Next_Proc.ProcessInit(-1,0,0,0);
                    break;
                }

            }
            else
            {
                S1.push(Running_Process);
                outfile<<" at t="<<Cycle<<" P"<<Running_Process.ProcessID<<" "<<"pushed to Stack"<<endl;
                Running_Process.ProcessInit(ID[i],Rt[i],Pri[i],At[i]);
                Next_Proc.ProcessInit(-1,0,0,0);

            }


        }

        if(Running_Process.RunTime==0) // here when the processor finishes the execution of a process, it selects
            //the highest priority process in the system as the next process to execute.
            //If there are two highest priority processes, it selects the older one.
        {

            latency = Cycle-Running_Process.ArrivalTime;
            Latency <<"Latency for P" << Running_Process.ProcessID << " is "   << latency<< endl; // write output like cout

            if(!Q1.QEmpty())//if any process in Q1 exists, it will be selected as the new running process directly.
            {
                Running_Process.ProcessInit(Q1.QFront().ProcessID,Q1.QFront().RunTime,Q1.QFront().Priority,Q1.QFront().ArrivalTime);
                outfile<<" at t="<<Cycle<<" P"<<Running_Process.ProcessID<<" "<<"selected from Q1"<<endl;
                Q1.QDelete();

            }
            else if(!Q2.QEmpty()&&S1.StackEmpty())//if Q2 is not empty and the stack is empty,the process in Q2 will be selected as the new running process directly.
            {
                Running_Process.ProcessInit(Q2.QFront().ProcessID,Q2.QFront().RunTime,Q2.QFront().Priority,Q2.QFront().ArrivalTime);
                outfile<<" at t="<<Cycle<<" P"<<Running_Process.ProcessID<<" "<<"selected from Q2"<<endl;
                Q2.QDelete();

            }
            else if(!Q2.QEmpty()&&!S1.StackEmpty())//if Q2 is not empty and the stack is also not empty,the process in Q2 will be selected as the new running
                //process directly, if its priority is higher than the process' in stack. If they have same priority, the one with less arrival time is put as
                //new process.
            {
                if(S1.Peek().Priority<Q2.QFront().Priority)
                {
                    Running_Process.ProcessInit(S1.Peek().ProcessID,S1.Peek().RunTime,S1.Peek().Priority,S1.Peek().ArrivalTime);
                    outfile<<" at t="<<Cycle<<" P"<<Running_Process.ProcessID<<" "<<"popped from S1 with RunTime "<<Running_Process.RunTime<<endl;;
                    S1.pop();

                }
                else if(S1.Peek().Priority==Q2.QFront().Priority)
                {
                    if(S1.Peek().ArrivalTime<Q2.QFront().ArrivalTime)
                    {
                        Running_Process.ProcessInit(S1.Peek().ProcessID,S1.Peek().RunTime,S1.Peek().Priority,S1.Peek().ArrivalTime);
                        outfile<<" at t="<<Cycle<<" P"<<Running_Process.ProcessID<<" "<<"popped from S1 with RunTime "<<Running_Process.RunTime<<endl;
                        S1.pop();

                    }
                    else
                    {
                        Running_Process.ProcessInit(Q2.QFront().ProcessID,Q2.QFront().RunTime,Q2.QFront().Priority,Q2.QFront().ArrivalTime);
                        outfile<<" at t="<<Cycle<<" P"<<Running_Process.ProcessID<<" "<<"selected from Q2"<<endl;
                        Q2.QDelete();

                    }

                }
                else if(S1.Peek().Priority>Q2.QFront().Priority)
                {
                    Running_Process.ProcessInit(Q2.QFront().ProcessID,Q2.QFront().RunTime,Q2.QFront().Priority,Q2.QFront().ArrivalTime);
                    outfile<<" at t="<<Cycle<<" P"<<Running_Process.ProcessID<<" "<<"selected from Q2"<<endl;
                    Q2.QDelete();
                }
            }
            else if(!Q3.QEmpty()&&S1.StackEmpty())//if Q3 is not empty and the stack is empty,the process in Q3 will be selected as the new running process directly.
            {
                Running_Process.ProcessInit(Q3.QFront().ProcessID,Q3.QFront().RunTime,Q3.QFront().Priority,Q3.QFront().ArrivalTime);
                outfile<<" at t="<<Cycle<<" P"<<Running_Process.ProcessID<<" "<<"selected from Q3"<<endl;
                Q3.QDelete();
            }
            else if(!Q3.QEmpty()&&!S1.StackEmpty())//if Q3 is not empty and the stack is also not empty, the one with less arrival time is put as
                //new process.
            {
                    if(S1.Peek().ArrivalTime<Q3.QFront().ArrivalTime)
                    {
                        Running_Process.ProcessInit(S1.Peek().ProcessID,S1.Peek().RunTime,S1.Peek().Priority,S1.Peek().ArrivalTime);
                        outfile<<" at t="<<Cycle<<" P"<<Running_Process.ProcessID<<" "<<"popped from S1 with RunTime "<<Running_Process.RunTime<<endl;
                        S1.pop();
                    }
                    else
                    {
                        Running_Process.ProcessInit(Q3.QFront().ProcessID,Q3.QFront().RunTime,Q3.QFront().Priority,Q3.QFront().ArrivalTime);
                        outfile<<" at t="<<Cycle<<" P"<<Running_Process.ProcessID<<" "<<"selected from Q3"<<endl;
                        Q3.QDelete();
                    }
            }
            else Running_Process.ProcessInit(-1,0,0,0);

            Next_Proc.ProcessInit(-1,0,0,0);


        }

    Cycle++;
    Running_Process.RunTime--;

    }

}



 // close the files





























