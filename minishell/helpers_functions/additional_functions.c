/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 21:43:19 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/11 01:21:24 by mohamed          ###   ########.fr       */
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
    char    *has_value;
    int len;
    
    len = 0;
    i = 0;
    while (env->envp[i])
    {
        has_value = ft_strchr(env->envp[i],'=');
        if (has_value)
        {
            len = has_value - env->envp[i];
            ft_putstr("declare -x ");
            write(1,env->envp[i],len);
            write(1,"=\"",2);
            write(1,has_value + 1,ft_strlen(has_value + 1));
            write(1,"\"",1);
            write(1,"\n",1);
        }
        else
        {
            ft_putstr("declare -x ");
            write(1, env->envp[i], ft_strlen(env->envp[i]));
            write(1, "\n", 1);
        }
        i++;  
    }
    return (0);
}
int is_builtin(const char *s)
{
    if (!s || !*s)
        return (0);
    return (ft_strcmp((char *)s, "echo") == 0
        ||  ft_strcmp((char *)s, "cd") == 0
        ||  ft_strcmp((char *)s, "pwd") == 0
        ||  ft_strcmp((char *)s, "export") == 0
        ||  ft_strcmp((char *)s, "unset") == 0
        ||  ft_strcmp((char *)s, "env") == 0
        ||  ft_strcmp((char *)s, "exit") == 0);
}

int decode_wait_status(int status)
{
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    return (1);
}

int    wait_for_all(t_pipes *pipes)
{
    int status;
    int i;
    int last_status;

    i = 0;
    last_status = 0;
    while(i < pipes->cmds_length)
    {
        waitpid(pipes->pids[i],&status,0);
        if (i == pipes->cmds_length - 1)
            last_status = status;
        i++;
    }
    return (decode_wait_status(last_status));
}

int ft_strcmp(char *str,char *str2)
{
    int i;

    i = 0;
    while (str[i] && str2[i] && str[i] == str2[i])
        i++;
    return ((unsigned char)str[i] - (unsigned char)str2[i]);
}
