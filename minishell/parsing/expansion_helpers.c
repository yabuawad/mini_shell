#include "../minishell.h"

int is_varchar(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') 
            || (c >= '0' && c <= '9') || c == '_');
}
int get_length(char *str,int i)
{
    int counter = 0;
    if (str[i + 1] == '?')
        return (1);
    if(i > 0 && str[i - 1] == '"')
    {
        i++;
        while (str[i] != '\0' && is_varchar(str[i]))
        {
            counter++;
            i++;
        }   
    }
    else if(i == 0 || (str[i - 1] && str[i - 1] != '"' ))
    {
        i++; 
        while (str[i] != '\0' && is_varchar(str[i]))
        {
            counter++;
            i++;
        }   
    }  
    return(counter);
}
char *get_var(char *str,int i,char *var)
{
    int j;

    j = 0;
    if (str[i + 1] == '?')
    {
        var[0] = '?';
        var[1] = '\0';
        return (var);
    }
    if(i > 0 && str[i - 1] == '"')
    {
        i++;
        while (str[i] != '\0' && is_varchar(str[i]))
            var[j++] = str[i++];
    }
    else
    {
        i++;
        while (str[i] != '\0' && is_varchar(str[i]))
            var[j++] = str[i++];
    }
    var[j] = '\0';
    return (var);
}
char *find_env_val(t_env *myenv,char *var)
{
    int i;
    char *val;
    int j;

    val = NULL;
    if (var && var[0] == '?' && var[1] == '\0')
        return (ft_itoa(myenv->last_exit_status));
    i = 0;
    while(myenv->envp[i])
    {
        if(ft_strncmp(var,myenv->envp[i],ft_strlen(var)) == 0 
            && myenv->envp[i][ft_strlen(var)] == '=')
        {
            j = 0;
            while(myenv->envp[i][j] != '=')
                j++;
            val = ft_strdup(myenv->envp[i] + j + 1);
            if(!val)
                return NULL;
            break;
        }
        i++;
    }
    return (val);
}
