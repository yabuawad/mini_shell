#include "../minishell.h"

// 0 unquoted, 1 single, 2 double
char    *removeqt(char *str,int j,size_t i)
{
    if (!str)
        return (NULL);
    char    *quoteless;
    int     state;
    
    state = 0;
    quoteless = malloc(ft_strlen(str) + 1);
    if (!quoteless)
        return (NULL);
    while (str[i])
    {
        if (str[i] == '\'' && state == 0)
            state = 1;
        else if (str[i] == '\'' && state == 1)
            state = 0;
        else if (str[i] == '"' && state == 0)
            state = 2;
        else if (str[i] == '"' && state == 2)
            state = 0;
        else
            quoteless[j++] = str[i];
        i++;
    }
    quoteless[j] = '\0';
    return (quoteless);
}

void    clean_qts(t_cmd *cmdlist,int i)
{
    while (cmdlist)
    {
        i = 0;
        while (cmdlist->argv[i])
        {
            char *tmp = removeqt(cmdlist->argv[i],0,0);
            free(cmdlist->argv[i]);
            cmdlist->argv[i] = tmp;
            i++;
        }
        t_redir *r = cmdlist->redirs;
        while (r)
        {
            if (r->type != R_HEREDOC)
            {
                char *tmp = removeqt(r->target,0,0);
                free(r->target);
                r->target = tmp;
            }
            r = r->next_redirection;
        }
        cmdlist = cmdlist->next;
    }
}

int     check_quotes(char *str,char c)
{
    int i;
    int q;

    q = 0;
    i = 0;
    while(str[i])
    {
        if(str[i] == c)
            q++;
        i++;
    }

    if(q % 2 != 0)
    {
        perror("unclosed quotes!!!\n");
        return (-1);
    }
    else 
        return (q);
}
t_env *addenv(void)
{
    t_env   *newenv = malloc(sizeof(t_env));
    if(!newenv)
        return NULL;
    newenv->cmd_head = NULL;
    newenv->last_exit_status = 0;
    newenv->envp = NULL;
    return(newenv);
}
char    **freearr(char **ptr)
{
    int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

