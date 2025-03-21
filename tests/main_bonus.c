/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:47:42 by acosi             #+#    #+#             */
/*   Updated: 2025/03/21 20:06:28 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RESET "\033[0m"


int main(void)
{
	int		fd1, fd2;
	char	*line1, *line2;
	int		i = 0;

	fd1 = open("testfile.txt", O_RDONLY);
	fd2 = open("testfile_bonus.txt", O_RDONLY);

	if (fd1 < 0 || fd2 < 0)
	{
		perror("open");
		return (1);
	}

	while (i < 20)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);

		if (line1)
		{
			printf(GREEN "fd1: %s" RESET, line1);
			free(line1);
		}
		if (line2)
		{
			printf(BLUE "fd2: %s" RESET, line2);
			free(line2);
		}
		++i;
	}
	close(fd1);
	close(fd2);
	return (0);
}