#include "minishell.h"

int main()
{
    // t_token *tokens;
    while(1)
    {
        char *line = readline("minishell$ ");//we use readline instead of argvs to make the shell interactive,readline works while the program is running
        if(!line)
            return 1;
        else
            add_history(line);
        tokenise(line);
        // parse(line);
        free(line);
    }
    rl_clear_history(); //clears history ,still not sure if this is the right placement
}
// cc -Wall -Wextra -Werror tokenise.c -L./libft -lft -lreadline
//perror only used when a system call or alibrary function fails
//