/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:41:57 by yabuawad          #+#    #+#             */
/*   Updated: 2026/04/05 11:42:02 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_builtin(t_cmd *cmd, t_env *shell)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (execute_echo(cmd));
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (execute_cd(cmd, shell));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (execute_pwd());
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (execute_env(cmd, shell));
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (execute_export(cmd, shell));
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (execute_unset(cmd, shell));
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (execute_exit(cmd, shell));
	return (1);
}

static int	fork_error(void)
{
	perror("minishell: fork\n");
	return (1);
}

int	run_exe_command(t_cmd *cmd, t_env *shell)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	*full_path;

	full_path = find_full_path(shell->envp);
	path = find_command_path(full_path, cmd->argv[0]);
	if (!path)
	{
		if (ft_strchr(cmd->argv[0], '/'))
			return (exec_error(cmd->argv[0]));
		if (!full_path)
			return (exec_error(cmd->argv[0]));
		return (path_error(cmd));
	}
	pid = fork();
	if (pid == -1)
		return (fork_error());
	if (pid == 0)
		execve_handler(path, cmd, shell);
	parent_signals();
	waitpid(pid, &status, 0);
	init_signals();
	free(path);
	return (decode_wait_status(status));
}
