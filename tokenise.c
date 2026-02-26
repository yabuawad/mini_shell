#include "minishell.h"

// char	**freearr(char **ptr)
// {
// 	int	i;
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
            if(tokenised[i][j] == '|' && ft_strlen(tokenised[i]) > 1)
                counter += 2;
            j++;
        }
        counter++;
        i++;
    }
    return(counter);
}

// char pipe
// char **check_pipes(char **tokenised,int i,int x) // this function is for post seperation pipe check
// {       //for example the command echo "hello"|grep h works even tho there are no spaces so this function is to seperate pipes from cmds 
//     int j;
//     int found;
//     char **pipedtok;
//     int qtfound;

//     pipedtok = malloc(sizeof(char *) * (count_tok(tokenised) + 1));
//     if (!pipedtok)
//         return NULL;

//     while (tokenised[i])
//     {
//         qtfound = 0;
//         j = 0;
//         found = 0;
//         while (tokenised[i][j])
//         {
//             if(check_quotes(tokenised[i],'"') > 0 || check_quotes(tokenised[i],'\'') > 0)
//             {
//                 qtfound = 1;
//                 j++;
//             }
//             else if (tokenised[i][j] == '|' && ft_strlen(tokenised[i]) > 1)
//             {
//                 if (j > 0)
//                     pipedtok[x++] = ft_substr(tokenised[i], 0, j);
//                 pipedtok[x++] = ft_strdup("|");
//                 if (tokenised[i][j + 1])
//                     pipedtok[x++] = ft_strdup(tokenised[i] + j + 1);
//                 found = 1;
//                 break;
//             }
//             j++;
//         }
//         if(qtfound)
//             pipedtok[x++] = ft_strdup(removeqt(tokenised[i]));
//         else if(!found)
//             pipedtok[x++] = ft_strdup(tokenised[i]);
//         i++;
//     }
//     // if(pipedtok[x -1] == '"')
//         // x--;
//     pipedtok[x] = NULL;
//     return (pipedtok);
// }

// char **check_pipes(char **tokenised, int i, int x)
// {
//     int j;
//     int found;
//     char **pipedtok;
//     int in_squote;
//     int in_dquote;

//     pipedtok = malloc(sizeof(char *) * (count_tok(tokenised) + 1));
//     if (!pipedtok)
//         return NULL;

//     while (tokenised[i])
//     {
//         j = 0;
//         found = 0;
//         in_squote = 0;
//         in_dquote = 0;

//         while (tokenised[i][j])
//         {
//             if (tokenised[i][j] == '\'' && !in_dquote)
//                 in_squote = !in_squote;
//             else if (tokenised[i][j] == '"' && !in_squote)
//                 in_dquote = !in_dquote;

//             else if (tokenised[i][j] == '|' && !in_squote && !in_dquote)
//             {
//                 if (j > 0)
//                     pipedtok[x++] = ft_substr(tokenised[i], 0, j);
//                 pipedtok[x++] = ft_strdup("|");
//                 if (tokenised[i][j + 1])
//                     pipedtok[x++] = ft_strdup(tokenised[i] + j + 1);
//                 found = 1;
//                 break;
//             }
//             j++;
//         }

//         if (!found)
//             pipedtok[x++] = ft_strdup(tokenised[i]);

//         i++;
//     }

//     pipedtok[x] = NULL;
//     return (pipedtok);
// }
char **check_pipes(char **tokenised,int i,int x)
{
    char **out;
    // int i = 0, x = 0;

    out = malloc(sizeof(char *) * (count_tok(tokenised) + 1));
    if (!out)
        return NULL;

    while (tokenised[i])
    {
        int j = 0, start = 0;
        int in_s = 0, in_d = 0;

        while (tokenised[i][j])
        {
            if (tokenised[i][j] == '\'' && !in_d)
                in_s = !in_s;
            else if (tokenised[i][j] == '"' && !in_s)
                in_d = !in_d;

            else if (tokenised[i][j] == '|' && !in_s && !in_d)
            {
                if (j > start)
                    out[x++] = ft_substr(tokenised[i], start, j - start);
                out[x++] = ft_strdup("|");
                start = j + 1;
            }
            j++;
        }

        if (j > start)
            out[x++] = ft_substr(tokenised[i], start, j - start);

        i++;
    }

    out[x] = NULL;
    return out;
}

char **check_redir(char **str, int i, int j, int x)
{
    int in_sqt, in_dqt, found;
    char **tok = malloc(sizeof(char *) * (count_tok(str) + 1));

    if (!tok)
        return NULL;

    while (str[i])
    {
        j = 0;
        in_sqt = 0;
        in_dqt = 0;
        found = 0;

        while (str[i][j])
        {
            if (str[i][j] == '\'' && !in_dqt)
                in_sqt = !in_sqt;
            else if (str[i][j] == '"' && !in_sqt)
                in_dqt = !in_dqt;

            else if (!in_sqt && !in_dqt && (str[i][j] == '>' || str[i][j] == '<'))
            {
                found = 1;
                if (j > 0)
                    tok[x++] = ft_substr(str[i], 0, j);

                if (str[i][j + 1] == str[i][j])
                {
                    tok[x++] = ft_substr(str[i], j, 2);
                    if (str[i][j + 2])
                        tok[x++] = ft_strdup(str[i] + j + 2);
                }
                else
                {
                    tok[x++] = ft_substr(str[i], j, 1);
                    if (str[i][j + 1])
                        tok[x++] = ft_strdup(str[i] + j + 1);
                }
                break;
            }
            j++;
        }
        if (!found)
            tok[x++] = ft_strdup(str[i]);
        i++;
    }
    tok[x] = NULL;
    return tok;
}
void  tokenise(char *line)
{
    char  **seperated;
    char **piped;
    char **redirected;
    // char **errorless;    
    if(check_quotes(line,'"') < 0 || check_quotes(line,'\'') < 0) //check on unclosed quotes
    {
        fprintf(stderr,"unclosed quotes!!!\n");
        return;
    }
    if(check_quotes(line,'"') > 0)  //if quotes are double you pass the double
        seperated = sep(line,' ','"');
    else
        seperated = sep(line,' ','\''); // any other case? we pass the single
    redirected = check_redir(seperated,0,0,0);
    piped = check_pipes(redirected,0,0);
    if(handled_errors(piped,0,0,0,0))
        print_split(piped);
    else
        printf("error\n");
    freearr(seperated);
    freearr(redirected);
    freearr(piped);
    // errorless = handled_errors(piped,0);
}

