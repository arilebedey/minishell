## Notes

### Heredocs

Advice to fork heredoc was wrong, since we are only allowed one global variable in the project, therefore freeing the parent state in the child was not possible without overriding that rule and possibly getting KO-ed. Setting up a signal handler for the heredoc part was our solution.

### Supress readline leaks

Copy the `valgrind.supp` file and add optionally add an alias, for e.g.:

```sh
alias msv='valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --suppressions=valgrind.supp ./minishell'
```

## Project specifications

For the project we relied on GNU’s readline library to manage user input and command history, but all the rest of the shell was built with raw POSIX syscalls and low-level primitives. Features like process control, redirection, environment handling, and signal management were implemented on top of these system calls.

<b>System calls used:</b>  
`readline, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, signal, sigaction, sigemptyset, kill, exit, getcwd, chdir, unlink, execve, dup, dup2, pipe, perror`

### Platforms

The project was tested both on macOS and Linux. On macOS run `brew install readline` first.

### Running

To build and run:

```bash
git clone git@github.com:arilebedey/minishell.git
cd minishell
make
./minishell
```

From there you get a prompt (`🥸 💻 petitshell>`), and you can run commands like `ls`, use pipes (`ls | wc -l`), redirections (`cat < in1 > out`), and builtins (`cd`, `export`, `unset`, `env`, `echo`, `exit`).

### Subject

[EN] https://cdn.intra.42.fr/pdf/pdf/154328/en.subject.pdf

### Others students minishell implementations

https://github.com/decilap/groupdev/

https://github.com/ft-palourde/minishell

https://github.com/mli42/at42minishell

## Git

freecodecamp git for pros: https://www.youtube.com/watch?v=Uszj_k0DGsg
