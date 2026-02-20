/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 21:30:14 by mohamed           #+#    #+#             */
/*   Updated: 2026/02/19 22:15:41 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int execute_export(t_cmd *cmd,t_env *env)
{
    int i;
    char    *splitted;
    
    i = 0;
    if (!cmd->argv[1])
    {
        while (env->envp[i])
        {
            splitted = ft_strchr(env->envp[i],'=');
            if (splitted)
            {
                *splitted = '\0';   
                printf("declare -x %s=\"%s\"\n",env->envp[i],splitted+1);
                *splitted = '=';
            }
            else
                printf("declare -x %s\n",env->envp[i]);
            i++;
        }
        return (0);
    }




















    
    i = 1;
    while (cmd->argv[i])
    {
        if (!ft_isalpha(cmd->argv[i][0]) && cmd->argv[i][0] != '_')
        {
            ft_putstr_fd("export: not a valid identifier\n",2);
            return (1);
        }
        splitted = ft_strchr(cmd->argv[i],'=');
        if (splitted)
        {
            
        }
        else
        i++;
    }
    return (0);
}