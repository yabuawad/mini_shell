#include "../minishell.h"

static int	infile_redirection(t_redir *redir)
{
	int	infile_fd;

	infile_fd = open(redir->target, O_RDONLY);
	if (infile_fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->target, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	if (dup2(infile_fd, 0) == -1)
	{
		close(infile_fd);
		return (0);
	}
	if (close(infile_fd) == -1)
		return (0);
	return (1);
}

static int	outfile_redirection(t_redir *redir)
{
	int	outfile_fd;

	outfile_fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->target, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	if (dup2(outfile_fd, 1) == -1)
	{
		close(outfile_fd);
		return (0);
	}
	if (close(outfile_fd) == -1)
		return (0);
	return (1);
}

static int	append_redirection(t_redir *redir)
{
	int	append_fd;

	append_fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (append_fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->target, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	if (dup2(append_fd, 1) == -1)
	{
		close(append_fd);
		return (0);
	}
	if (close(append_fd) == -1)
		return (0);
	return (1);
}

int	apply_redirections(t_redir *redir, t_env *env)
{
	while (redir)
	{
		if (redir->type == R_IN)
		{
			if (!infile_redirection(redir))
				return (0);
		}
		else if (redir->type == R_OUT)
		{
			if (!outfile_redirection(redir))
				return (0);
		}
		else if (redir->type == R_APPEND)
		{
			if (!append_redirection(redir))
				return (0);
		}
		else if (redir->type == R_HEREDOC)
		{
			if (!heredoc_redirection(redir, env))
				return (0);
		}
		redir = redir->next_redirection;
	}
	return (1);
}
