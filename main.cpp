#include <iostream>       // std::cout, std::endl
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <vector>         // std::vector
#include <mutex>          // std::mutex

using namespace std;

#define N 5 /* numero de filosofos */
#define LEFT (i+N-1)%N-1 /* numero do filosofo a esquerda */
#define RIGHT (i+1)%N /* numero do filosofo a direita */
#define THINKING 0 /* o filosofo esta pensando */
#define HUNGRY 1 /* o filosofo esta faminto */
#define EATING 2 /* o filosofo esta comendo */

int state[N]; /* array para controlar o estado de cada filosofo */

typedef int semaphore; /* semaforos s~ao um tipo especial de int */
semaphore garfo[N];

mutex mtx;

void filosofo(int i);
void take_forks(int i);
void put_forks(int i);
void test(int i);
void thinking(int i);
void eating(int i);
void down(semaphore * mutex);
void up(semaphore * mutex);

int main() {
    cout << "Hello, World!" << endl;
    vector<std::thread> myThreads;
    for(int i = 0; i < N; i++){
        myThreads.push_back(thread(filosofo, i));
    }
    for (auto& th : myThreads) th.join();
    return 0;
}

void filosofo(int i) { /* i: o numero do filosofo, de 0 a N-1 */
    while(true) { /* repete para sempre */
        thinking(i); /* esta pensando */
        take_forks(i); /* pega os dois garfos ou fica bloqueado */
        eating(i); /* esta comendo */
        put_forks(i); /* devolve os dois garfos a mesa */
    }
}

void take_forks(int i) /* i: o numero do filosofo, de 0 a N-1 */
{
    mtx.lock(); /* entra na regi~ao crtica */
    state[i] = HUNGRY; /* registra que o filosofo esta faminto */
    test(i); /* tenta pegar os garfos */
    mtx.unlock(); /* sai da regi~ao crtica */
    down(&garfo[i]); /* bloqueia se os garfos n~ao foram pegos */
}

void put_forks(int i) /* i: o numero do filosofo, de 0 a N-1 */
{
    mtx.lock(); /* entra na regi~ao crtica */
    state[i] = THINKING; /* registra que o filosofo esta pensando */
    test(LEFT); /* v^e se o filosofo da esquerda pode comer agora */
    test(RIGHT); /* v^e se o filosofo da direita pode comer agora */
    mtx.unlock(); /* sai da regi~ao crtica */
}

void test(int i) /* i: o numero do filosofo, de 0 a N-1 */
{
    if(state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        up(&garfo[i]);
    }
}

void thinking(int i){

    this_thread::sleep_for (chrono::seconds(5));
}

void eating(int i){
    this_thread::sleep_for (chrono::seconds(2));
}

void down(semaphore * mutex){
    if(*mutex == 1)
        *mutex = 0;
    else{
        int try_again = rand() % 3 + 1;
        this_thread::sleep_for (chrono::seconds(try_again));
    }
}

void up(semaphore * mutex){

}