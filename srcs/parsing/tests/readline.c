/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:01:36 by flima             #+#    #+#             */
/*   Updated: 2025/03/10 20:22:58 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char *str;
	char dir[1024];
	
	getcwd(dir, 1024);
    while (1)
    {
        // Solicita a entrada do usuário
        str = readline(dir);
        
        if (!str)
        {
            printf("\nExiting...\n");
            break;
        }

        // Se o comando for "erro", substitui a linha
        if (strcmp(str, "erro") == 0)
        {
            // Substitui a linha com uma sugestão e não reinicia a entrada
            rl_replace_line("suggested_command", 1);
            rl_redisplay();
        }
        // Se o comando for "hel", substitui por "hello"
        else if (strcmp(str, "hel") == 0)
        {
            rl_replace_line("hello", 1);
            rl_redisplay();
        }
        else
        {
            // Caso contrário, apenas imprime o que foi digitado
            printf("You entered: %s\n", str);
        }

        // Adiciona a entrada ao histórico, independente de substituição ou não
        add_history(str);
		

        // Libera a memória alocada para a entrada
        free(str);
    }
	rl_clear_history();
	str = readline("minishell> ");
    return 0;
}



