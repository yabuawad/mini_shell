/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:25:18 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/04 18:27:44 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void    child_execution(t_cmd *cmd, t_env *shell)
{
    int status;
    char    *path;
    
    apply_redirections(cmd->redirs);
    if (!cmd->argv || !cmd->argv[0])
        exit(0);
    if (is_builtin(cmd->argv[0]))
    {
        status = execute_builtin(cmd, shell);
        exit(status);
    }
    path = find_command_path(find_full_path(shell->envp), cmd->argv[0]);
    if (!path)
        path_error(cmd);
    execve(path, cmd->argv, shell->envp);
    perror("execve");
    free(path);
    exit(127);
}
int check_redirection(t_cmd *cmd,t_env *shell)
{
    int status;
    pid_t pid;
    
    if (!cmd || !cmd->redirs)
        return (0);
    pid = fork();
    if (pid == -1)
    {
        perror("minishell: fork");
        return (1);
    }
    if (pid == 0)
        child_execution(cmd, shell);
    waitpid(pid, &status, 0);
    return (WEXITSTATUS(status));
}