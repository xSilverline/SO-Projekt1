// Copyright 2025 Marcin Musielski

#include "../headers/Philosopher.h"

vector<unique_ptr<mutex>> Philosopher::forkList;
vector<bool> Philosopher::forkDirty;
vector<unique_ptr<binary_semaphore>> Philosopher::forkSem;
mutex Philosopher::output;
vector<bool> Philosopher::hasLeftFork;
vector<bool> Philosopher::hasRightFork;

int main(int argc, char* argv[]) {
    vector<thread> philosophers;
    vector<Philosopher> philosopher;
    SetConsoleOutputCP(65001);
    int numberOfPhilosophers = 0;
    bool dataFlag = false;

    cout << "Problem Jedzących Filozofów" << endl << endl;

    if (argc > 1) {
        numberOfPhilosophers = stoi(argv[1]);
        if (numberOfPhilosophers <= 1) {
            cout << "Wczytano niepoprawną liczbę filozofów - wymaganych min. 2 !" << endl << endl;
            dataFlag = true;
        }
    } else {
        cout << "Nie wykryto argumentu wejściowego" << endl << endl;
        dataFlag = true;
    }

    if (dataFlag) {
        while (numberOfPhilosophers <= 0) {
            cout << "Podaj liczbę filozofów: ";
            cin >> numberOfPhilosophers;

            if (numberOfPhilosophers <= 0) {
                cout << endl <<
                     "Niepoprawna liczba filozofów! Powinna być większa od 0"
                     << endl << endl;
            }
        }
    }

    Philosopher::forkDirty.resize(numberOfPhilosophers, true);
    Philosopher::hasLeftFork.resize(numberOfPhilosophers, false);
    Philosopher::hasRightFork.resize(numberOfPhilosophers, false);
    Philosopher::forkSem.resize(numberOfPhilosophers);

    Philosopher::forkList.clear();
    for (int i = 0; i < numberOfPhilosophers; i++) {
        Philosopher::forkList.push_back(std::make_unique<std::mutex>());
    }

    Philosopher::forkSem.clear();
    for (int i = 0; i < numberOfPhilosophers; i++) {
        Philosopher::forkSem.push_back(
                std::make_unique<std::binary_semaphore>(1));
    }


    for (int i = 0; i < numberOfPhilosophers; i++) {
        philosopher.emplace_back(i, numberOfPhilosophers);
    }

    for (int i = 0; i < numberOfPhilosophers; i++) {
        philosophers.emplace_back(&Philosopher::start, &philosopher[i]);
    }

    for (auto& p : philosophers) {
        p.join();
    }
    return 0;
}
