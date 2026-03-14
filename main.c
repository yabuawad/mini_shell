#include "minishell.h"
void free_redirs(t_redir *redir)
{
    t_redir *tmp;

    while (redir)
    {
        tmp = redir->next_redirection;

        if (redir->target)
            free(redir->target);   // if you strdup the filename

        free(redir);
        redir = tmp;
    }
}
void free_cmdlist(t_cmd *cmd)
{
    while (cmd)
    {
        t_cmd *next = cmd->next;

        freearr(cmd->argv);
        free_redirs(cmd->redirs);

        free(cmd);
        cmd = next;
    }
}
int main(int argc,char **argv,char **env)
{
    (void)argc;
    (void)argv;
    t_cmd *cmdlist;
    t_env *myenv;
    while(1)
    {
        char *line = readline("minishell$ ");//we use readline instead of argvs to make the shell interactive,readline works while the program is running
        if(!line)
            return 1;
        else
            add_history(line);
        char **tokens = tokenise(line);
        if(!tokens)
            return 1;
        cmdlist = parse(tokens,0,0);
        myenv = expand(cmdlist,env);
        print_cmdlist(cmdlist);
        (void)myenv;
        free_cmdlist(cmdlist);
        free(line);
        freearr(tokens);
        free(myenv);
    }
    rl_clear_history(); //clears history ,still not sure if this is the right placement
}
// cc -Wall -Wextra -Werror tokenise.c -L./libft -lft -lreadline
//perror only used when a system call or alibrary function fails
//