/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:30:21 by yabuawad          #+#    #+#             */
/*   Updated: 2026/04/05 11:30:22 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*removeqt(char *str, int j, size_t i)
{
	char	*quoteless;
	int		state;

	if (!str)
		return (NULL);
	state = 0;
	quoteless = malloc(ft_strlen(str) + 1);
	if (!quoteless)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && state == 0)
			state = 1;
		else if (str[i] == '\'' && state == 1)
			state = 0;
		else if (str[i] == '"' && state == 0)
			state = 2;
		else if (str[i] == '"' && state == 2)
			state = 0;
		else
			quoteless[j++] = str[i];
		i++;
	}
	quoteless[j] = '\0';
	return (quoteless);
}

void	clean_qts(t_cmd *cmdlist, int i, t_redir *r)
{
	char	*tmp;

	while (cmdlist)
	{
		i = 0;
		while (cmdlist->argv[i])
		{
			tmp = removeqt(cmdlist->argv[i], 0, 0);
			free(cmdlist->argv[i]);
			cmdlist->argv[i] = tmp;
			i++;
		}
		r = cmdlist->redirs;
		while (r)
		{
			if (r->type != R_HEREDOC)
			{
				tmp = removeqt(r->target, 0, 0);
				free(r->target);
				r->target = tmp;
			}
			r = r->next_redirection;
		}
		cmdlist = cmdlist->next;
	}
}

int	check_quotes(char *str, char c)
{
	int	i;
	int	q;

	q = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			q++;
		i++;
	}
	if (q % 2 != 0)
	{
		ft_putendl_fd("minishell: unclosed quotes", 2);
		return (-1);
	}
	else
		return (q);
}

t_env	*addenv(void)
{
	t_env	*newenv;

	newenv = malloc(sizeof(t_env));
	if (!newenv)
		return (NULL);
	newenv->cmd_head = NULL;
	newenv->last_exit_status = 0;
	newenv->envp = NULL;
	return (newenv);
}

char	**freearr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}
