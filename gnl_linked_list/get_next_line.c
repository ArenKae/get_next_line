/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:12:50 by acosi             #+#    #+#             */
/*   Updated: 2023/04/17 16:33:56 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_and_stash(fd, &stash);
	if (stash == NULL)
		return (NULL);
	extract_line(stash, &line);
	clean_stash(&stash);
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

// Uses read() to add characters to the stash.

void	read_and_stash(int fd, t_list **stash)
{
	char	*buffer;
	int		read_size;

	read_size = 1;
	while (!found_newline(*stash) && read_size != 0)
	{
		buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (buffer == NULL)
			return ;
		read_size = (int)read(fd, buffer, BUFFER_SIZE);
		if ((*stash == NULL && read_size == 0) || read_size == -1)
		{
			free(buffer);
			return ;
		}
		buffer[read_size] = '\0';
		add_to_stash(stash, buffer, read_size);
		free(buffer);
	}
}

// Adds the content of our buffer to the end of our stash.

void	add_to_stash(t_list **stash, char *buffer, int read_size)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (read_size + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buffer[i] && i < read_size)
	{
		new_node->content[i] = buffer[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = ft_lst_get_last(*stash);
	last->next = new_node;
}

// Extract all characters from the stash and stores them in the line variable,
// stopping after the first \n it encounters.

void	extract_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	malloc_line(stash, line);
	if (*line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

// After extracting the line that was read, we don't need those characters
// anymore. This function clears the stash so only the characters that have not
// been returned at the end of get_next_line() remain in our static stash.

void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (stash == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = ft_lst_get_last(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		i++;
	j = ft_strlen(last->content);
	clean_node->content = malloc(sizeof(char) * (j - i) + 1);
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_stash(*stash);
	*stash = clean_node;
}
