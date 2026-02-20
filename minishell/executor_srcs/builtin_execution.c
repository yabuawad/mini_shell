/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:09:18 by malhassa          #+#    #+#             */
/*   Updated: 2026/02/17 22:41:52 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_cd(t_cmd *cmd)
{
    char *home;
    
    if (!cmd->argv[1])
    {
        home = getenv("HOME");
        if (!home)
        {
            write(2, "cd: HOME not set\n", 17);
            return (1);
        }
        return (chdir(home));
    }
    if (chdir(cmd->argv[1]) == -1)
    {
        perror("cd");
        return (1);
    }
    return (0);
}
int execute_echo(t_cmd *cmd)
{
    int i;
    int newline;
    
    i = 1;
    newline = 1;
    if (cmd->argv[1] && ft_strncmp(cmd->argv[1], "-n", 2) == 0)
    {
        newline = 0;
        i++;
    }
    while (cmd->argv[i])
    {
        printf("%s", cmd->argv[i]);
        if (cmd->argv[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        write(1, "\n", 1);
    return (0);
}
int execute_pwd(void)
{
    char    pwd[4096];

    if (getcwd(pwd,sizeof(pwd)) == NULL)
    {
        perror("pwd");
        return (1);
    }
    printf("%s\n",pwd);
    return (0);
}
int execute_env(t_cmd *cmd , t_env *env)
{
    int i;
    
    if (cmd->argv[1])
    {
        write(2,"env: '",6);
        write(2,cmd->argv[1],ft_strlen(cmd->argv[1]));
        write(2, "’: No such file or directory\n", 29);
        return (127);
    }
    i = 0;
    while(env->envp[i])
    {
        write (1,env->envp[i],ft_strlen(env->envp[i]));
        write(1,"\n",1);
        i++;
    }
    return (0);
}

int execute_exit(t_cmd *cmd,t_env *env)
{
    int exit_c;

    exit_c = 0;
    if (cmd->argv[1])
        exit_c = ft_atoi(cmd->argv[1]);
    else if (env)
        exit_c = env->last_exit_status;
    exit(exit_c);
    return (0);
}



