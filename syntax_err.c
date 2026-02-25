#include "minishell.h"

// int check_word(char *tokens,int i)
// {
//     i++;
//     while(tokens[i] == ' ' && tokens[i])
//         i++;
//     if((tokens[i] >= 'a' && tokens[i] <= 'z'))
//         return 1;
//     else
//         return 0;
// }
// int check_red(char *tokens,int i)
// {
//     i++;
//     while(tokens[i] == ' ')
//         i++;
//     if(tokens[i] == '>' && tokens[i + 1] == '>')
//         i++;
//     if(tokens[i] == '<' && tokens[i + 1] == '<')
//         i++;
//     if(!check_word(tokens,i))
//         return 0;
//     else 
//         return 1;
// }
// int check_redcmd(char *tokens,int i)
// {
//     int j;

//     j = 0;
//     if(i == 0)
//         return 0;
//     while(j < i)
//     {
//         if(tokens[j] == ' ')
//             j++;
//     }
//     if(j == i)
//         return 0;
//     else
//         return 1;
// }

int print_err(char *err_msg)
{
    printf("%s\n",err_msg);
    return 0;
}

// int error_cases(char *tokens,int dqt,int sqt,int i,int j)
// {
//     while(tokens[j])
//     {
//         if(tokens[j] == '"')
//             dqt = !dqt;
//         else if(tokens[j] == '\'')
//             sqt = !sqt;
//         else if(!dqt && !sqt)
//         {
//             if((j == 0 && tokens[j] == '|'))
//                 return (print_err("pipe at end/beggining of cmd"));
//             if(tokens[j] == '|' && (tokens[j + 1] == '>' || tokens[j + 1] == '<'))
//                 return (print_err("redirection after a pipe"));
//             if(tokens[j] == '|' && (check_word(tokens,j) != 0))
//                 return (print_err("pipe not followed by a cmd"));
//             if((tokens[j] == '>' || tokens[j] == '<')&& !check_red(tokens,j))
//                 return (print_err("redirection not followed by a cmd"));
//             if((tokens[j] == '>' || tokens[j] == '<') && !check_redcmd(tokens,j))
//                 return (print_err("redirection without a previous cmd"));
//         }
//         j++;
//     }
//     return 1;
// }

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
                if(tokens[i][j] == '|' && (i == 0))
                    return (print_err("pipe at end/beggining of cmd"));
                // if(tokens[j] == '|' && (tokens[j + 1] == '>' || tokens[j + 1] == '<'))
                //     return (print_err("redirection after a pipe"));
                // if(tokens[j] == '|' && (check_word(tokens,j) != 0))
                //     return (print_err("pipe not followed by a cmd"));
                // if((tokens[j] == '>' || tokens[j] == '<')&& !check_red(tokens,j))
                //     return (print_err("redirection not followed by a cmd"));
                // if((tokens[j] == '>' || tokens[j] == '<') && !check_redcmd(tokens,j))
                //     return (print_err("redirection without a previous cmd"));
            }
            j++;
        }
    i++;
    }
    return 1;
}
/*
errorsto handle:
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