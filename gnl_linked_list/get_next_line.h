/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:14:52 by acosi             #+#    #+#             */
/*   Updated: 2023/04/04 12:21:07 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
void	read_and_stash(int fd, t_list **stash);
void	add_to_stash(t_list **stash, char *buffer, int readed);
void	extract_line(t_list *stash, char **line);
void	clean_stash(t_list **stash);
int		found_newline(t_list *stash);
t_list	*ft_lst_get_last(t_list *stash);
void	malloc_line(t_list *stash, char **line);
void	free_stash(t_list *stash);
int		ft_strlen(char *content);

#endif