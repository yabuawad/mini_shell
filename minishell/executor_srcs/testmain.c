/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:14:27 by malhassa          #+#    #+#             */
/*   Updated: 2026/02/18 13:59:42 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_env   env;
    t_cmd   cmd1, cmd2, cmd3, cmd4, cmd5;
    t_redir redir1, redir2;
    int     result;

    (void)argc;
    (void)argv;
    (void)cmd4,(void)cmd5,(void)redir1,(void)redir2;
    
    env.envp = envp;
    env.last_exit_status = 0;

    printf("=== EXECUTOR TEST SUITE ===\n\n");

    // Test 1: echo builtin
    printf("TEST 1: echo hello world\n");
    {
        char *argv1[] = {"echo", "hello", "world", NULL};
        cmd1.argv = argv1;
        cmd1.redirs = NULL;
        cmd1.next = NULL;
        result = execute_builtin(&cmd1, &env);
        printf("\nExit status: %d\n\n", result);
    }

    // Test 2: pwd builtin
    printf("TEST 2: pwd\n");
    {
        char *argv2[] = {"pwd", NULL};
        cmd2.argv = argv2;
        cmd2.redirs = NULL;
        cmd2.next = NULL;
        result = execute_builtin(&cmd2, &env);
        printf("Exit status: %d\n\n", result);
    }

    // Test 3: env builtin
    printf("TEST 3: env (first 3 entries)\n");
    {
        char *argv3[] = {"env", NULL};
        cmd3.argv = argv3;
        cmd3.redirs = NULL;
        cmd3.next = NULL;
        result = execute_builtin(&cmd3, &env);
        printf("Exit status: %d\n\n", result);
    }

    // Test 4: echo with output redirection (structure only)
    printf("TEST 4: echo test > /tmp/test_output.txt (structure ready)\n");
    {
        redir1.fd = -1;
        redir1.target = "/tmp/test_output.txt";
        redir1.type = R_OUT;
        redir1.next_redirection = NULL;

        char *argv4[] = {"echo", "redirected test", NULL};
        cmd4.argv = argv4;
        cmd4.redirs = &redir1;
        cmd4.next = NULL;
        
        printf("Structure created - awaiting redirection implementation\n\n");
    }

    // Test 5: External command structure
    printf("TEST 5: ls -la /tmp (structure ready)\n");
    {
        char *argv5[] = {"ls", "-la", "/tmp", NULL};
        cmd5.argv = argv5;
        cmd5.redirs = NULL;
        cmd5.next = NULL;
        
        printf("Structure created - awaiting external execution implementation\n\n");
    }

    printf("=== END TEST SUITE ===\n");
    return (0);
}