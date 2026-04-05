/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:41:35 by yabuawad          #+#    #+#             */
/*   Updated: 2026/04/05 11:41:37 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_newline(char *cmd)
{
	int	i;

	if (!cmd || cmd[0] != '-' || cmd[1] != 'n')
		return (0);
	i = 2;
	while (cmd[i])
	{
		if (cmd[i] != 'n' && cmd[i] != 'e' && cmd[i] != 'E')
			return (0);
		i++;
	}
	return (1);
}

static void	update_on_env(t_env *shell, char *variable, char *value)
{
	char	*full;
	int		j;

	full = ft_strjoin(variable, value);
	if (full)
	{
		j = envp_search(shell->envp, variable);
		env_update(full, shell, j);
		free(full);
	}
}

int	update_pwd(t_env *shell)
{
	char	*old_path;
	char	new_path[4096];

	old_path = find_envp_value(shell->envp, "PWD");
	if (old_path)
		update_on_env(shell, "OLDPWD=", old_path);
	if (getcwd(new_path, sizeof(new_path)) != NULL)
		update_on_env(shell, "PWD=", new_path);
	else
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd(" No such file or directory\n", 2);
	}
	return (1);
}

int	cd_home(t_env *shell)
{
	char	*home;

	home = find_envp_value(shell->envp, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home) == -1)
		return (chdir_error(home));
	if (!update_pwd(shell))
		return (1);
	return (0);
}

int	cd_oldpwd(t_env *shell)
{
	char	*prv_pwd;

	prv_pwd = find_envp_value(shell->envp, "OLDPWD");
	if (!prv_pwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (chdir(prv_pwd) == -1)
		return (chdir_error(prv_pwd));
	ft_putendl_fd(prv_pwd, 1);
	if (!update_pwd(shell))
		return (1);
	return (0);
}
