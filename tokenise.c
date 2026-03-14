#include "minishell.h"

char **handle_pr(char **str)
{
    int     i;
    int x;
    char    **tok = malloc(sizeof(char *) * 1024);
    if (!tok)
        return NULL;
    
    i = 0;
    x = 0;
    while (str[i])
    {
        int j = 0;
        int start = 0;
        int in_sqt = 0;
        int in_dqt = 0;

        while (str[i][j])
        {
            if (str[i][j] == '\'' && !in_dqt)
                in_sqt = !in_sqt;
            else if (str[i][j] == '"' && !in_sqt)
                in_dqt = !in_dqt;

            else if (!in_sqt && !in_dqt
                && (str[i][j] == '|' || str[i][j] == '<' || str[i][j] == '>'))
            {
                if (j > start)
                    tok[x++] = ft_substr(str[i], start, j - start);

                if ((str[i][j] == '<' || str[i][j] == '>')
                    && str[i][j + 1] == str[i][j])
                {
                    tok[x++] = ft_substr(str[i], j, 2);
                    j += 2;
                }
                else
                {
                    tok[x++] = ft_substr(str[i], j, 1);
                    j += 1;
                }
                start = j;
                continue;
            }
            j++;
        }
        if (j > start)
            tok[x++] = ft_substr(str[i], start, j - start);
        i++;
    }
    tok[x] = NULL;
    return (tok);
}

char **tokenise(char *line)
{
    char  **seperated;
    char **tokenised;   
    if(check_quotes(line,'"') < 0 || check_quotes(line,'\'') < 0) //check on unclosed quotes
    {
        fprintf(stderr,"unclosed quotes!!!\n");
        return NULL;
    }
    if(check_quotes(line,'"') > 0)  //if quotes are double you pass the double
        seperated = sep(line,' ','"');
    else
        seperated = sep(line,' ','\''); // any other case? we pass the single
    if(!seperated)
        return NULL;
    tokenised = handle_pr(seperated);
    freearr(seperated);
    if(!tokenised)
        return NULL;
    if (handled_errors(tokenised,0,0,0,0))
        print_split(tokenised);
    else
    {
        printf("error\n");
        freearr(tokenised);
        return NULL;
    }
    // print_split(tokenised);
    return(tokenised);
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