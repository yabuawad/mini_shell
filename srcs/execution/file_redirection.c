#include "../minishell.h"

static int	dup_failure(int old_stdin, int old_stdout)
{
	if (old_stdin != -1)
		close(old_stdin);
	if (old_stdout != -1)
		close(old_stdout);
	perror("minishell: dup");
	return (1);
}

static void	child_execution(t_cmd *cmd, t_env *shell)
{
	int		status;
	char	*path;
	char	*full_path;

	if (!apply_redirections(cmd->redirs, shell))
		exit(1);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_builtin(cmd->argv[0]))
	{
		status = execute_builtin(cmd, shell);
		exit(status);
	}
	full_path = find_full_path(shell->envp);
	path = find_command_path(full_path, cmd->argv[0]);
	if (!path)
		path_handler(cmd, full_path);
	execve_handler(path, cmd, shell);
}

static int	builtin_with_redirection(t_cmd *cmd, t_env *shell)
{
	int	status;
	int	old_stdin;
	int	old_stdout;

	old_stdin = dup(0);
	old_stdout = dup(1);
	if (old_stdin == -1 || old_stdout == -1)
		return (dup_failure(old_stdin, old_stdout));
	if (!apply_redirections(cmd->redirs, shell))
		status = 1;
	else
		status = execute_builtin(cmd, shell);
	if (dup2(old_stdin, 0) == -1)
		perror("minishell: dup2");
	if (dup2(old_stdout, 1) == -1)
		perror("minishell: dup2");
	close(old_stdin);
	close(old_stdout);
	return (status);
}

int	execute_with_redirections(t_cmd *cmd, t_env *shell)
{
	int		status;
	pid_t	pid;

	if (!cmd || !cmd->redirs)
		return (0);
	if (cmd->argv && cmd->argv[0] && is_builtin(cmd->argv[0]))
		return (builtin_with_redirection(cmd, shell));
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	if (pid == 0)
		child_execution(cmd, shell);
	waitpid(pid, &status, 0);
	return (decode_wait_status(status)); // ?
}
