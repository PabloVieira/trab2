#include <iostream>
#include <iostream>       // std::cout, std::endl
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

using namespace std;

#define N 5 /* numero de filosofos */
#define LEFT (i+N-1)%N-1 /* numero do filosofo a esquerda */
#define RIGHT (i+1)%N /* numero do filosofo a direita */
#define THINKING 0 /* o filosofo esta pensando */
#define HUNGRY 1 /* o filosofo esta faminto */
#define EATING 2 /* o filosofo esta comendo */

int state[N]; /* array para controlar o estado de cada filosofo */

typedef int semaphore; /* semaforos s~ao um tipo especial de int */
semaphore mutex; /* semaforo para controlar o acesso a regi~ao crtica */
semaphore s[N]; /* um semaforo para cada filosofo para sincronizac~ao */

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
    down(&mutex); /* entra na regi~ao crtica */
    state[i] = HUNGRY; /* registra que o filosofo esta faminto */
    test(i); /* tenta pegar os garfos */
    up(&mutex); /* sai da regi~ao crtica */
    down(&s[i]); /* bloqueia se os garfos n~ao foram pegos */
}

void put_forks(int i) /* i: o numero do filosofo, de 0 a N-1 */
{
    down(&mutex); /* entra na regi~ao crtica */
    state[i] = THINKING; /* registra que o filosofo esta pensando */
    test(LEFT); /* v^e se o filosofo da esquerda pode comer agora */
    test(RIGHT); /* v^e se o filosofo da direita pode comer agora */
    up(&mutex); /* sai da regi~ao crtica */
}

void test(int i) /* i: o numero do filosofo, de 0 a N-1 */
{
    if(state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        up(&s[i]);
    }
}

void thinking(int i){

}

void eating(int i){

}

void down(semaphore * mutex){

}

void up(semaphore * mutex){

}