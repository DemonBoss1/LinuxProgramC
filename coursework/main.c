#include "main.h"

int compare(const void * x1, const void * x2)                                   // функция сравнения элементов массива
{
  return ( *(int*)x1 - *(int*)x2 );                                             // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

int test(){
    int A[1000000];                                                             //Объявление массива
    srand(time(NULL));                                                          //Семя для рандомайзера
    for(int i = 0; i<1000000;i++)                                               //Цикл заполнения массива
        A[i] = rand() % 1000000;
    qsort(A,1000000,sizeof(int),compare);                                       //Сортировка массива
    //for(int i = 1; i!=0;i++);                                                   //Цикл длинной в размер int
}

int main(int argc, char *argv[]){
    pid_t childPid;                                                             //Объявление переменнной для ID процесса потомка
    clock_t t0,t1;                                                              //Объявление переменных начала и конца отсчета времени
    int error;                                                                  //Объявление переменной для выявления ошибки в функции nice()
    struct sched_param sp = {.sched_priority = 1};                              //param для функции sched_setscheduler()
    int ret;                                                                    //Объявление переменной для выявления ошибки в функции sched_setscheduler()
    printf("Nice  SCHED_OTHER  SCHED_FIFO   SCHED_RR\n");
    for(int i=-20;i<20;i++){                                                    //Перебор приоритетов для функции nice()
        //SCHED_OTHER
        t0 = clock();                                                           //Установление значения начала отсчета времени
        switch (childPid = fork()){                                             //Начало конструкции создания дочернего процесса с помощью fork()
            case -1:                                                            //Участок обратотки ошибки при вызове функции fork()
                perror("fork");                                                 //Обработка ошибки
                return -1;

            case 0:                                                             //Участок кода потомка процесса
                /*ret = sched_setscheduler(2,SCHED_OTHER,&sp);                    //Вызов функции sched_setscheduler()
                if(ret==-1){
                    perror("sched_setscheduler");                               //Обработка ошибки
                    return 0;
                }*/
                if(i!=-1){
                    error = nice(i);                                            //Установка проритета процесса
                    if (error == -1)perror("nice");                             //Обработка ошибки при вызове nice()
                } else {
                    error = nice(-2);                                           //Обработка особого случая функции nice()
                    if (error == -1)perror("nice");  
                    nice(i);
                }
                test();                                                         //Загрузка в память дочернего процесса программы для провеки зависимости времени от приоритета процесса в системе Linux
                exit(0);
            
            default:                                                            //Участок кода для родительского процесса
                wait(0);                                                        //Ожидание выполнения дочернего процесса, и функция удаляющая зомби процесс и освобождающая ресурсы
                t1 = clock();                                                   //Установления значения конца отсчета времени
                printf("%4d%13lf\n", i, (double)(t1 - t0) / CLOCKS_PER_SEC);      //Вывод в консоль зависимости приоритета и времени выполнения
                break;
        }
        //SCHED_FIFO
        t0 = clock();                                                           //Установление значения начала отсчета времени
        switch (childPid = fork()){                                             //Начало конструкции создания дочернего процесса с помощью fork()
            case -1:                                                            //Участок обратотки ошибки при вызове функции fork()
                perror("fork");                                                 //Обработка ошибки
                return -1;

            case 0:                                                             //Участок кода потомка процесса
                ret = sched_setscheduler(0,SCHED_FIFO,&sp);                     //Вызов функции sched_setscheduler()
                if(ret==-1){
                    perror("sched_setscheduler");                               //Обработка ошибки
                    return 0;
                }
                if(i!=-1){
                    error = nice(i);                                            //Установка проритета процесса
                    if (error == -1)perror("nice");                             //Обработка ошибки при вызове nice()
                } else {
                    error = nice(-2);                                           //Обработка особого случая функции nice()
                    if (error == -1)perror("nice");  
                    nice(i);
                }
                execve("./TestCode",NULL,NULL);                                 //Загрузка в память дочернего процесса программы для провеки зависимости времени от приоритета процесса в системе Linux
                exit(0);
            
            default:                                                            //Участок кода для родительского процесса
                wait(0);                                                        //Ожидание выполнения дочернего процесса, и функция удаляющая зомби процесс и освобождающая ресурсы
                t1 = clock();                                                   //Установления значения конца отсчета времени
                printf("%12lf",  (double)(t1 - t0) / CLOCKS_PER_SEC);           //Вывод в консоль зависимости приоритета и времени выполнения
                break;
        }
        //SCHED_RR
        t0 = clock();                                                           //Установление значения начала отсчета времени
        switch (childPid = fork()){                                             //Начало конструкции создания дочернего процесса с помощью fork()
            case -1:                                                            //Участок обратотки ошибки при вызове функции fork()
                perror("fork");                                                 //Обработка ошибки
                return -1;

            case 0:                                                             //Участок кода потомка процесса
                ret = sched_setscheduler(0,SCHED_RR,&sp);                       //Вызов функции sched_setscheduler()
                if(ret==-1){
                    perror("sched_setscheduler");                               //Обработка ошибки
                    return 0;
                }
                if(i!=-1){
                    error = nice(i);                                            //Установка проритета процесса
                    if (error == -1)perror("nice");                             //Обработка ошибки при вызове nice()
                } else {
                    error = nice(-2);                                           //Обработка особого случая функции nice()
                    if (error == -1)perror("nice");  
                    nice(i);
                }
                execve("./TestCode",NULL,NULL);                                 //Загрузка в память дочернего процесса программы для провеки зависимости времени от приоритета процесса в системе Linux
                exit(0);
            
            default:                                                            //Участок кода для родительского процесса
                wait(0);                                                        //Ожидание выполнения дочернего процесса, и функция удаляющая зомби процесс и освобождающая ресурсы
                t1 = clock();                                                   //Установления значения конца отсчета времени
                printf("%11lf\n",  (double)(t1 - t0) / CLOCKS_PER_SEC);         //Вывод в консоль зависимости приоритета и времени выполнения
                break;
        }
    }
    /*for(int i=1;i<100;i++){
        //SCHED_FIFO
        t0 = clock();                                                           //Установление значения начала отсчета времени
        switch (childPid = fork()){                                             //Начало конструкции создания дочернего процесса с помощью fork()
            case -1:                                                            //Участок обратотки ошибки при вызове функции fork()
                perror("fork");                                                 //Обработка ошибки
                return -1;

            case 0:                                                             //Участок кода потомка процесса
                ret = sched_setscheduler(0,SCHED_FIFO,&sp);                     //Вызов функции sched_setscheduler()
                if(ret==-1){
                    perror("sched_setscheduler");                               //Обработка ошибки
                    return 0;
                }
                test();                                                         //Загрузка в память дочернего процесса программы для провеки зависимости времени от приоритета процесса в системе Linux
                exit(0);
            
            default:                                                            //Участок кода для родительского процесса
                wait(0);                                                        //Ожидание выполнения дочернего процесса, и функция удаляющая зомби процесс и освобождающая ресурсы
                t1 = clock();                                                   //Установления значения конца отсчета времени
                printf("%4d%12lf",i,  (double)(t1 - t0) / CLOCKS_PER_SEC);           //Вывод в консоль зависимости приоритета и времени выполнения
                break;
        }
        //SCHED_RR
        t0 = clock();                                                           //Установление значения начала отсчета времени
        switch (childPid = fork()){                                             //Начало конструкции создания дочернего процесса с помощью fork()
            case -1:                                                            //Участок обратотки ошибки при вызове функции fork()
                perror("fork");                                                 //Обработка ошибки
                return -1;

            case 0:                                                             //Участок кода потомка процесса
                ret = sched_setscheduler(0,SCHED_RR,&sp);                       //Вызов функции sched_setscheduler()
                if(ret==-1){
                    perror("sched_setscheduler");                               //Обработка ошибки
                    return 0;
                }
                test();                                                         //Загрузка в память дочернего процесса программы для провеки зависимости времени от приоритета процесса в системе Linux
                exit(0);
            
            default:                                                            //Участок кода для родительского процесса
                wait(0);                                                        //Ожидание выполнения дочернего процесса, и функция удаляющая зомби процесс и освобождающая ресурсы
                t1 = clock();                                                   //Установления значения конца отсчета времени
                printf("%11lf\n",  (double)(t1 - t0) / CLOCKS_PER_SEC);         //Вывод в консоль зависимости приоритета и времени выполнения
                break;
        }
        sp.sched_priority++;
    }*/
}