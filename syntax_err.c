#include "minishell.h"

                  
int check_word(char *tokens,int i)
{
    while(tokens[i] == ' ' && tokens[i])
        i++;
    if(ft_isalpha(tokens[i]))
        return 1;
    if(tokens[i] == '"' || tokens[i] == '\'')
     {
        char c = tokens[i];
        i++;
        while(tokens[i] != c)
        {
            if(!ft_isalpha(tokens[i]))
                return 0;
            i++;
        }
        return 1;
    }
    else
        return 0;
}                    
                        
int check_red(char *tokens,int i)
{
    if(!tokens)
        return 0;
    while(tokens[i] == ' ')
        i++;
    if(!tokens[i])
        return 0;
    if(tokens[i] == '>' || tokens[i] == '<' || tokens[i] == '|')
        return 0;
    else 
        return 1;
}

int print_err(char *err_msg)
{
    printf("%s\n",err_msg);
    return 0;
}
int handled_errors(char **tokens,int i,int j,int dqt,int sqt)
{
    while(tokens[i])
    {
        j = 0;
        while(tokens[i][j])
        {
            if(tokens[i][j] == '"')
                dqt = !dqt;
            else if(tokens[i][j] == '\'')
                sqt = !sqt;
            else if(!dqt && !sqt)
            {
                if(tokens[i][j] == '|' && (i == 0 || !tokens[i+ 1])) 
                    return (print_err("pipe at end/beggining of cmd"));
                // if(tokens[i][j] == '|' && !check_word(tokens[i + 1],0))
                //     return (print_err("pipe not followed by a cmd"));
                if((tokens[i][j] == '>' || tokens[i][j] == '<')&& !check_red(tokens[i + 1],0))  
                    return (print_err("redirection file invalid"));
                if((tokens[i][j] == '>' || tokens[i][j] == '<') && i == 0)
                    return(print_err("redirection with no previous cmd/file"));
            }
            j++;
        }
    i++;
    }
    return 1;
}


/*
errors to handle:
1.pipes at begining or end of cmd 
    // | ls 
    // ls |
2.Pipe after redirection
    //ls > | wc
    //ls < | wc
3.Between two |, there must be at least one word
    // ls || grep h
4. redirections withput a target
    // ls >
    // ls <
    // ls >>
    // ls <<
5.redirection followed by operater
    // ls < >
    //ls > | 
    //ls > << ...etc
6.multi redirections with no words
    //ls >< file
    //ls >>< file
7.empty commands
    //ls | | wc
    //ls |    | wc
8.redirection without a cmd
    //> file
    //< input
9.operater chains
    //ls >>> file
    //ls <<< file
10.<< must be followed by a word delimiter
    // cat <<
11.
    */