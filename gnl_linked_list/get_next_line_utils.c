/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:13:20 by acosi             #+#    #+#             */
/*   Updated: 2023/04/04 12:20:37 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Looks for a newline character in the given linked list.

int	found_newline(t_list *stash)
{
	int		i;
	t_list	*temp;

	if (stash == NULL)
		return (0);
	temp = ft_lst_get_last(stash);
	i = 0;
	while (temp->content[i])
	{
		if (temp->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

// Returns a pointer to the last node in our stash.

t_list	*ft_lst_get_last(t_list *stash)
{
	t_list	*temp;

	temp = stash;
	while (temp && temp->next)
		temp = temp->next;
	return (temp);
}

// Calculate the number of chars in the current line,
// including the trailing \n if there is one, and allocates memory accordingly.

void	malloc_line(t_list *stash, char **line)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

// Frees the entire stash.

void	free_stash(t_list *stash)
{
	t_list	*temp;
	t_list	*next;

	temp = stash;
	while (temp)
	{
		free (temp->content);
		next = temp->next;
		free (temp);
		temp = next;
	}
}

int	ft_strlen(char *content)
{
	int	i;

	i = 0;
	while (*(content++))
		i++;
	return (i);
}
