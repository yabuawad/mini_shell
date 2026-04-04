#include "../minishell.h"

void	execve_handler(char *path, t_cmd *cmd, t_env *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, cmd->argv, shell->envp);
	perror("execve");
	free(path);
	exit(127);
}

void	path_handler(t_cmd *cmd, char *full_path)
{
	if (ft_strchr(cmd->argv[0], '/'))
		exit(exec_error(cmd->argv[0]));
	if (!full_path)
		exit(exec_error(cmd->argv[0]));
	exit(path_error(cmd));
}

int	setup_fds(int i, t_pipes *pipes)
{
	if (i > 0)
	{
		if (dup2(pipes->last_read, 0) == -1)
		{
			perror("minishell: dup2");
			return (-1);
		}
	}
	if (dup2(pipes->fd[1], 1) == -1)
	{
		perror("minishell: dup2");
		return (-1);
	}
	if (pipes->last_read != -1)
		close(pipes->last_read);
	if (pipes->fd[1] != -1)
		close(pipes->fd[1]);
	if (pipes->fd[0] != -1)
		close(pipes->fd[0]);
	return (1);
}

int	decode_wait_status(int status)
{
	// converts the raw waitpid() status int shell-style code,
	if (WIFEXITED(status)) // child ended normally
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status)) // child was killed by a signal
		return (128 + WTERMSIG(status));
	return (1); // safe generic failure
}

int	wait_for_all(t_pipes *pipes)
{
	int	status;
	int	i;
	int	last_status;

	i = 0;
	last_status = 0;
	if (pipes->last_read != -1)
		close(pipes->last_read);
	while (i < pipes->cmds_length)
	{
		waitpid(pipes->pids[i], &status, 0);
		if (i == pipes->cmds_length - 1)
			last_status = status;
		i++;
	}
	pipes_cleanup(pipes, 0);
	init_signals();
	return (decode_wait_status(last_status));
}
