/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:30:02 by yabuawad          #+#    #+#             */
/*   Updated: 2026/04/05 11:30:03 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_tokens(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static t_exp	*init_myexp(void)
{
	t_exp	*myexp;

	myexp = malloc(sizeof(t_exp));
	if (!myexp)
		return (NULL);
	myexp->old_len = 0;
	myexp->exp_len = 0;
	myexp->new_len = 0;
	myexp->new_argv = NULL;
	myexp->i = 0;
	myexp->j = 0;
	return (myexp);
}

char	**split_argv(char **argv, int pos, char **expanded)
{
	t_exp	*myexp;

	myexp = init_myexp();
	if (!myexp)
		return (NULL);
	myexp->old_len = count_tokens(argv);
	myexp->exp_len = count_tokens(expanded);
	myexp->new_len = myexp->old_len - 1 + myexp->exp_len;
	myexp->new_argv = malloc(sizeof(char *) * (myexp->new_len + 1));
	if (!myexp->new_argv)
		return (NULL);
	myexp->i = 0;
	myexp->j = 0;
	while (myexp->j < pos)
		myexp->new_argv[myexp->i++] = argv[myexp->j++];
	myexp->j = 0;
	while (expanded[myexp->j])
		myexp->new_argv[myexp->i++] = ft_strdup(expanded[myexp->j++]);
	myexp->j = pos + 1;
	while (argv[myexp->j])
		myexp->new_argv[myexp->i++] = argv[myexp->j++];
	myexp->new_argv[myexp->i] = NULL;
	return (myexp->new_argv);
}

int	is_pure_var(char *str)
{
	int	i;

	if (str[0] != '$')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	check_tok(t_cmd *curnt, t_env *myenv, char ***split, int *i)
{
	char	**new_argv;

	expand_this(&curnt->argv[*i], myenv, 0, 0);
	*split = sep(curnt->argv[*i], ' ', 0);
	if (*split && count_tokens(*split) > 1)
	{
		new_argv = split_argv(curnt->argv, *i, *split);
		if (new_argv)
		{
			free(curnt->argv[*i]);
			free(curnt->argv);
			curnt->argv = new_argv;
			*i += count_tokens(*split);
		}
		else
			(*i)++;
		freearr(*split);
	}
	else
	{
		freearr(*split);
		(*i)++;
	}
}
