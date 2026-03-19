/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 21:43:19 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/19 02:56:47 by mohamed          ###   ########.fr       */
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

static void free_redirections(t_redir *redirs)
{
    t_redir *current;
    t_redir *temp;

    current = redirs;
    while (current)
    {
        temp = current->next_redirection;
		if (current->fd != -1)
			close(current->fd);
        if (current->target)
            free(current->target);
        free(current);
        current = temp;
    }
}

static void free_argv(char **argv)
{
    int i;

    if (!argv)
        return;
    i = 0;
    while (argv[i])
    {
        free(argv[i]);
        i++;
    }
    free(argv);
}
void free_commands(t_cmd *cmd)
{
    t_cmd *current;
    t_cmd *temp;

    current = cmd;
    while (current)
    {
        temp = current->next;
        if (current->argv)
            free_argv(current->argv);
        if (current->redirs)
            free_redirections(current->redirs);
        free(current);
        current = temp;
    }
}
