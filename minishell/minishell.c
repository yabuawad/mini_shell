/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:45:04 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/27 15:45:37 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  initialization(int argc, char **argv, char **envp ,t_env *shell)
{
    (void)argv;
  
    if (argc != 1)
    {
        ft_putendl_fd("more than one argument!",2);
        return (0);
    }
    shell->envp = ft_envdup(envp,0);
    if (!shell->envp)
    {
        ft_putendl_fd("malloc failed\n",2);
        return (0);
    }
    shell->last_exit_status = 0;
    shell->cmd_head = NULL;
    return (1);
}

static int get_status(t_cmd *cmd,t_env *shell)
{
    int status;
    
    if (cmd -> redirs)
        status = execute_with_redirections(cmd, shell);
    else if (!cmd->argv || !cmd->argv[0])
        status = -2; 
    else if (is_builtin(cmd->argv[0]))
        status = execute_builtin(cmd, shell);
    else
        status = run_command(cmd, shell);
    return (status);
}
static void run_command_list(t_env *shell)
{
    t_cmd   *cmd;
    int status;
    
    if (!shell || !shell->cmd_head)
        return;
    cmd = shell->cmd_head;
    while (cmd)
    {
        if (cmd->has_pipe == 1)
        {
            if (heredocs_with_pipes(cmd,&shell) == -1)
                return;
            shell->last_exit_status = apply_pipe(&cmd,shell);
        }
        else
        {
            if (heredocs_with_pipes(cmd,&shell) == -1)
                return;
            status = get_status(cmd,shell);
            if (status != -2)
                shell->last_exit_status = status;
        }
        if (cmd)
            cmd = cmd->next;
    }
}
static void run_minishell(t_env *shell)
{
    char    *line;
    
    init_signals();
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
        if (!apply_parse(line,shell))
            continue;
        run_command_list(shell);
        memory_cleanup(line,shell);
    }   
}

int main(int argc, char **argv, char **envp)
{   
    t_env   *shell;

    shell = malloc(sizeof(t_env));
    if (!shell)
        return (1);
    if (!initialization(argc,argv,envp,shell))
    {
        free(shell);
        return (1);
    }
<<<<<<< HEAD
    while (1)
    {
        line = readline("minishell $ ");
        if (!line)
        {
            printf("exit\n");
            exit(1); 
            // break;
        } 
        if (*line)
            add_history(line);   
        tokens = tokenise(line);
        if (!tokens)
        {
            free(line);
            continue;
        }
        shell->cmd_head = parse(tokens);
        freearr(tokens);
        if (shell->cmd_head)
        {
            expanded = expand(shell->cmd_head, shell->envp);
            if (expanded)
                free(expanded);
        }
        run_command_list(shell);
        memory_cleanup(line,shell);
    }
=======
    run_minishell(shell);
>>>>>>> 19fa583 (done)
    free_2d(shell->envp);
    free(shell);
    return (0);
}
