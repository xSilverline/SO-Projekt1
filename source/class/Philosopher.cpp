// Copyright 2025 Marcin Musielski

#include "../headers/Philosopher.h"

default_random_engine generator(
        chrono::system_clock::now().time_since_epoch().count());
std::uniform_int_distribution<int> dist(1000, 3000);

Philosopher::Philosopher(int index, int n) {
        id = index;
        leftFork = id;
        rightFork = (id+1)%n;
        leftNeighbour = (id+n-1)%n;
        rightNeighbour = (id+1)%n;

        if (id < rightFork) {
            forkSem[id] -> acquire();
            hasLeftFork[id] = true;
        }

        if (id == 0) {
            forkSem[n-1] -> acquire();
            hasRightFork[id] = true;
        }
}

void Philosopher::start() {
    while (true) {
        thinking();
        waiting_for_forks();
        eating();
        releasing_forks();
    }
}

void Philosopher::eating() const {
    {
        lock_guard<std::mutex> lock(output);
        cout << "Filozof " << id << " je" << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(dist(generator)));
}

void Philosopher::thinking() const {
    {
        lock_guard<std::mutex> lock(output);
        cout << "Filozof " << id << " myśli" << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(dist(generator)));
}

void Philosopher::waiting_for_forks() {
    {
        lock_guard<std::mutex> lock(output);
        cout << "Filozof " << id << " czeka na widelce" << endl;
    }
    if (!hasLeftFork[id]) {
        request_fork(leftFork);
        hasLeftFork[id] = true;
    }
    if (!hasRightFork[id]) {
        request_fork(rightFork);
        hasRightFork[id] = true;
    }
}

void Philosopher::releasing_forks() const {
    {
        lock_guard<std::mutex> lock(output);
        cout << "Filozof " << id << " oddaje widelce" << endl;
    }
    forkSem[rightFork]->release();
    hasRightFork[id] = false;
    forkDirty[rightFork] = true;

    forkSem[leftFork]->release();
    hasLeftFork[id] = false;
    forkDirty[leftFork] = true;
}

void Philosopher::request_fork(int forkid) const {
    if (forkDirty[forkid]) {
        forkSem[forkid] ->release();
        if (forkid == leftFork) {
            hasRightFork[leftNeighbour] = false;
        } else if (forkid == rightFork) {
            hasLeftFork[rightNeighbour] = false;
        }
    }

    forkSem[forkid] -> acquire();
    forkDirty[forkid] = false;
}
