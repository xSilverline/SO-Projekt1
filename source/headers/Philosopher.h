//
// Created by Silver on 27.03.2025.
//

#ifndef PROJEKT1_PHILOSOPHER_H
#define PROJEKT1_PHILOSOPHER_H

#include <thread>
#include <mutex>
#include <vector>
#include <memory>
#include <iostream>
#include <random>
#include <windows.h>
#include <semaphore>

using namespace std;



class Philosopher{

    public:

        static vector<unique_ptr<mutex>>  forkList;
        static mutex output;
        static vector<bool> forkDirty;
        static vector<bool> hasLeftFork;
        static vector<bool> hasRightFork;
        static vector<unique_ptr<binary_semaphore>> forkSem;

        Philosopher(int index, int n);
        void start();
    private:


        int id;
        int leftFork;
        int rightFork;
        int leftNeighbour;
        int rightNeighbour;
//        bool hasLeftFork;
//        bool hasRightFork;


        void eating();
        void thinking();
        void waiting_for_forks();
        void releasing_forks();
        void request_fork(int id);


};


#endif //PROJEKT1_PHILOSOPHER_H
