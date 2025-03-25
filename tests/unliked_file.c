#include <stdio.h>
#include <unistd.h>
# include <fcntl.h>

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	int fd;
	char *tmp_file = "/tmp/heredoc_tmp.txt";
	char str[10] = {0};  // Inicializa o buffer

	fd = open(tmp_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Erro ao abrir o arquivo");
		return (1);
	}
	unlink(tmp_file);
	write(fd, "hello", 6);  // Escreve "hello" no arquivo

	// Reposiciona o cursor para o início do arquivo antes de ler
	lseek(fd, 0, SEEK_SET);

	read(fd, str, 6);  // Agora a leitura ocorre do início do arquivo
	printf("%s\n", str);

	close(fd);  // Fecha o arquivo
	return (0);
}
