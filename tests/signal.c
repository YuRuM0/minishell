# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
#include <signal.h>
#include <unistd.h>


// void	handle_signal(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	// rl_redisplay();
// }

static void sigint_handler(int sig)
{
	write(1, "\n", 1);
	write(STDOUT_FILENO, "SIGINT recebido, processando...\n", 32);
	sleep(5); // Simulando algum trabalho com o arquivo
	write(1, "opaaa\n", 6);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void init_signals()
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));    // Zera a estrutura
	act.sa_handler = sigint_handler;  // Define o handler para SIGINT
	sigemptyset(&act.sa_mask);       // Limpa a máscara (não bloqueará sinais)
	// sigaddset(&act.sa_mask, SIGINT); // Bloqueia SIGINT enquanto o handler está rodando
	sigaction(SIGINT, &act, NULL);    // Aplica o sigaction para SIGINT
}

int	main(void)
{
	char *str;
	while (1)
	{
		init_signals();
		str = readline("$:");
		if (str == NULL)
			break ;
		printf("%s\n", str);
	}
	return (0);
}

