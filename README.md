<p align="center">
  <img src="imgs/minipink.png" width="400px" alt="Minishell logo" />
</p>

# Minishell (aka Minipink)

## 📖 Overview

**Minishell** is a simplified recreation of a Unix shell (Bash-like), developed in C as part of the **École 42** curriculum.

This project represents a significant milestone in our educational journey:
*   **First major project**: A deep dive into Unix systems and complex memory management.
*   **First team project**: An enriching experience in collaborative development, task distribution, and Git version control.

The objective is to recreate the internal mechanisms of a shell: from command-line parsing to process execution, including signal handling and I/O redirections.


## ✨ Features

### Shell & Execution
*   Interactive **prompt** display.
*   Command search and execution via the `PATH` environment variable, or through relative/absolute paths.
*   **Pipe** handling (`|`) for command chaining.
*   **I/O Redirections**: `<`, `>`, `>>`, and `<<` (heredoc).
*   **Environment variable** expansion (`$VAR`) and exit status (`$?`).
*   Comprehensive **quote** handling: single (`'`) and double (`"`).

### Built-in Commands
The following commands have been reimplemented to match Bash behavior:
*   `echo` (with `-n` option)
*   `cd` (path handling, `~` and `-` support)
*   `pwd`
*   `export`
*   `unset`
*   `env`
*   `exit`

### Signal Handling
*   `Ctrl+C`: Displays a new prompt on a new line.
*   `Ctrl+D`: Exits the shell (EOF).
*   `Ctrl+\`: Does nothing (ignores SIGQUIT).


## 🔧 Technical Skills

*   **Process management**: Using `fork`, `wait`, `waitpid`, and `execve`.
*   **Inter-process communication**: Manipulation of `pipe` and file descriptors (`dup`, `dup2`).
*   **Parsing**: Implementation of a lexer and parser to transform command strings into executable instructions.
*   **C Programming rigor**: Zero memory leaks (Valgrind-tested) and compliance with École 42's coding standards (Norminette).


## ⚙️ Installation & Usage

### Prerequisites
*   A C compiler (`gcc` or `clang`).
*   The `readline` library installed on your system.

### Compilation
```bash
git clone https://github.com/noanjrd/42_Minishell.git
cd 42_Minishell
make
```

### Execution
```bash
./minishell
```

## 📚 Project Structure

```bash
srcs/
├── builtins/       # Built-in command implementations
├── exec/           # Execution engine and process management
├── parsing/        # Lexer, parser, and syntax validation
└── utils/          # Helper functions and utilities
```

## 🧪 Testing

The project has been thoroughly tested with:

* Standard Bash command comparison
* Edge cases (empty strings, special characters, etc.)
* Memory leak detection with Valgrind
* Signal behavior validation

## 👥 Contributors

This project was developed in collaboration as a team effort with [AANKOUR Naziha](https://github.com/naankour).
