#include "../minishell.h"

void	free_2d(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static void	free_redirections(t_redir *redirs)
{
	t_redir	*current;
	t_redir	*temp;

	current = redirs;
	while (current)
	{
		temp = current->next_redirection;
		if (current->fd != -1)
			close(current->fd);
		if (current->target)
			free(current->target);
		free(current);
		current = temp;
	}
}

static void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_commands(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*temp;

	current = cmd;
	while (current)
	{
		temp = current->next;
		if (current->argv)
			free_argv(current->argv);
		if (current->redirs)
			free_redirections(current->redirs);
		free(current);
		current = temp;
	}
}

void	memory_cleanup(char *line, t_env *shell)
{
	if (shell->cmd_head)
		free_commands(shell->cmd_head);
	shell->cmd_head = NULL;
	free(line);
}
