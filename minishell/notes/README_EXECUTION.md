# Minishell Execution Module - Implementation Roadmap

## Project Structure

```
executor_srcs/
├── minishell.h              # Main header with all structures and prototypes
├── minishell.c              # Main entry point (needs parser integration)
├── testmain.c               # Test suite for execution module
├── execution.c              # Main execution logic (builtin + external)
├── builtin_execution.c      # All builtin command implementations
├── redirections.c           # TODO: Redirection setup/restore functions
├── find_executable.c        # PATH resolution for external commands
└── redirections_setup.c     # Can be removed/merged later
```

## Implementation Status

### ✅ Phase 1: Basic Builtins (DONE)
- [x] `echo` with `-n` option
- [x] `cd` with HOME fallback
- [x] `pwd`
- [x] `env`
- [x] `exit`
- [x] External command execution (fork + execve)

### 🚧 Phase 2: Redirections (CURRENT)
**Goal**: Make builtins work with `<`, `>`, `>>` redirections

**Key Concepts**:
- Save original stdin/stdout using `dup()`
- Open target files based on redirection type
- Apply redirections using `dup2()`
- Restore original fds after command execution
- Close all opened fds

**Files to Work On**:
- `redirections.c` - Create functions for setup/restore/cleanup
- `minishell.h` - Add function prototypes
- `execution.c` - Integrate redirection calls into `execute_builtin()`
- `testmain.c` - Test redirections

**Hints**:
- Walk through the `cmd->redirs` linked list
- Handle multiple redirections (last one wins)
- Don't forget error handling for `open()`, `dup()`, `dup2()`

### 📋 Phase 3: Export & Unset (TODO)
**Goal**: Implement environment variable management

**Key Concepts**:
- Need to modify `envp` (can't use system's envp directly)
- Create your own environment array copy
- `export VAR=value` adds/updates variable
- `unset VAR` removes variable
- `export` with no args shows all variables

### 📋 Phase 4: Heredoc (TODO)
**Goal**: Implement `<<` delimiter input

**Key Concepts**:
- Parser identifies delimiter
- Executor reads stdin until delimiter is seen
- Store in temporary file or pipe
- Don't add heredoc input to history

### 📋 Phase 5: Pipes (TODO)
**Goal**: Chain multiple commands together

**Key Concepts**:
- Create pipe for each pair of commands
- Fork for each command in pipeline
- Connect stdout of cmd1 to stdin of cmd2
- Wait for all child processes
- Return exit status of last command

### 📋 Phase 6: Advanced Features (TODO)
- Signal handling (ctrl-C, ctrl-D, ctrl-\)
- `$?` expansion 
- Better error messages matching bash

## How to Test Your Implementation

### Test Each Phase Incrementally

**Phase 1 Testing** (Basic builtins - already working):
```bash
gcc testmain.c execution.c builtin_execution.c find_executable.c \
    -I../libft -L../libft -lft -o test_exec
./test_exec
```

**Phase 2 Testing** (After implementing redirections):
- Update testmain.c to actually execute redirected commands
- Check output files exist and contain expected content
- Test error cases (invalid files, permission denied)

**Integration Testing** (With parser):
```bash
# Once parser is ready
gcc minishell.c execution.c builtin_execution.c redirections.c \
    find_executable.c -I../libft -L../libft -lft -lreadline -o minishell
./minishell
```

## Redirection Implementation Guide

### Step 1: Understanding File Descriptors
- `0` = stdin, `1` = stdout, `2` = stderr
- `dup(fd)` - duplicates fd, returns new fd number
- `dup2(oldfd, newfd)` - makes newfd a copy of oldfd

### Step 2: The Redirection Flow
```
1. Save original stdin/stdout (for later restoration)
2. Walk through cmd->redirs linked list
3. For each redirection:
   - Open the target file with appropriate flags
   - Use dup2() to redirect stdin or stdout
   - Close the opened file fd
4. Execute the command
5. Restore original stdin/stdout
6. Close saved fds
```

### Step 3: Opening Files Based on Type
- `R_IN` (`<`): `open(file, O_RDONLY)` → redirect to stdin
- `R_OUT` (`>`): `open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644)` → redirect to stdout
- `R_APPEND` (`>>`): `open(file, O_WRONLY | O_CREAT | O_APPEND, 0644)` → redirect to stdout
- `R_HEREDOC` (`<<`): Will handle later

### Step 4: Error Handling
- Check if `open()` fails (return -1)
- Check if `dup()` / `dup2()` fail
- Print error with `perror()` or custom message
- Return non-zero exit status

## Integration with Parser

Your teammate's parser should:
```c
// After tokenizing and parsing line:
pipeline.cmd_head = parsed_commands;  // Linked list

// Each command structure:
cmd->argv = {"echo", "hello", NULL};       // Parsed arguments
cmd->redirs = redirection_list;            // Linked list or NULL
cmd->next = next_command_in_pipe;          // Or NULL if last
```

## Questions to Ask Yourself

**For Redirections**:
- [ ] How do I save stdin/stdout before changing them?
- [ ] How do I walk through the linked list of redirections?
- [ ] What flags do I need for each redirection type?
- [ ] When do I close file descriptors?
- [ ] What if a redirection fails?

**For Pipes** (later):
- [ ] How many pipes do I need for N commands?
- [ ] Which command writes to which pipe?
- [ ] When do I close pipe ends?
- [ ] How do I wait for all children?

**For Export/Unset** (later):
- [ ] How do I copy the environment?
- [ ] How do I add/update a variable?
- [ ] How do I remove a variable?
- [ ] How do I pass modified env to child processes?
