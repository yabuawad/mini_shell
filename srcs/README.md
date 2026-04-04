*This project has been created as part of the 42 curriculum by malhassa and yabuawad.*

## Description
Minishell is a small Unix shell written in C. It is divided into parsing and execution. The parsing part handles user input, and variable expansion. The execution part runs the parsed commands and built-ins.

The goal of the project is to reproduce the core behavior of a basic shell while learning how shells work at a low level.

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