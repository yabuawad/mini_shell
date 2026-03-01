#include "minishell.h"

// tokens = ["ls","-l","|","grep","h"];

t_cmd *parse(char **tokens,int i,int tmpsize)
{        
    t_cmd   *head;              
    t_cmd   *current;           
    char    *argv_temp[1024];
    t_redir *redir_head;
    head = addnode();
    if (!head)
        return NULL;
    current = head;
    redir_head = NULL;
    t_redir *redtail = NULL;
    while (tokens[i])
    {
        if (ft_strncmp(tokens[i],"|",ft_strlen(tokens[i])) == 0)
        {
            current = end_cmd(current,tmpsize,argv_temp,redir_head);
            tmpsize = 0;
            redir_head = NULL;
            i++;
            continue;
        }
        if ((ft_strncmp(tokens[i],"<",1) == 0) || (ft_strncmp(tokens[i],">",1) == 0))
        {
            t_redir *cmdredir = addredir();
            fill_red(cmdredir,&redtail,&redir_head,tokens,i);
            i += 2;
            continue;
        }
            argv_temp[tmpsize] = tokens[i];
            tmpsize++;
        i++;
    }
    lastcmd(current,argv_temp,redir_head,tmpsize);

    return (head);
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