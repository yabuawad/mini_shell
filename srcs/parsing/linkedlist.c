/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:30:32 by yabuawad          #+#    #+#             */
/*   Updated: 2026/04/05 11:30:34 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*addnode(void)
{
	t_cmd	*newnode;

	newnode = malloc(sizeof(t_cmd));
	if (!newnode)
		return (NULL);
	newnode->argv = NULL;
	newnode->has_pipe = 0;
	newnode->next = NULL;
	newnode->redirs = NULL;
	return (newnode);
}

t_redir	*addredir(void)
{
	t_redir	*newnode;

	newnode = malloc(sizeof(t_redir));
	if (!newnode)
		return (NULL);
	newnode->fd = -1;
	newnode->target = NULL;
	newnode->next_redirection = NULL;
	return (newnode);
}

void	free_partial_argv(char **argv, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	init(t_tok *mytok)
{
	mytok->j = 0;
	mytok->start = 0;
	mytok->in_sqt = 0;
	mytok->in_dqt = 0;
}
