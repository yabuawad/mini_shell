/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:14:27 by malhassa          #+#    #+#             */
/*   Updated: 2026/02/20 17:37:49 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_env   env;
    t_cmd   cmd;
    int     result;

    (void)argc;
    (void)argv;
    
    env.envp = ft_envdup(envp);
    env.last_exit_status = 0;
    env.cmd_head = NULL;

    printf("=== MINISHELL EXPORT/UNSET TEST SUITE ===\n\n");

    // Test 1: export VAR=value
    printf("TEST 1: export MY_VAR=hello\n");
    {
        char *argv1[] = {"export", "MY_VAR=hello", NULL};
        cmd.argv = argv1;
        cmd.redirs = NULL;
        cmd.next = NULL;
        result = execute_builtin(&cmd, &env);
        printf("Exit status: %d\n\n", result);
    }

    // Test 2: env - check if MY_VAR appears
    printf("TEST 2: env (should show MY_VAR=hello)\n");
    {
        char *argv2[] = {"env", NULL};
        cmd.argv = argv2;
        result = execute_builtin(&cmd, &env);
        printf("\nExit status: %d\n\n", result);
    }

    // Test 3: export with no args (display all)
    printf("TEST 3: export (display all with declare -x format)\n");
    {
        char *argv3[] = {"export", NULL};
        cmd.argv = argv3;
        result = execute_builtin(&cmd, &env);
        printf("Exit status: %d\n\n", result);
    }

    // Test 4: export VAR=value with spaces
    printf("TEST 4: export TEST_VAR=hello world test\n");
    {
        char *argv4[] = {"export", "TEST_VAR=hello world test", NULL};
        cmd.argv = argv4;
        result = execute_builtin(&cmd, &env);
        printf("Exit status: %d\n\n", result);
    }

    // Test 5: export update existing variable
    printf("TEST 5: export MY_VAR=updated (updating existing)\n");
    {
        char *argv5[] = {"export", "MY_VAR=updated", NULL};
        cmd.argv = argv5;
        result = execute_builtin(&cmd, &env);
        printf("Exit status: %d\n\n", result);
    }

    // Test 6: env - check if MY_VAR is updated
    printf("TEST 6: env (MY_VAR should be 'updated')\n");
    {
        char *argv6[] = {"env", NULL};
        cmd.argv = argv6;
        result = execute_builtin(&cmd, &env);
        printf("\nExit status: %d\n\n", result);
    }

    // Test 7: export multiple variables at once
    printf("TEST 7: export VAR1=value1 VAR2=value2 VAR3=value3\n");
    {
        char *argv7[] = {"export", "VAR1=value1", "VAR2=value2", "VAR3=value3", NULL};
        cmd.argv = argv7;
        result = execute_builtin(&cmd, &env);
        printf("Exit status: %d\n\n", result);
    }

    // Test 8: unset single variable
    printf("TEST 8: unset VAR1\n");
    {
        char *argv8[] = {"unset", "VAR1", NULL};
        cmd.argv = argv8;
        result = execute_builtin(&cmd, &env);
        printf("Exit status: %d\n\n", result);
    }

    // Test 9: env - check if VAR1 is gone
    printf("TEST 9: env (VAR1 should be removed)\n");
    {
        char *argv9[] = {"env", NULL};
        cmd.argv = argv9;
        result = execute_builtin(&cmd, &env);
        printf("\nExit status: %d\n\n", result);
    }

    // Test 10: unset multiple variables
    printf("TEST 10: unset VAR2 VAR3 MY_VAR\n");
    {
        char *argv10[] = {"unset", "VAR2", "VAR3", "MY_VAR", NULL};
        cmd.argv = argv10;
        result = execute_builtin(&cmd, &env);
        printf("Exit status: %d\n\n", result);
    }

    // Test 11: env - check if all three are removed
    printf("TEST 11: env (VAR2, VAR3, MY_VAR should be removed)\n");
    {
        char *argv11[] = {"env", NULL};
        cmd.argv = argv11;
        result = execute_builtin(&cmd, &env);
        printf("\nExit status: %d\n\n", result);
    }

    // Test 12: export variable with special characters
    printf("TEST 12: export SPECIAL=/usr/bin:/usr/local/bin\n");
    {
        char *argv12[] = {"export", "SPECIAL=/usr/bin:/usr/local/bin", NULL};
        cmd.argv = argv12;
        result = execute_builtin(&cmd, &env);
        printf("Exit status: %d\n\n", result);
    }

    // Test 13: export without value
    printf("TEST 13: export EMPTY_VAR\n");
    {
        char *argv13[] = {"export", "EMPTY_VAR", NULL};
        cmd.argv = argv13;
        result = execute_builtin(&cmd, &env);
        printf("Exit status: %d\n\n", result);
    }

    // Test 14: export - check format with quotes
    printf("TEST 14: export (check declare -x format with quotes)\n");
    {
        char *argv14[] = {"export", NULL};
        cmd.argv = argv14;
        result = execute_builtin(&cmd, &env);
        printf("Exit status: %d\n\n", result);
    }

    // Test 15: cd with exported HOME
    printf("TEST 15: export HOME=/tmp then cd\n");
    {
        char *argv15[] = {"export", "HOME=/tmp", NULL};
        cmd.argv = argv15;
        result = execute_builtin(&cmd, &env);
        printf("Export exit status: %d\n", result);
    }
    {
        char *argv15b[] = {"cd", NULL};
        cmd.argv = argv15b;
        result = execute_builtin(&cmd, &env);
        printf("CD exit status: %d\n", result);
        
        // Verify with pwd
        char *argv15c[] = {"pwd", NULL};
        cmd.argv = argv15c;
        printf("PWD after cd: ");
        execute_builtin(&cmd, &env);
        printf("\n\n");
    }

    // Test 16: export empty value
    printf("TEST 16: export EMPTY=\"\"\n");
    {
        char *argv16[] = {"export", "EMPTY=\"\"", NULL};
        cmd.argv = argv16;
        result = execute_builtin(&cmd, &env);
        printf("Exit status: %d\n\n", result);
    }

    // Test 17: unset non-existent variable
    printf("TEST 17: unset NON_EXISTENT (should succeed silently)\n");
    {
        char *argv17[] = {"unset", "NON_EXISTENT", NULL};
        cmd.argv = argv17;
        result = execute_builtin(&cmd, &env);
        printf("Exit status: %d\n\n", result);
    }

    // Test 18: export with equals in value
    printf("TEST 18: export EQUATION=a=b=c\n");
    {
        char *argv18[] = {"export", "EQUATION=a=b=c", NULL};
        cmd.argv = argv18;
        result = execute_builtin(&cmd, &env);
        printf("Exit status: %d\n\n", result);
    }

    // Test 19: echo to verify env variable
    printf("TEST 19: echo $TEST_VAR (just structure test)\n");
    {
        char *argv19[] = {"echo", "TEST_VAR_VALUE", NULL};
        cmd.argv = argv19;
        result = execute_builtin(&cmd, &env);
        printf("Exit status: %d\n\n", result);
    }

    // Test 20: Final env check
    printf("TEST 20: Final env (all exported variables)\n");
    {
        char *argv20[] = {"env", NULL};
        cmd.argv = argv20;
        result = execute_builtin(&cmd, &env);
        printf("\nExit status: %d\n\n", result);
    }

    printf("=== END TEST SUITE ===\n");
    return (0);
}