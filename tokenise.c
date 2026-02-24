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

char **check_pipes(char **tokenised, int i, int x)
{
    int j;
    int found;
    char **pipedtok;
    int in_squote;
    int in_dquote;

    pipedtok = malloc(sizeof(char *) * (count_tok(tokenised) + 1));
    if (!pipedtok)
        return NULL;

    while (tokenised[i])
    {
        j = 0;
        found = 0;
        in_squote = 0;
        in_dquote = 0;

        while (tokenised[i][j])
        {
            if (tokenised[i][j] == '\'' && !in_dquote)
                in_squote = !in_squote;
            else if (tokenised[i][j] == '"' && !in_squote)
                in_dquote = !in_dquote;

            else if (tokenised[i][j] == '|' && !in_squote && !in_dquote)
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
// char **redir(char **str,char red,char **tok)
// {

// }
char **check_redir(char **str,int i,int j ,int x)
{
    int found;
    int in_dqt;
    int in_sqt;
    char **tok;

    tok = malloc(sizeof(char *) * (count_tok(str) + 1));
    if (!tok)
    return NULL;
    while(str[i])
    {
        j = 0;
        found = 0;
        in_dqt = 0;
        in_sqt = 0;
        while(str[i][j])
        {
            if (str[i][j] == '\'' && !in_dqt)
                in_sqt = !in_sqt;
            else if (str[i][j] == '"' && !in_sqt)
                in_dqt = !in_dqt;
            if(str[i][j] == '>' && !in_sqt && !in_dqt)
            {
                found = 1;
                if (j > 0)
                    tok[x++] = ft_substr(str[i],0,j);
                if(str[i][j+1] == '>')
                {
                    tok[x++] = ft_strdup(">>");
                    if(str[i][j +1])
                    tok[x++] = ft_strdup(str[i] +j + 2);
                }
                else
                 {   
                    tok[x++] = ft_strdup(">");
                    if(str[i][j +1])
                    tok[x++] = ft_strdup(str[i] + j + 1);
                }
            }
              if(str[i][j] == '<' && !in_sqt && !in_dqt)
            {
                found = 1;
                tok[x++] = ft_substr(str[i],0,j);
                if(str[i][j+1] == '<')
                {
                    tok[x++] = ft_strdup("<<");
                    if(str[i][j +1])
                        tok[x++] = ft_strdup(str[i] +j + 2);
                }
                else
                {
                    if (j > 0)
                        tok[x++] = ft_strdup("<");
                    if(str[i][j +1])
                        tok[x++] = ft_strdup(str[i] + j + 1);
                }
            }
        j++;
        }
        if(!found)
            tok[x++] = ft_strdup(str[i]);
        i++;
    }
    tok[x] = NULL;
    return (tok);
}
void  tokenise(char *line)
{
    char  **tokenised;
    char **extratok;    
    if(check_quotes(line,'"') < 0 || check_quotes(line,'\'') < 0) //check on unclosed quotes
    {
        fprintf(stderr,"unclosed quotes!!!\n");
        return;
    }
    if(check_quotes(line,'"') > 0)  //if quotes are double you pass the double
        tokenised = sep(line,' ','"');
    else
        tokenised = sep(line,' ','\''); // any other case? we pass the single
    extratok = check_pipes(check_redir(tokenised,0,0,0),0,0);
    freearr(tokenised);
    print_split(extratok);
    // makelist(check_pipes(tokenised));
    // freearr(extratok);
    // return (extratok);
}

