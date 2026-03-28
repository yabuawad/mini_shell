
#include"minishell.c"
void handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1); // dontttt use printf in a signal handler EVER
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void init_signals(void)
{
    signal(SIGINT, handle_sigint); //SIGINT means ctrl+c ,
    signal(SIGQUIT,  SIG_DFL); // SIGQUIT is for ctr+\ 
}

//SIG_DFL == default behaviour. 
