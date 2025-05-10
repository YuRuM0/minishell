# Minishell

> "As beautiful as a shell.....This project is about creating a simple shell. Yes, our very own little Bash."

## 🧠 About

**Minishell** is a project from 42 School that aims to build a basic shell with functionality similar to `bash`. It supports command execution with arguments, environment variable management, redirections, and pipelines.

> ⚠️ Only the **mandatory part** of the project has been implemented. Bonus features such as `&&`, `||`, parentheses `()`, and wildcards (`*`) are **not** included.

---

## ✅ Implemented Features

### 🎯 Shell Behavior

- Displays an interactive prompt while waiting for a command.
- Functional command history using `readline`.
- Locates and executes commands using the `PATH` environment variable or relative/absolute paths.
- Uses **at most one global variable** to store the received signal number (no access to shared data or global structs).
- Proper quote handling:
  - Single quotes `'` prevent expansion of any special characters.
  - Double quotes `"` prevent most expansions, **except** for `$`.
  - Variable expansion inside heredocs if the delimiter is not inside quotes.
- Ignores unsupported characters like `\` or `;` (as not required by the subject).
- Special characters as \', \" and \\ are supported. 
- Environment variable expansion:
  - `$VAR`
  - `$?` (exit status of the last executed foreground pipeline)
- Signal behavior:
  - `Ctrl-C`: displays a new prompt on a new line.
  - `Ctrl-D`: exits the shell if the user is in the interactive mode (readline) and the prompt is empty.
  - `Ctrl-\`: has no effect.

### 🔧 Redirections

- `<` redirects input.
- `>` redirects output (overwrite).
- `>>` redirects output in **append** mode.
- `<<` (heredoc) reads input until a delimiter line is reached.
  - **Note:** Heredoc **does not update the history**.

### 🔗 Pipelines

- Supports `|` to connect the output of one command to the input of the next.

### 💬 Built-in Commands

- `echo` (with `-n` option)
- `cd` (with relative or absolute paths)
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### 📝 Heredoc Internals
- The heredoc (<<) implementation in **Minishell** closely mimics the behavior of Bash, especially regarding signal handling and input redirection:
  - When a heredoc is encountered, the shell creates a child process to handle user input until the delimiter is reached.
  - The input is written to a temporary file created in /tmp.

- Signal behavior matches Bash during heredoc input:
  - Ctrl-C: interrupts input and cancels the heredoc with an error status.
  - Ctrl-\: is ignored.
  - Ctrl-D: ends input as expected.

- Once writing is complete, the parent process opens the temporary file, saves the file descriptor, and immediately calls unlink() to remove the file path, ensuring the file is deleted automatically after use.
- This approach ensures that heredoc content is safely isolated, temporary, and leaves no residual files on the system.

### 📦 Memory Management

- No memory leaks are allowed (except those potentially caused by the internal `readline` function, as permitted by the subject).

---

## 🧩 Core Concepts Explored

Working on **Minishell** offered a deep dive into low-level system programming, shell architecture, and efficient data handling. Some of the most valuable lessons and skills gained include:

- **Process Management:**  
  Learned to create and manage processes using `fork()`, execute commands with `execve()`, and properly synchronize them using `wait()` and `waitpid()`.
- **File Descriptors and Redirections:**  
  Gained experience in manipulating file descriptors to implement input/output redirections (`<`, `>`, `>>`, `<<`) and pipe chaining using `|`.
- **Signal Handling:**  
  Understood how to capture and respond to signals like `SIGINT` and `SIGQUIT`, mimicking Bash behavior accurately — especially in heredoc and interactive contexts.
- **Environment Variable Handling:**  
  Implemented custom management of environment variables using a linked list, including features like `$VAR`, `$?`, and built-in commands like `export`, `unset`, and `env`.
- **Lexical Analysis and Tokenization:**  
  Built a custom tokenizer for shell input that uses **jumptables** to efficiently dispatch handlers for each **metacharacter** (`" \t\n|<>$\"\'&"`). This significantly improved parsing performance and maintainability.
- **Data Structures:**  
  Used **linked lists** extensively for managing:
  - **Tokens** parsed from user input,
  - **Commands** (including their arguments and redirections),
  - **Environment variables**, enabling dynamic updates during shell execution.
- **Memory Management:**  
  Ensured clean memory handling across all components using `malloc`/`free`, including nested structures and cleanup on exit. Validated memory correctness with tools like `valgrind`.
- **Readline Integration:**  
  Integrated the GNU `readline` library to manage input history and improve user experience in the interactive shell prompt.
> Overall, this project provided a comprehensive understanding of how a shell works under the hood and sharpened my skills in systems programming, code modularization, debugging, and resource management.

## 🚫 Not Implemented (Bonus Part)

- Logical operators: `&&`, `||`
- Grouping commands with parentheses `()`
- Wildcards (`*`)

---

## 🔧 Compilation

```bash
make
```
---

## ▶️ Running

```bash
./minishell
```

### 🐞 Debug Mode

```bash
./minishell -g
```
#### 🔍 Example Output in debug mode
```bash
minishell$ echo > outfile | cat <<EOF > outfile
>minishell debug mode
>EOF
```

```
token      token_type           token_value         
--------------------------------------------
0          WORD                 echo                
1          GREAT                >                   
2          WORD                 outfile             
3          PIPE                 |                   
4          WORD                 cat                 
5          HEREDOC              <<                  
6          WORD                 3                   
7          GREAT                >                   
8          WORD                 outfile             
--------------------------------------------

Command[0] echo                
REDIR_ID : REDIR_OUT            file_name: outfile   

Command[1] cat                 
REDIR_ID : REDIR_HEREDOC        fd: 3
REDIR_ID : REDIR_OUT            file_name: outfile   

--------------------------------------------

minishell$ 
```

This feature is for debugging purposes and helps visualize how the parser and executor understand and process the input.

---

