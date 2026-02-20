#include "minishell.h"

static int	countwd(char const *s, char c)
{
	int	counter;
	int	isword;
	int	i;
    int qt;

	i = 0;
	counter = 0;
	isword = 0;
    qt = 0;
	while (s[i])
	{
        if(s[i] == '"' )
        {
            qt = !qt;
            i++;
            continue;
        }
		if (s[i] != c && !isword ) 
		{                                 
			isword = 1;
			counter++;
		}
		else if (s[i] == c && !qt)
		    isword = 0;
		i++;
	}
	return (counter);
}

static int	token_len(char const *s, char c)
{
	int	i;
    int qt;

    qt = 0;
	i = 0;
	while (s[i])
    {
        if(s[i] == '"')
            qt = !qt;
        if(s[i] == c && !qt)
            break;     
	i++;
    }
	return (i);
}

static char	*extract_word(char const *s, char c)
{
	char	*neword;
	int		i;
    int j;

    j = 0;
	i = 0;
	neword = (char *)malloc(token_len(s, c) + 1);
	if (!neword)
        return (NULL);
    while (i < token_len(s,c))
	{
        if(s[i] == '"')
        {
            i++;
            continue;
        }
        neword[j++] = s[i++];
	}
	neword[j] = '\0';
	return (neword);
}

// static char	**freeptr(char **ptr, int j)
// {
//     int	i;
    
// 	i = 0;
// 	while (i < j)
// 	{
//         free(ptr[i]);
// 		i++;
// 	}
// 	free(ptr);
// 	return (NULL);
// }

char	**sep(char const *s, char c)
{
    char **arr;
    int i = 0;

    arr = malloc(sizeof(char *) * (countwd(s, c) + 1));
    if (!arr)
        return NULL;

    while (*s)
    {
        while (*s == c)
            s++;
        if (!*s)
            break;
        arr[i++] = extract_word(s, c);
        s += token_len(s, c);
    }
    arr[i] = NULL;
    return arr;
}


void print_split(char **arr) {
    int i = 0;

    if (arr == NULL) {
        printf("NULL\n");
        return ;
    }

    while (arr[i] != NULL) {
        printf("[%s]\n", arr[i]);
        i++;
    }
    printf("----\n");
}

// int main(void) {
//     char **result;

//     result = ft_split("hello!",' ');
// 	print_split(result);

//     return (0);
// }