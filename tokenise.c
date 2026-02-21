#include "minishell.h"

int count_tok(char **tokenised) // count the size of tokens after seperating the pipe,so we can malloc the right size
{
    int i;
    int j;
    int counter;

    i = 0;
    counter =0;
    while(tokenised[i])
    {
        j = 0;
        while(tokenised[i][j])
        {
            if(tokenised[i][j] == '|')
                counter++;
            j++;
        }
        counter++;
        i++;
    }
    return(counter);
}
// char pipe
char **check_pipes(char **tokenised) // this function is for post seperation pipe check
{       //for example the command echo "hello"|grep h works even tho there are no spaces so this function is to seperate pipes from cmds 
    int i;
    int x;
    int j;
    int found;
    char **pipedtok;

    pipedtok = malloc(sizeof(char *) * (count_tok(tokenised) + 1));
    if (!pipedtok)
        return NULL;

    i = 0;
    x = 0;
    while (tokenised[i])
    {
        j = 0;
        found = 0;

        while (tokenised[i][j])
        {
            if (tokenised[i][j] == '|' && ft_strlen(tokenised[i]) > 1)
            {
                if (j > 0)
                    pipedtok[x++] = ft_substr(tokenised[i], 0, j);
                pipedtok[x++] = ft_strdup("|");
                if (tokenised[i][j + 1])
                    pipedtok[x++] = ft_strdup(tokenised[i] + j + 1);
                found = 1;
                break;
            }
            j++;
        }
        if (!found)
            pipedtok[x++] = ft_strdup(tokenised[i]);
        i++;
    }
    pipedtok[x] = NULL;
    return (pipedtok);
}


void tokenise(char *line)
{
    char  **tokenised;
    // dq = 1;    
    if(check_quotes(line,'"') < 0 || check_quotes(line,'\'') < 0) //check on unclosed quotes
    {
        fprintf(stderr,"unclosed quotes!!!\n");
        return;
    }
    if(check_quotes(line,'"') > 0)  //if quotes are double you pass the double
        tokenised = sep(line,' ','"');
    else
        tokenised = sep(line,' ','\''); // any other case? we pass the single
    print_split(check_pipes(tokenised));
    // print_split(tokenised);
    // makelist(tokenised);
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