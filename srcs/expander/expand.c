/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:37:17 by yabuawad          #+#    #+#             */
/*   Updated: 2026/04/05 11:37:24 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*build_replaced(char *old, char *value, char *var, size_t var_index)
{
	size_t	i;
	size_t	j;
	size_t	n;
	char	*newstr;

	i = 0;
	j = 0;
	n = var_index + ft_strlen(var) + 1;
	newstr = malloc(ft_strlen(old) - (ft_strlen(var) + 1) + ft_strlen(value)
			+ 1);
	if (!newstr)
		return (NULL);
	while (i < var_index)
	{
		newstr[i] = old[i];
		i++;
	}
	while (value[j])
		newstr[i++] = value[j++];
	while (old[n])
		newstr[i++] = old[n++];
	newstr[i] = '\0';
	return (newstr);
}

void	replace_var(t_env *myenv, char *var, char **str, size_t var_index)
{
	char	*old;
	char	*value;
	char	*newstr;

	value = find_env_val(myenv, var);
	if (!value)
		value = ft_strdup("");
	old = *str;
	newstr = build_replaced(old, value, var, var_index);
	if (!newstr)
	{
		free(value);
		return ;
	}
	*str = ft_strdup(newstr);
	free_var(old, newstr, value);
}

void	expand_this(char **str, t_env *myenv, int i, int state)
{
	int	result;

	result = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' && state == 0)
			state = 1;
		else if ((*str)[i] == '\'' && state == 1)
			state = 0;
		else if ((*str)[i] == '"' && state == 0)
			state = 2;
		else if ((*str)[i] == '"' && state == 2)
			state = 0;
		else if ((*str)[i] == '$' && state != 1)
		{
			result = dollar_sign_handler(myenv, str, i);
			if (result == -1)
				return ;
			else if (!result)
				continue ;
		}
		i++;
	}
}

static void	do_expansion(t_env *myenv, t_cmd *curnt, t_redir *r)
{
	int		i;
	char	**split;

	while (curnt)
	{
		i = 0;
		while (curnt->argv[i])
		{
			if (is_pure_var(curnt->argv[i]))
				check_tok(curnt, myenv, &split, &i);
			else
			{
				expand_this(&curnt->argv[i], myenv, 0, 0);
				i++;
			}
		}
		r = curnt->redirs;
		while (r)
		{
			if (r->type != R_HEREDOC)
				expand_this(&r->target, myenv, 0, 0);
			r = r->next_redirection;
		}
		curnt = curnt->next;
	}
}

t_env	*expand(t_cmd *cmdlist, char **env, int last_exit_status)
{
	t_env	*myenv;
	t_cmd	*curnt;
	t_redir	*r;

	myenv = addenv();
	if (!myenv)
		return (NULL);
	myenv->cmd_head = cmdlist;
	myenv->envp = env;
	myenv->last_exit_status = last_exit_status;
	curnt = cmdlist;
	r = NULL;
	do_expansion(myenv, curnt, r);
	return (myenv);
}
/*
only double qts are expanded,single qts are always literal
you need to expand commands arguments AND redirections targets
*/
