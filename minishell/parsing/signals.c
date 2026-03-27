
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
    //signal(*signal sent(ex = ctrl+c)* , here is the function to behave once the signal is sent(could be a default built in one like(SIG_IGN)))
    signal(SIGINT, handle_sigint); //SIGINT means ctrl+c ,
    signal(SIGQUIT,  SIG_DFL); // SIGQUIT is for ctr+\ 
}

//SIG_DFL == default behaviour. 
