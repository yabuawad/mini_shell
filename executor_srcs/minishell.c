/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:45:04 by mohamed           #+#    #+#             */
/*   Updated: 2026/02/28 22:49:35 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  before_execution(int argc, char **argv, char **envp ,t_env *pipeline)
{
    (void)argc;
    (void)argv;
    pipeline->envp = ft_envdup(envp);
    if (!pipeline->envp)
    {
        ft_putendl_fd("malloc failed\n",2);
        return (0);
    }
    pipeline->last_exit_status = 0;
    pipeline->cmd_head = NULL;
    return (1);
}
static void  after_execution(char *line,t_env *pipeline)
{
    if (pipeline->cmd_head)
            free_commands(pipeline->cmd_head);
        pipeline->cmd_head = NULL;
        free(line);
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
static int status_value(t_cmd *cmd,t_env *pipeline)
{
    int status;
    
    if (cmd -> redirs)
        status = check_redirection(cmd, pipeline);
    else if (is_builtin(cmd->argv[0]))
        status = execute_builtin(cmd, pipeline);
    else if (!cmd->argv || !cmd->argv[0])
        status = -2; 
    else
        status = execute_command(cmd, pipeline);
    return (status);
}
static void execute_pipeline(t_env *pipeline)
{
    t_cmd   *cmd;
    int status;
    
    if (!pipeline || !pipeline->cmd_head)
        return;
    cmd = pipeline->cmd_head;
    while (cmd)
    {
        if (cmd->has_pipe == 1)
        {
            pipeline->last_exit_status = apply_pipe(cmd,pipeline);
            while (cmd && cmd->has_pipe == 1)
                cmd = cmd->next;
            if (cmd)
                cmd = cmd->next; 
        }
        else
        {
            status = status_value(cmd,pipeline);
            if (status != -2)
                pipeline->last_exit_status = status;
            cmd = cmd->next;
        }
    }
}

int main(int argc, char **argv, char **envp)
{
    char    *line;
    t_env   pipeline;

    if (!before_execution(argc,argv,envp,&pipeline))
        return (0);
    while (1)
    {
        line = readline("minishell $ ");
        if (!line)
        {
            printf("exit\n");
            break;
        } 
        if (*line)
            add_history(line);   
        pipeline.cmd_head = parse_input(line);
        execute_pipeline(&pipeline);
        after_execution(line,&pipeline);
    }
    free_2d(pipeline.envp);
    return (0);
}
