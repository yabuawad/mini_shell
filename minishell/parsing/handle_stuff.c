#include "../minishell.h"

char *removeqt(char *str)
{
    char *quoteless;

    if (!str)
        return (NULL);
    quoteless = malloc(ft_strlen(str) + 1);
    if(!quoteless)
        return NULL;
    size_t i;
    int j;

    j = 0;
    i = 0;
    while(str[i])
    {
        if(str[i] == '"' || str[i] == '\'' )
        {
            // if(i != 0 && i < ft_strlen(str))
                i++;
        }
        else        
            quoteless[j++] = str[i++];  
    }
    quoteless[j] = '\0';
    return (quoteless);
}

// void clean_qts(t_cmd *cmdlist)
// {
//     int i;

//     i = 0;
//     while(cmdlist->argv[i])
//     {
//         removeqt()
//     }
// }

int check_quotes(char *str,char c)
{
    int i;
    int q;

    q = 0;
    i = 0;
    while(str[i])
    {
        if(str[i] == c)
            q++;
        i++;
    }

    if(q % 2 != 0)
        return -1;
    else 
        return q;
}

char	**freearr(char **ptr)
{
    int	i;
	// int j;

	// j = 0;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}
