#include"minishell.h"

t_cmd	*addnode(void)
{
	t_cmd *newnode = malloc(sizeof(t_cmd));
	if(!newnode)
		return NULL;
	newnode->argv = NULL;
	newnode->has_pipe = 0;
	newnode->next = NULL;
	newnode->redirs = NULL;
	return (newnode);
}

t_redir	*addredir(void)
{
	t_redir	*newnode;

	newnode = malloc(sizeof(t_cmd));
	if (!newnode)
		return (NULL);
	newnode->fd = -1;
	newnode->target = NULL;
	newnode->next_redirection = NULL;
    return (newnode);
}

void print_argv(char **argv)	
{
    int i = 0;

    if (!argv)
    {
        printf("    argv: (null)\n");
        return;
    }
    while (argv[i])
    {
        printf("    argv[%d]: [%s]\n", i, argv[i]);
        i++;
    }
}

void print_redirs(t_redir *redir)
{
	int i = 0;

	while (redir)
	{
		printf("    redir[%d]: ", i);
		if (redir->type == R_IN)
			printf("R_IN");
		if (redir->type == R_OUT)
			printf("R_OUT");
		if (redir->type == R_HEREDOC)
			printf("R_HEREDOC");
		if (redir->type == R_APPEND)
			printf("R_APPEND");

		printf(" target=[%s] fd=%d\n",
			   redir->target ? redir->target : "NULL",
			   redir->fd);

		redir = redir->next_redirection;
		i++;
	}
}
void print_cmdlist(t_cmd *cmd)
{
    int i = 0;

    while (cmd)
    {
        printf("CMD %d\n", i);
        printf("  argv:\n");
        print_argv(cmd->argv);

        printf("  redirs:\n");
        if (cmd->redirs)
            print_redirs(cmd->redirs);
        else
            printf("    (none)\n");

        printf("\n");
        cmd = cmd->next;
        i++;
    }
}
