/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_stdout.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:01:12 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/23 16:01:21 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

//int	main(void)
//{
//    int fd = open("teste.txt", O_WRONLY | O_CREAT | O_TRUNC , 0777);
//    if (fd == -1)
//        return (1);

//    printf("Fd do arquivo test = %d\n", fd);
//    int fd2 = dup2(fd, 1);
//    close(fd);
//    printf("aaaaa\n");
//    return(0);
//}
