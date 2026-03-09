/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 21:43:19 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/09 06:07:00 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_2d(char **array)
{
    int i;

    if (!array)
        return ;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}
int ft_2dstrlen(char **str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return (i);
}
void print_exit(char *message, int exit_value) 
{
    ft_putendl_fd(message, 2);
    exit(exit_value);
}

int print_export(t_env *env)
{
    int i;

    i = 0;
    while (env->envp[i])
    {
        printf("declare -x %s\n", env->envp[i]);
        i++;  
    }
    return (0);
}
int is_builtin(const char *s)
{
    if (!s || !*s)
        return 0;
    return (ft_strcmp((char *)s, "echo") == 0
        ||  ft_strcmp((char *)s, "cd") == 0
        ||  ft_strcmp((char *)s, "pwd") == 0
        ||  ft_strcmp((char *)s, "export") == 0
        ||  ft_strcmp((char *)s, "unset") == 0
        ||  ft_strcmp((char *)s, "env") == 0
        ||  ft_strcmp((char *)s, "exit") == 0);
}

int    wait_for_all(t_pipes *pipes)
{
    int status;
    int i;

    i = 0;
    while(i < pipes->cmds_length)
    {
        waitpid(pipes->pids[i],&status,0);
        i++;
    }
    return (WEXITSTATUS(status)); // ?
}

int ft_strcmp(char *str,char *str2)
{
    int i;

    i = 0;
    while (str[i] && str2[i] && str[i] == str2[i])
        i++;
    return ((unsigned char)str[i] - (unsigned char)str2[i]);
}
