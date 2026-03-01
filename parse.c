#include "minishell.h"

// tokens = ["ls","-l","|","grep","h"];

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

void fill_argv(t_cmd *cmd,char **tempargv,int tmpsize)
{
    int i;

    i = 0;
    while(i < tmpsize)
    {
        cmd->argv[i] = tempargv[i];
        i++;
    }
    cmd->argv[i] = NULL;
}

t_cmd *parse(char **tokens,int i)
{        
    t_cmd   *head;              
    t_cmd   *current;           
    char    *argv_temp[1024];
    int     tmpsize;
    t_redir *redir_head;
    head = addnode();
    if (!head)
        return NULL;
    current = head;
    tmpsize = 0;
    redir_head = NULL;
    while (tokens[i])
    {
        if (ft_strncmp(tokens[i],"|",ft_strlen(tokens[i])) == 0)
        {
            // end current command
            current->next= NULL;
            current->argv = malloc(sizeof(char *) * (tmpsize + 1));
            if(!current->argv)
                return NULL;
            fill_argv(current,argv_temp,tmpsize); // to fill current cmd with temp
            current->redirs = redir_head;
            current->next = addnode();
            current = current->next;
            tmpsize = 0;
            redir_head = NULL;
            i++;
            continue;
        }
        if ((ft_strncmp(tokens[i],"<",1) == 0) || (ft_strncmp(tokens[i],">",1) == 0))
        {
            t_redir *cmdredir = addredir();
            t_redir *redtail;
            if(!cmdredir)
                return NULL;
            set_redtype(cmdredir,tokens,i);
                cmdredir->target = tokens[i + 1];
           if (!redir_head)
            {
                redir_head = cmdredir;
                redtail = cmdredir;
            }
            else
            {
                redtail->next_redirection = cmdredir;
                redtail = cmdredir;
            }
            i += 2;
            continue;
        }
            argv_temp[tmpsize] = tokens[i];
            tmpsize++;
        i++;
    }
    current->argv = malloc(sizeof(char *) * (tmpsize + 1));
    if(!current->argv)
        return NULL;
    fill_argv(current,argv_temp,tmpsize);
    current->redirs = redir_head;
    current->next = NULL;
    return head;
}

// tokens
//   ↓
// syntax validation
//   ↓
// expansion
//   ↓
// quote removal
//   ↓
// build command structures (t_cmd, redirs, pipes)

//tokenise =  OK
//syntax validation = OK
// fill struct = OK
// expand
//excute