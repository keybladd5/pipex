#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "libft/libft.h"

int main(int argc, char *argv[], char *envp[])
{
    if (argc != 5)
    {
        perror("Número incorrecto de argumentos\n");
        return 1;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("Error en pipe\n");
        return 1;
    }

    int pid1 = fork();
    if (pid1 == 0)
    {
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
            perror("Error al abrir el archivo en el primer hijo\n");
            exit(1);
        }

        dup2(fd, 0);
        dup2(pipefd[1], 1);

        close(fd);
        close(pipefd[0]);
        close(pipefd[1]);

        char *arg = ft_strjoin("/bin/", argv[2]);
        ft_printf("Ejecutando: %s %s %s\n", arg, argv[2], NULL);
        if (execve(arg, argv + 2, NULL) == -1)
        {
            perror("ERROR en EXECVE hijo\n");
            exit(1);
        }
    }

    int pid2 = fork();
    if (pid2 == 0)
    {
        int fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd2 == -1)
        {
            perror("Error al abrir el archivo en el segundo hijo\n");
            exit(1);
        }

        dup2(pipefd[0], 0);
        dup2(fd2, 1);

        close(fd2);
        close(pipefd[0]);
        close(pipefd[1]);

        char *arg2 = ft_strjoin("/usr/bin/", argv[3]);
        ft_printf("Ejecutando: %s %s %s\n", arg2, argv[3], NULL);
        if (execve(arg2, argv + 3, NULL) == -1)
        {
            perror("ERROR en EXECVE padre\n");
            exit(1);
        }
    }

    close(pipefd[0]);
    close(pipefd[1]);

    int status;
    waitpid(pid1, NULL, 0);
    waitpid(pid2, &status, 0);

    if (WIFEXITED(status))
        return WEXITSTATUS(status);

    return 1;
}

