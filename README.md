*This project has been created as part of the 42 curriculum by malhassa and yabuawad.*
# Minishell ₍^. .^₎⟆
## Description
Minishell is a small Unix shell written in C. It is divided into parsing and execution. The parsing part handles user input, and variable expansion. The execution part runs the parsed commands and built-ins.

The goal of the project is to reproduce the core behavior of a basic shell while learning how shells work at a low level.

## Parsing

parsing shell input is handled through three core phases: *tokenisation*, *parsing* and *expansion*.
each phase transforms the input into a more structured and usable form, making it easier to eventually execute the command.  
here are some details about each phase: 

### ~The Tokenisation (aka lexing) phase

tokenising is the process of breaking down a stream of text -the command line- into smaller pieces called tokens.
i initially stored these tokens in a 2d array as a starting point. by converting raw text into manageable chunks, the later phases become much easier to handle.  
#### example
``` bash
minishell$: ls -l | grep Apr
```
tokenised into:
```bash
[ ls ]
[ -l ]
[ | ]
[ grep ]
[ Apr ]
```
this phase also includes detecting basic syntax errors.like:
```bash
minishell$: ls |
syntax error near unexpected token |
```

### ~The Parsing phase

this phase is responsible for assigning a type to each token.
the classification depends on the token itself and its surrounding context (what comes before and after it). this allows us to understand the role of each token in the command.
the data structure used here is a linked list with a custom structure (see minishell.h).  
this step transforms a simple list of tokens into a structured representation that can be interpreted correctly during execution.

### ~The Expansion phase

expansion is the phase where tokens are transformed into their final values before execution.
this happens after parsing, since we first need to understand the role of each token before modifying its content.
the main operations performed during this phase are:  

#### environment variable expansion
variables like $USER or $PATH are replaced with their corresponding values from the environment(env).

#### example  
```bash
minishell$: echo $USER
```
expands into:
```bash
[ echo ]
[ yara ]
```
#### quote handling

quotes determine how the content inside them should be interpreted.  

single quotes ' '  
everything inside is treated literally — no expansion occurs.  
#### example
```bash
minishell$: echo '$USER'
```
result:
```bash
[ echo ]
[ $USER ]
```
double quotes " "  
allow expansion while preserving spaces as part of the same token.

#### example
```bash
minishell$: echo "$USER is here"
```
result:
```bash
[ echo ]
[ yara is here ]
```
#### exit status expansion

the special variable $? is replaced with the exit status of the last executed command.

#### example
```bash
minishell$: echo $?
```
result:
```bash
[ echo ]
[ 0 ]
```
this phase ensures that all tokens are fully resolved and ready to be passed to the execution stage.
## Instructions
### Compilation
```bash
make
```

### Cleaning
```bash
make clean
make fclean
make re
```

### Execution
```bash
./minishell
```

You can then type commands interactively, for example:
```bash
echo hello
ls -l | cat
cat << EOF
text
EOF
```

## Resources
### References
- Main Source : Bash
- Bash manual: https://www.gnu.org/software/bash/manual/
- GNU Readline documentation: https://tiswww.case.edu/php/chet/readline/rltop.html
- Test Cases : https://swift-healer-09e.notion.site/Minishell-Edge-Cases-WIP-19070ced3da3808ca44ec22ec5e41436
- Bash Environment : https://tldp.org/LDP/Bash-Beginners-Guide/html/chap_03.html

### AI Usage
AI was used to help explore shell edge cases, and provide support when I was stuck while thinking through a problem. The implementation and final decisions remained under manual review.
