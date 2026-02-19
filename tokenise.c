#include "minishell.h"

// void new_tok(char *tok,int size)
// {
//     if(!tok[0])
//         return ;
//     t_token *new_tok = malloc(sizeof(t_token));
//     if(!new_tok)
//         return ;
//     new_tok->value = malloc(size + 1);
//     if(!new_tok->value)
//     {
//         free(new_tok);
//         return ;
//     }
//     ft_memcpy(new_tok->value,tok,size);
//     new_tok->value[size] = '\0';
//     new_tok->next = NULL;
// }

void fill_argv(char *line,int size,t_cmd *cmd)
{
    while(size > 0)
    {
        cmd->argv[0][size] = line[size];
        size--;
    }
}
void tokenise(char *line)
{
    char  **split;
    split = seperate(line,' ');
	print_split(split);
}
//ls -l | grep h > out
int main()
{
    while(1)
    {
    char *line = readline("minishell$ ");//we use readline instead of argvs to make the shell interactive,readline works while the program is running
    if(!line)
        return 1;
    else
        add_history(line);
    tokenise(line);
    // parse();
    free(line);
    }
    rl_clear_history(); //clears history ,still not sure if this is the right placement
}
// gcc -Wall -Wextra -Werror tokenise.c -L./libft -lft -lreadline