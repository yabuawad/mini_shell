#include "../minishell.h"

int	heredoc_fds(t_redir *redir, t_env *env)
{
	int	fd[2];
	int	ret;

	if (pipe(fd) == -1)
		return (-1);
	g_sig_status = 0;
	while (1)
	{
		ret = heredoc_input(redir, fd, env);
		if (ret <= 0)
			break ;
	}
	close(fd[1]);
	if (ret == -1)
	{
		close(fd[0]);
		return (-1);
	}
	redir->fd = fd[0];
	return (1);
}

int	heredocs_with_pipes(t_cmd *cmd, t_env **shell)
{
	t_cmd	*temp;
	t_redir	*temp_redir;

	temp = cmd;
	while (temp)
	{
		temp_redir = temp->redirs;
		while (temp_redir)
		{
			if (temp_redir->type == R_HEREDOC && temp_redir->fd == -1)
			{
				if (heredoc_fds(temp_redir, *shell) == -1)
				{
					(*shell)->last_exit_status = 130;
					return (-1);
				}
			}
			temp_redir = temp_redir->next_redirection;
		}
		if (!temp->has_pipe)
			break ;
		temp = temp->next;
	}
	return (1);
}

int	heredoc_redirection(t_redir *redir, t_env *env)
{
	int	fd[2];

	if (redir->fd != -1)
	{
		if (dup2(redir->fd, 0) == -1)
			return (dup2_error(redir->fd));
		close(redir->fd);
		redir->fd = -1;
		return (1);
	}
	if (pipe(fd) == -1)
	{
		perror("minishell: pipe");
		return (0);
	}
	while (1)
		if (!heredoc_input(redir, fd, env))
			break ;
	close(fd[1]);
	if (dup2(fd[0], 0) == -1)
		return (dup2_error(fd[0]));
	close(fd[0]);
	return (1);
}
