#include "minishell.h"

char *removeqt(char *str)
{
    char *quoteless = malloc(ft_strlen(str)* sizeof(char));
    if(!quoteless)
        return NULL;
    int i;
    int j;

    j = 0;
    i = 0;
    while(str[i])
    {
        // if(str[i] == '"' || str[i] == '\'' )
        // {
        //     i++;
        // }
        // else        
            quoteless[j++] = str[i++];  
    }
    quoteless[j] = '\0';
    return (quoteless);
}

// char	**freearr(char **ptr)
// {
//     int	i;
// 	// int j;

// 	// j = 0;
// 	i = 0;
// 	while (ptr[i])
// 	{
// 		free(ptr[i]);
// 		i++;
// 	}
// 	free(ptr);
// 	return (NULL);
// }


// void append_token(t_token **head,t_token **tail,t_token *newtok)
// {
//     if(!*head)
//     {
//         *head = newtok;
//         *tail = newtok;
//     }
//     else
//         (*tail)->next = newtok;
//         *tail = newtok;
//     newtok->next = NULL;
// }