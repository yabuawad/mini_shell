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

### Execution

The execution phase reads through all the commands we parsed and runs them. it checks for heredocs first, then decides how to run each command based on whether it has pipes and redirections.

The basic steps are:

1. Check for heredocs: look for '<<' operators and prepare them before running anything
2. check for pipes: see if the command has '|' characters
3. run the command! : execute based on what we found above

#### Case 1: Commands with Pipes

When you use the pipe character ('|'), we run multiple commands at once and connect them together:

- go through each command in the list
- connect them with pipes using the pipe() function
-  create a new child process for each command
- each child reads from the previous command and writes to the next one
- wait for all children to finish

**Example**:
```bash
minishell$: cat file.txt | grep mh | sort
```
#### Case 2: Commands without Pipes

When there are no pipes, commands are executed individually. the execution further branches based on whether redirections are present.
if there are no pipes, we run the command on its own. but we need to check if there are redirections like `<`, `>`, `<<`, or `>>`.

##### Case 2a: No Pipes, But Has Redirections

When a command has redirections (`<`, `>`, `<<`, `>>`):

- **built-in Commands** (like `echo`, `cd`, `export`):
  1. save the current file descriptors (stdin, stdout)
  2. change where it reads/writes based on the redirections
  3. run the command with the new read/write locations
  4. restore the original file descriptors so the shell continues normally

- **Regular Programs** (like `ls`, `cat`, etc.):
  1. fork a child process
  2. set up the redirections in the child process
  3. execute the command in the child process
  4. parent shell waits for completion

**Example**:
```bash
minishell$: echo "mohamed" > output.txt
minishell$: cat < input.txt
```

##### Case 2b: No Pipes, No Redirections

When a command has no pipes and no redirections, we check what kind of command it is:

- **Built-in Commands**: Run directly in the shell (no new process needed)
  
- **Regular Programs**: Create a child process and run it there

**Example**:
```bash
minishell$: echo "mohamed"
minishell$: ls -la
minishell$: pwd
```

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
## Resources
### References
- Main Source : Bash
- Bash manual: https://www.gnu.org/software/bash/manual/
- GNU Readline documentation: https://tiswww.case.edu/php/chet/readline/rltop.html
- Test Cases : https://swift-healer-09e.notion.site/Minishell-Edge-Cases-WIP-19070ced3da3808ca44ec22ec5e41436
- Bash Environment : https://tldp.org/LDP/Bash-Beginners-Guide/html/chap_03.html

### AI Usage
AI was used to help explore shell edge cases, and provide support when I was stuck while thinking through a problem. The implementation and final decisions remained under manual review.
