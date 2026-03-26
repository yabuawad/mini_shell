#include"../minishell.h"

void fill_argv(t_cmd *cmd, char **tempargv, int tmpsize)
{
    int i = 0;

    while (i < tmpsize)
    {
        cmd->argv[i] = ft_strdup(tempargv[i]);
        if(!cmd->argv[i])
            return;
        i++;
    }
    cmd->argv[i] = NULL;
}
t_cmd *end_cmd(t_parse **parse,char **argv_temp)
{
    (*parse)->current->next= NULL;
    (*parse)->current->argv = malloc(sizeof(char *) * ((*parse)->tmpsize + 1));
    if(!(*parse)->current->argv)
        return NULL;
    fill_argv((*parse)->current,argv_temp,(*parse)->tmpsize); // to fill (*parse)->current cmd with temp
    (*parse)->current->redirs = (*parse)->redir_head;
    (*parse)->current->next = addnode();
    if (!(*parse)->current->next)
        return (NULL);
    (*parse)->current = (*parse)->current->next;
    return ((*parse)->current);
}

void set_redtype(t_redir *cmdredir,char **tokens,int i)
{
    if(ft_strncmp(tokens[i],"<<",2) == 0)
        cmdredir->type = R_HEREDOC;
    else if(ft_strncmp(tokens[i],">>",2) == 0)
        cmdredir->type = R_APPEND;
    else if(ft_strncmp(tokens[i],"<",1) == 0)
        cmdredir->type = R_IN;
    else if(ft_strncmp(tokens[i],">",1) == 0)
        cmdredir->type = R_OUT;
}

void fill_red(t_redir *cmdredir,t_redir **redtail,t_redir **redir_head,char **tokens,int i)
{
    // if(!cmdredir)
    //     return NULL;    
    cmdredir->next_redirection = NULL;   
    set_redtype(cmdredir,tokens,i);
    (cmdredir)->target = ft_strdup(tokens[i + 1]);
    if(!*redir_head)
    {
        *redir_head = cmdredir;
        *redtail = cmdredir;
    }
    else
    {
        (*redtail)->next_redirection = cmdredir;
         *redtail = cmdredir;
    }
    // return(*cmdredir);
}

void lastcmd(t_cmd *current,char **argv_temp,t_redir *redir_head,int tmpsize)
{
    current->argv = malloc(sizeof(char *) * (tmpsize + 1));
    if(!current->argv)
        return ;
    fill_argv(current,argv_temp,tmpsize);
    current->redirs = redir_head;
    current->next = NULL;
}