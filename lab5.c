#include "main_header.h"

void goodbye(void){
    printf("Goodbye parent\n");
}

void Ex_5_1(){
    pid_t childPid;
    int status;
    switch (childPid = fork()) {
        case -1:
            perror("fork");
            exit -1;
        case 0:
            printf("This is child\n");
            if (atexit(goodbye) != 0) {
                perror("atexit 1");
            }
            break;
        default:
            printf("This is parent\n");
            wait(&status);
            printf("Child status = %d\n",status);
            break;
    }
    exit(EXIT_SUCCESS);
}
void Ex_5_6(){
    char cmd[4096];
    pid_t child_pid;
    printf("Parent PID=%ld\n", (long)getpid());
    switch (child_pid = fork()) {
        case -1:
            // Обработка ошибки
            perror("fork");
            break;
        case 0:
            /* Потомок , который должен немедленно завершится */
            /* Не забудьте получить PID child_pid */
            exit(0);
        default:
            /* Родитель */
            /* Немного нужно подождать ^.^ */
            /* Немного нужно подождать и еще немного ... */
            /* Подожди еще ... sleep() sleep() */
            sleep(5);

            /* Загляни в PS, что там по потомку */
            /* Изучи системный вызов system() для того, чтобы заглянуть в ps */
            /* Для формирования команды нужно завести буфер cmd */
            char cmd[] = "ps";
            system(cmd);
            sleep(2);

            /* ?? И использовать snprintf() ?? */
            printf("\n");

            /* Может нужно отправить child сигнал завершения */
            /* Отправил, посмотри, что произошло */
            /* Отправить сигнал можно системным вызовом kill() */
            /* Я это делаю так kill(child_pid, SIGKILL) */
            kill(child_pid, SIGKILL);
            system(cmd);
            sleep(2);
            printf("\n");

            /* Не забудь проверить ошибки */
            /* Не убивается child так и висит в PS */
            /* Беда... */
            /* Сделай waitpid() */
            waitpid(child_pid,0,WNOHANG);

            /* Посмотри снова в PS */
            system(cmd);
    }
}
void Ex_5_7(char *argv[]){
    pid_t childPid;
    char* pathname = "ArgPrint";
    argv[0]=pathname;
    switch (childPid = fork()) {
        case -1:
            perror("fork");
            exit -1;
        case 0:
            if (execve("./ArgPrint",argv,NULL)) {
                perror("execve");
            }
            break;
        default:
            printf("Parent wait child\n");
            sleep(2);
            wait(0);
            break;
    }
    exit(EXIT_SUCCESS);
}