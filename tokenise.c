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

// void fill_argv(char *line,int size,t_cmd *cmd)
// {
//     while(size > 0)
//     {
//         cmd->argv[0][size] = line[size];
//         size--;
//     }
// }   

// char **seperate_pipes(char **tokenised,int i,int j)
// {
//     char **fullytokenised = malloc(sizeof(char *) * ft_strlen(*tokenised) + 2);
//     int x;
//     int y;

//     x = 0;
//     y = 0;
//     if(j == 0)
//     {
//     }
// }

char  **check_pipes(char **tokenised)
{
    if(!tokenised)
        return NULL;
    char **fullytokenised = malloc(sizeof(char *) * (ft_strlen(*tokenised) + 2));
    if(!fullytokenised)
        return NULL;
    int i;
    int j;
    int y;
    int x;
    x = 0;
    
    y = 0;
    i = 0;
    j = 0;
    while(tokenised[i])
    {
        j = 0;
        fullytokenised[x] = malloc(ft_strlen(tokenised[i]) + 1);
        if(!fullytokenised[x])
            return NULL;
        while(tokenised[i][j])
        {
            if(tokenised[i][j] == '|' && ft_strlen(tokenised[i]) != 1)
            {
                printf("here");
                if(j == 0)
                {
                    fullytokenised[x++][0] = '|';
                    x++;
                }
                // if(j > 0)
                // {
                //     fullytokenised[x][y] = '|';
            }
            else
                fullytokenised[x++][y++] = tokenised[i][j];
            j++;
        }
        i++;
    }
    return fullytokenised;
}

void tokenise(char *line)
{
    char  **tokenised;
    // dq = 1;    
    if(check_quotes(line,'"') < 0 || check_quotes(line,'\'') < 0)
    {
        fprintf(stderr,"unclosed quotes!!!\n");
        return;
    }
    if(check_quotes(line,'"') > 0)
        tokenised = sep(line,' ','"');
    else
        tokenised = sep(line,' ','\'');
    print_split(check_pipes(tokenised));

    // print_split(tokenised);
}

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
// cc -Wall -Wextra -Werror tokenise.c -L./libft -lft -lreadline
//perror only used when a system call or alibrary function fails
//