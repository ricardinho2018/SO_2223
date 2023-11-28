#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFSIZE 1024

// função para obter o timestamp em milissegundos
long long current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL);
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
    return milliseconds;
}

int main(int argc, char *argv[]) {
    // verificar argumentos
    if (argc < 3) {
        fprintf(stderr, "Uso: %s -u programa [argumentos]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    // obter nome do programa e argumentos
    char *programa = argv[2];
    char **argumentos = &argv[2];
    // obter PID
    pid_t pid = getpid();
    // obter timestamp antes da execução
    long long timestamp_inicio = current_timestamp();
    // notificar servidor
    printf("Notificando servidor: PID=%d, programa=%s, timestamp_inicio=%lld\n", pid, programa, timestamp_inicio);
    // executar programa
    if (execvp(programa, argumentos) == -1) {
        fprintf(stderr, "Erro ao executar o programa %s\n", programa);
        exit(EXIT_FAILURE);
    }
    // obter timestamp após a execução
    long long timestamp_fim = current_timestamp();
    // notificar servidor
    printf("Notificando servidor: PID=%d, timestamp_fim=%lld\n", pid, timestamp_fim);
    // calcular tempo de execução
    long long tempo_execucao = timestamp_fim - timestamp_inicio;
    // notificar utilizador
    printf("Programa executado com sucesso. PID=%d, tempo de execução=%lldms\n", pid, tempo_execucao);
    return 0;
}
