#include "minishell.h"

int main(int argc,char **argv,char **env)
{
    (void)argc;
    (void)argv;
    t_cmd *cmdlist;
    while(1)
    {
        char *line = readline("minishell$ ");//we use readline instead of argvs to make the shell interactive,readline works while the program is running
        if(!line)
            return 1;
        else
            add_history(line);
        char **tokens = tokenise(line);
        // if(!tokens)
        //     return 1;
        cmdlist = parse(tokens,0,0);
        print_cmdlist(cmdlist);
        expand(cmdlist,env);
        free(line);
    }
    rl_clear_history(); //clears history ,still not sure if this is the right placement
}
// cc -Wall -Wextra -Werror tokenise.c -L./libft -lft -lreadline
//perror only used when a system call or alibrary function fails
//