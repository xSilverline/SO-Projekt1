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

using namespace std;



class Philosopher{

    public:

        static vector<unique_ptr<mutex>>  forkList;
        static mutex output;
        static vector<bool> forkStatus;
        static vector<bool> requestFork;

        Philosopher(int index, int n);
        void start();
    private:


        int id;
        int leftFork;
        int rightFork;

        void eating();
        void thinking();
        void waiting_for_fork();
        void releasing_forks();


};


#endif //PROJEKT1_PHILOSOPHER_H
