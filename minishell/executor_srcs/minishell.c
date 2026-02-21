/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:45:04 by mohamed           #+#    #+#             */
/*   Updated: 2026/02/21 03:45:46 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int is_builtin(const char *s)
{
    if (!s || !*s)
        return 0;
    return (strcmp(s, "echo") == 0
        ||  strcmp(s, "cd") == 0
        ||  strcmp(s, "pwd") == 0
        ||  strcmp(s, "export") == 0
        ||  strcmp(s, "unset") == 0
        ||  strcmp(s, "env") == 0
        ||  strcmp(s, "exit") == 0);
}

static void execute_pipeline(t_env *pipeline)
{
    t_cmd   *cmd;
    int     status;
    
    if (!pipeline || !pipeline->cmd_head)
        return;
    cmd = pipeline->cmd_head;
    while (cmd)
    {
        if (!cmd->argv || !cmd->argv[0])
        {
            cmd = cmd->next;
            continue;
        }
        if (cmd->redirs && cmd->redirs->type)
            status = check_redirection(cmd, pipeline);
        else if (is_builtin(cmd->argv[0]))
            status = execute_builtin(cmd, pipeline);
        else
            status = execute_command(cmd, pipeline);
        pipeline->last_exit_status = status;
        cmd = cmd->next;
    }
}

int main(int argc, char **argv, char **envp)
{
    char    *line;
    t_env   pipeline;

    (void)argc;
    (void)argv;
    pipeline.envp = ft_envdup(envp);
    pipeline.last_exit_status = 0;
    pipeline.cmd_head = NULL;
    while (1)
    {
        line = readline("minishell$ ");
        if (!line)
        {
            printf("exit\n");
            break;
        } 
        if (*line)
            add_history(line);   
        pipeline.cmd_head = parse_input(line);
        execute_pipeline(&pipeline);
        if (pipeline.cmd_head)
            free_commands(pipeline.cmd_head);
        pipeline.cmd_head = NULL;
        free(line);
    }
    return (0);
}
