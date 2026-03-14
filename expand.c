#include "minishell.h"

void replace_var(t_env *myenv,char *var,char **str,size_t var_index)
{
    size_t i = 0;
    size_t j = 0;
    // int flg = 0;
    // char *str  = cmdlist->argv[r];
    char *old = *str;
    char *value = find_env_val(myenv,var);
    if(!value)
        value = ft_strdup("");
    // printf("value ::: %s\n",value);
    char *newstr = malloc(ft_strlen(old)-(ft_strlen(var)+1)+ft_strlen(value) + 1);
    if(!newstr)
    {
        free(value);
        return;
    }
    while(i < var_index) // to fill whats bfore $
    {
        newstr[i] = old[i];
        i++;
    }
    while(j < ft_strlen(value))
        newstr[i++] = value[j++];
    size_t n = var_index + ft_strlen(var) + 1;
    while(old[n] != '\0')
        newstr[i++] = old[n++];
    newstr[i] = '\0';
    *str = ft_strdup(newstr);
    free(old);
    free(newstr);
    free(value);

}
void expand_this(char **str,t_env *myenv)
{
    int i;
    // char *str = cmdlist->argv[r];
    i = 0;
    while((*str)[i])
    {
        if((*str)[i] =='$')
        {
            // printf("here\n");
            if(i > 0 && (*str)[i - 1] == '\'')
            {
                i++;
                continue;
            }
            else
            {
                char *var = malloc(get_length(*str,i)+ 1);
                printf("length: %d\n",get_length(*str,i));
                if(!var)
                {
                    free(myenv);
                    return ;
                }
                var = get_var(*str,i,var); //PATH
                printf("ITS :: %s\n",var);
                replace_var(myenv,var,str,i);
                free(var);
                continue;
                // str = cmdlist->argv[r];
            }   
        }
        i++;
    }
}
 
t_env *addenv(void)
{
    t_env *newenv = malloc(sizeof(t_env));
    if(!newenv)
        return NULL;
    newenv->cmd_head = NULL;
    newenv->last_exit_status = 0;
    newenv->envp = NULL;
    return(newenv);
}

t_env *expand(t_cmd *cmdlist,char **env)
{
    t_env *myenv = addenv();
    if(!myenv)
    return NULL;
    myenv->cmd_head = cmdlist;
    myenv->envp = env;
    t_cmd *curnt = cmdlist;
    while (curnt)
    {
        size_t i = 0;
        while (curnt->argv[i])
        {
            expand_this(&curnt->argv[i], myenv); 
            i++;
        }
        t_redir *r = curnt->redirs;
        while (r)
        {
            if (r->type != R_HEREDOC)
                expand_this(&r->target, myenv);
            r = r->next_redirection;
        }
        curnt = curnt->next;
    }
    return(myenv);
}   

/*
only double qts are expanded,single qts are always literal
you need to expand commands arguments AND redirections targets
*/
