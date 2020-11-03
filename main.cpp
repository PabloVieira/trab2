#include <iostream>

#define N 5 /* numero de filosofos */
#define LEFT (i+N-1)%N-1 /* numero do filosofo a esquerda */
#define RIGHT (i+1)%N /* numero do filosofo a direita */
#define THINKING 0 /* o filosofo esta pensando */
#define HUNGRY 1 /* o filosofo esta faminto */
#define EATING 2 /* o filosofo esta comendo */

int state[N]; /* array para controlar o estado de cada filosofo */

typedef int semaphore; /* semaforos s~ao um tipo especial de int */
semaphore mutex; /* semaforo para controlar o acesso a regi~ao crtica */
semaphore s[N]; /* um semaforo para cada filosofo para sincronizac~ao */

void filosofo(int i);
void take_forks(int i);
void put_forks(int i);
void test(int i);

using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}

void filosofo(int i) { /* i: o numero do filosofo, de 0 a N-1 */
    while(true) { /* repete para sempre */
        thinking(i); /* esta pensando */
        take_forks(i); /* pega os dois garfos ou fica bloqueado */
        eating(i); /* esta comendo */
        put_forks(i); /* devolve os dois garfos a mesa */
    }
}

void take_forks(int i) /* i: o numero do filosofo, de 0 a N-1 */
{
    down(mutex); /* entra na regi~ao crtica */
    state[i] = HUNGRY; /* registra que o filosofo esta faminto */
    test(i); /* tenta pegar os garfos */
    up(mutex); /* sai da regi~ao crtica */
    down(s[i]); /* bloqueia se os garfos n~ao foram pegos */
}

void put_forks(int i) /* i: o numero do filosofo, de 0 a N-1 */
{
    down(&mutex); /* entra na regi~ao crtica */
    state[i] = THINKING; /* registra que o filosofo esta pensando */
    test(LEFT); /* v^e se o filosofo da esquerda pode comer agora */
    test(RIGHT); /* v^e se o filosofo da direita pode comer agora */
    up(&mutex); /* sai da regi~ao crtica */
}

void test(int i) /* i: o numero do filosofo, de 0 a N-1 */
{
    if(state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        up(&s[i]);
    }
}