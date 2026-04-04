#include "../minishell.h"

int	execute_cd(t_cmd *cmd, t_env *shell)
{
	if (!cmd || !cmd->argv)
		return (1);
	if (!cmd->argv[1] || (cmd->argv[1][0] == '~' && cmd->argv[1][1] == '\0'))
		return (cd_home(shell));
	if (cmd->argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (cmd->argv[1][0] == '-' && cmd->argv[1][1] == '\0')
		return (cd_oldpwd(shell));
	if (chdir(cmd->argv[1]) == -1)
		return (chdir_error(cmd->argv[1]));
	if (!update_pwd(shell))
		return (1);
	return (0);
}

int	execute_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (cmd->argv[i] && echo_newline(cmd->argv[i]))
	{
		newline = 0;
		i++;
	}
	while (cmd->argv[i])
	{
		write(1, cmd->argv[i], ft_strlen(cmd->argv[i]));
		if (cmd->argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}

int	execute_pwd(void)
{
	char	pwd[4096];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("minishell: pwd");
		return (1);
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (0);
}

int	execute_env(t_cmd *cmd, t_env *shell)
{
	int	i;

	if (cmd->argv[1])
	{
		i = 1;
		while (cmd->argv[i])
		{
			if (ft_strcmp(cmd->argv[i], "env") != 0)
				return (env_error(cmd->argv[i]));
			i++;
		}
	}
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strchr(shell->envp[i], '='))
		{
			write(1, shell->envp[i], ft_strlen(shell->envp[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}
