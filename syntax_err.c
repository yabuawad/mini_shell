#include "minishell.h"

// char **handled_errors(char **tokens)
// {

// }
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