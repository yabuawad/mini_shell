#include "minishell.h"

int check_quotes(char *str)
{
    int i;
    int q;

    q = 0;
    i = 0;
    while(str[i])
    {
        if(str[i] == '"')
            q++;
        i++;
    }

    if(q % 2 != 0)
        return -1;
    else 
        return q;
}

void error(char *error_message)
{
    perror(error_message);
    exit(1);
}