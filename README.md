# Minishell

A small POSIX-like command-line shell implemented in C. This project implements a tokenizer, parser (finite‑state), expander (variable and heredoc expansion), and executor with builtin commands, pipelines and redirections — primarily an educational and technical exercise in systems programming.

## Key Features
- Tokenize and parse shell input using a finite‑state approach ([`ft_parser_fda`](parser/parser_fda.c)).  
- Expand environment variables and special status `$?`, including heredoc expansion ([`ft_expand_heredoc`](expander/expander_heredoc.c), [`ft_store_heredoc`](expander/expander_heredoc_utils.c)).  
- Execute commands with full pipeline and redirection support ([`ft_pipeline`](executer/executer_pipe.c), [`ft_executer`](executer/executer.c)).  
- Builtin commands: cd, echo, pwd, env, export, unset, exit (implemented under `executer/builtin/`).  
- Memory-safe utility library (`libft`) with common helpers (e.g. [`ft_itoa`](libft/src/ft_itoa.c)).  
- Signal handling for interactive and heredoc modes; valgrind friendly via [`leaks.sh`](leaks.sh).

## Tech Stack
- Language: C (clang)
- Build: Makefile ([`Makefile`](Makefile))
- Libraries: GNU readline (link via Makefile)
- Tools: valgrind (`leaks.sh`) for leak checking

## Architecture & Design
- Modular C codebase split into clear layers:
  - Tokenizer: `tokenizer/` (token production)
  - Parser: `parser/` (AST construction) — see [`parser/parser_fda.c`](parser/parser_fda.c)
  - Expander: `expander/` (variable & heredoc expansion) — see [`expander/expander.c`](expander/expander.c)
  - Executer: `executer/` (builtin dispatch, process management, pipes) — see [`executer/executer.c`](executer/executer.c)
  - Shared types & headers: [`include/structs.h`](include/structs.h), [`include/executer.h`](include/executer.h), [`include/expander.h`](include/expander.h)
- AST and token structures centralized in [`include/structs.h`](include/structs.h).
- Custom utility library: `libft/` with standard helpers used across modules (e.g. [`libft/src/ft_itoa.c`](libft/src/ft_itoa.c)).

## Getting Started

### Prerequisites
- clang (or compatible C compiler)
- make
- development headers for readline (libreadline / libtinfo)
- (optional) valgrind for leak checks

### Installation
Clone the repository (assumed) and build:

```bash
# build the project (this also builds libft)
make
```

### Running the project
Start the shell:

```bash
./minishell
```

Run with valgrind (basic leak check):

```bash
./leaks.sh
```

Files of interest: main entry point is [`main.c`](main.c); build config in [`Makefile`](Makefile).

## Usage
- Shell prompt accepts standard commands, pipes, redirections and heredoc:
  - Pipeline: ls | grep foo
  - Redirection: grep pattern file > out.txt
  - Heredoc:
    - cat << EOF
      multiline
      EOF
- Builtins available: cd, echo, pwd, env, export, unset, exit (implementations under `executer/builtin/`).

Relevant execution and pipe logic: [`executer/executer_pipe.c`](executer/executer_pipe.c), [`executer/executer_command.c`](executer/executer_command.c).

## What I Learned / Technical Challenges
- Implementing a robust tokenizer and a finite‑state parser for shell syntax ([`parser/parser_fda.c`](parser/parser_fda.c)).
- Using of Abstract Syntax Tree.
- Correct environment and special‑variable expansion including `$?` and heredoc semantics ([`expander/expander_dollar_*`](expander/)).
- Managing file descriptors across processes for pipelines and redirections ([`executer/executer_pipe.c`](executer/executer_pipe.c)).
- Handling signals cleanly in parent and child processes for both interactive and heredoc modes.
- Careful manual memory management and leakage detection using valgrind (`leaks.sh`).

## Future Improvements
- Add job control (background/foreground, job listing, SIGTSTP handling).
- Expand test coverage and add automated unit / integration tests.
- Improve parser resilience (more POSIX corner cases) and error messages.
- Implement more shell features (command history expansion, completion).

## Author & Contact
- Authors: schamizo, saroca-f
- Contact: 
salvadorchamizo@gmail.com, saroca1993@gmail.com

- For code reference and browsing, key files:
    - [`main.c`](main.c) — program entry
    - [`Makefile`](Makefile) — build
    - [`parser/parser_fda.c`](parser/parser_fda.c) — parser (finite automaton)
    - [`expander/expander.c`](expander/expander.c) — expansion
    - [`expander/expander_heredoc.c`](expander/expander_heredoc.c) — heredoc handling
    - [`executer/executer.c`](executer/executer.c) — builtin dispatch and execution
    - [`executer/executer_pipe.c`](executer/executer_pipe.c) — pipeline execution
    - [`include/structs.h`](include/structs.h) — central data structures
    - [`libft/src/ft_itoa.c`](libft/src/ft_itoa.c) — libft example
    - [`leaks.sh`](leaks.sh) — valgrind helper
