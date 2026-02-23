#include "minishell.h"

static int	countwd(char const *s, char c,char quote)
{
	int	counter;
	int	isword;
	// int	i;
    int qt;

	// i = 0;
	counter = 0;
	isword = 0;
    qt = 0;
	while (*s)
	{
        if(*s == quote)
        {
            qt = !qt;
            s++;
            continue;
        }
		if (*s != c && !isword ) 
		{                                 
			isword = 1;
			counter++;
		}
		else if (*s == c && !qt)
		    isword = 0;
		s++;
	}
	return (counter);
}

static int	token_len(char const *s, char c,char quote)
{
	int	i;
    int qt;

    qt = 0;
	i = 0;
	while (s[i])
    {
        if(s[i] == quote)
            qt = !qt;
        if(s[i] == c && !qt)
            break;     
	i++;
    }
	return (i);
}

static char	*extract_word(char const *s, char c,char quote)
{
	char	*neword;
	int		i;
    int j;

    j = 0;
	i = 0;
	neword = (char *)malloc(token_len(s, c,quote) + 1);
	if (!neword)
        return (NULL);
    while (i < token_len(s,c,quote))
	{
        // if(s[i] == quote)
        // {
        //     i++;
        //     continue;
        // }
        neword[j++] = s[i++];
	}
	neword[j] = '\0';
	return (neword);
}


char	**sep(char const *s, char c,char quote)
{
    char **arr;
    int i;
    
    i = 0;
    arr = malloc(sizeof(char *) * (countwd(s, c,quote) + 1));
    if (!arr)
        return NULL;

    while (*s)
    {
        while (*s == c)
            s++;
        if (!*s)
            break;
        arr[i++] = extract_word(s, c,quote);
        s += token_len(s, c,quote);
    }
    arr[i] = NULL;
    return arr;
}


void print_split(char **arr) 
{
    if(!arr)
        return ;
    int i;
    
    i = 0;
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

