/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:30:00 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/19 03:54:35 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parse(char **tokens, int i, int tmpsize)
{
	t_cmd	*head;
	t_cmd	*current;
	t_redir	*redir_head;
	t_redir	*redtail;
	t_redir	*cmdredir;
	char	*argv_temp[1024];

	head = addnode();
	if (!head)
		return (NULL);
	current = head;
	redir_head = NULL;
	redtail = NULL;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "|", 1) == 0)
		{
			current->has_pipe = 1;
			current = end_cmd(current, tmpsize, argv_temp, redir_head);
			tmpsize = 0;
			redir_head = NULL;
			i++;
		}
		else if (ft_strncmp(tokens[i], "<", 1) == 0
			|| ft_strncmp(tokens[i], ">", 1) == 0)
		{
			cmdredir = addredir();
			if (!cmdredir)
				return (head);
			fill_red(cmdredir, &redtail, &redir_head, tokens, i);
			i += 2;
		}
		else
			argv_temp[tmpsize++] = tokens[i++];
	}
	lastcmd(current, argv_temp, redir_head, tmpsize);
	return (head);
}
