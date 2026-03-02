/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 21:43:19 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/02 15:51:31 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    return (ft_strncmp(s, "echo",5) == 0
        ||  ft_strncmp(s, "cd",3) == 0
        ||  ft_strncmp(s, "pwd",4) == 0
        ||  ft_strncmp(s, "export",7) == 0
        ||  ft_strncmp(s, "unset",6) == 0
        ||  ft_strncmp(s, "env",4) == 0
        ||  ft_strncmp(s, "exit",5) == 0);
}
