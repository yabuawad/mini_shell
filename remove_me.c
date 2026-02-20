#include "minishell.h"

// static int token_len(const char *s, char sep)
// {
//     int i = 0;
//     int in_q = 0;
//     int in_sq = 0;

//     while (s[i])
//     {
//         if (s[i] == '"')
//             in_q = !in_q;
//         if(s[i] == '\'')
//             in_sq = !in_sq;
//         else if (s[i] == sep && !in_q && !in_sq)
//             break;
//         i++;
//     }
//     return i;
// }

// static char *extract_word(const char *s, char sep)
// {
//     int len = token_len(s, sep);
//     char *w = malloc(len + 1);
//     int i = 0, j = 0;
//     int in_q = 0;
//     int in_sq = 0;

//     if (!w)
//         return NULL;

//     while (i < len)
//     {
//         if (s[i] == '"')
//         {
//             in_q = !in_q;
//             i++;
//             continue;
//         }
//         w[j++] = s[i++];
//     }
//     w[j] = '\0';
//     return w;
// }

// static int count_words(const char *s, char sep)
// {
//     int count = 0;

//     while (*s)
//     {
//         while (*s == sep)
//             s++;
//         if (!*s)
//             break;
//         count++;
//         s += token_len(s, sep);
//     }
//     return count;
// }

// char **seperate(const char *s, char sep)
// {
//     char **arr;
//     int i = 0;

//     arr = malloc(sizeof(char *) * (count_words(s, sep) + 1));
//     if (!arr)
//         return NULL;

//     while (*s)
//     {
//         while (*s == sep)
//             s++;
//         if (!*s)
//             break;
//         arr[i++] = extract_word(s, sep);
//         s += token_len(s, sep);
//     }
//     arr[i] = NULL;
//     return arr;
// }


// void print_split(char **arr) {
//     int i = 0;

//     if (arr == NULL) {
//         printf("NULL\n");
//         return ;
//     }

//     while (arr[i] != NULL) {
//         printf("[%s]\n", arr[i]);
//         i++;
//     }
//     printf("----\n");
// }