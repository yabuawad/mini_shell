/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:41:43 by yabuawad          #+#    #+#             */
/*   Updated: 2026/04/05 11:41:45 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	unset_validation(char *cmd)
{
	int	i;

	if (!cmd || !cmd[0])
		return (1);
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
		return (1);
	i = 1;
	while (cmd[i])
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static void	unset_env(t_env *shell, int index)
{
	int	j;

	j = 0;
	if (index != -1)
	{
		free(shell->envp[index]);
		j = index;
		while (shell->envp[j])
		{
			shell->envp[j] = shell->envp[j + 1];
			j++;
		}
	}
}

int	execute_unset(t_cmd *cmd, t_env *shell)
{
	int	i;
	int	index;
	int	had_error;

	i = 1;
	had_error = 0;
	while (cmd->argv[i])
	{
		if (unset_validation(cmd->argv[i]))
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(cmd->argv[i], 2);
			ft_putendl_fd(": not a valid identifier", 2);
			had_error = 1;
			i++;
			continue ;
		}
		index = envp_search(shell->envp, cmd->argv[i]);
		unset_env(shell, index);
		i++;
	}
	return (had_error);
}
