//
// Created by Silver on 27.03.2025.
//


#include "../headers/Philosopher.h"

default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
std::uniform_int_distribution<int> dist(1000, 3000);

Philosopher::Philosopher(int index, int n)
{
        id = index;
        leftFork = id;
        rightFork = (id+1)%n;

        if(id<rightFork)
            forkStatus[leftFork] = true;

        cout<<id<<"\t"<<leftFork<<"\t"<<rightFork<<"\t"<<forkStatus[leftFork]<<endl;
}

void Philosopher::start()
{
    while(true)
    {
            thinking();
            waiting_for_fork();
            eating();
            releasing_forks();
    }

}



void Philosopher::eating()
{
    {
        lock_guard<std::mutex> lock(output);
        cout<<"Filozof "<<id<<" je"<<endl;
    }
    this_thread::sleep_for(chrono::milliseconds(dist(generator)));
}

void Philosopher::thinking()
{
    {
        lock_guard<std::mutex> lock(output);
        cout<<"Filozof "<<id<<" myśli"<<endl;
    }
    this_thread::sleep_for(chrono::milliseconds(dist(generator)));

}

void Philosopher::waiting_for_fork()
{
    {
        lock_guard<std::mutex> lock(output);
        cout<<"Filozof "<<id<<" czeka na widelce"<<endl;
    }

    if(!forkStatus[leftFork])
    {
        requestFork[leftFork] = true;

        while(!forkStatus[leftFork])
        {
            // just wait, be patient :)
        }
    }
    forkList[leftFork]->lock();


    if(!forkStatus[rightFork])
    {
        requestFork[rightFork] = true;

        while(!forkStatus[rightFork])
        {
            // just wait, be patient :)
        }
    }
    forkList[rightFork]->lock();


}

void Philosopher::releasing_forks()
{
    {
        lock_guard<std::mutex> lock(output);
        cout<<"Filozof "<<id<<" oddaje widelce"<<endl;
    }

    forkList[leftFork]->unlock();
    forkStatus[leftFork] = false;
    if(requestFork[leftFork])
    {
        forkStatus[leftFork] = true;
        requestFork[leftFork] = false;
    }

    forkList[rightFork]->unlock();
    forkStatus[rightFork] = false;
    if(requestFork[rightFork])
    {
        forkStatus[rightFork] = true;
        requestFork[rightFork] = false;
    }


}


