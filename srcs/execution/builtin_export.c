#include "../minishell.h"

static char	**new_environment(char **envp, char *cmd)
{
	char	**new_envp;
	int		i;

	if (!envp || !cmd)
		return (NULL);
	i = 0;
	new_envp = ft_envdup(envp, 1);
	if (!new_envp)
		return (NULL);
	i = ft_2dstrlen(envp);
	new_envp[i] = ft_strdup(cmd);
	if (!new_envp[i])
	{
		free_2d(new_envp);
		return (NULL);
	}
	i++;
	new_envp[i] = NULL;
	return (new_envp);
}

int	env_update(char *cmd, t_env *shell, int j)
{
	char	**old_envp;
	char	*new_value;

	if (j == -1)
	{
		old_envp = shell->envp;
		shell->envp = new_environment(shell->envp, cmd);
		if (!shell->envp)
		{
			shell->envp = old_envp;
			return (0);
		}
		free_2d(old_envp);
		return (1);
	}
	if (ft_strchr(cmd, '='))
	{
		new_value = ft_strdup(cmd);
		if (!new_value)
			return (0);
		free(shell->envp[j]);
		shell->envp[j] = new_value;
	}
	return (1);
}

static int	export_validation(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !cmd[0])
		return (export_error(""));
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
		return (export_error(cmd));
	i = 1;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (export_error(cmd));
		i++;
	}
	return (0);
}
// static void	print_sorted_export(t_env *env)
// {
// 	int	i;
// 	int	j;

// 	i = 0;

// }
int	print_export(t_env *env)
{
	int		i;
	char	*has_value;
	int		len;

	len = 0;
	i = 0;
	while (env->envp[i])
	{
		has_value = ft_strchr(env->envp[i], '=');
		ft_putstr("declare -x ");
		if (has_value)
		{
			len = has_value - env->envp[i];
			write(1, env->envp[i], len);
			write(1, "=\"", 2);
			write(1, has_value + 1, ft_strlen(has_value + 1));
			write(1, "\"", 1);
		}
		else
			write(1, env->envp[i], ft_strlen(env->envp[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

int	execute_export(t_cmd *cmd, t_env *shell)
{
	int	i;
	int	j;
	int	had_error;

	i = 1;
	had_error = 0;
	if (!cmd->argv[1])
		return (print_export(shell));
	while (cmd->argv[i])
	{
		if (export_validation(cmd->argv[i]))
			had_error = 1;
		else
		{
			j = envp_search(shell->envp, cmd->argv[i]);
			if (!env_update(cmd->argv[i], shell, j))
				return (1);
		}
		i++;
	}
	return (had_error);
}
