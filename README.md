# Minishell

> "This project is about creating a simple shell. Yes, your very own little Bash."

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

### 📦 Memory Management

- No memory leaks are allowed (except those potentially caused by the internal `readline` function, as permitted by the subject).

---

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
<pre> ``` token token_type token_value -------------------------------------------- 0 WORD echo 1 GREAT > 2 WORD outfile 3 PIPE | 4 WORD cat 5 HEREDOC << 6 WORD 3 7 GREAT > 8 WORD outfile -------------------------------------------- Command[0] echo REDIR_ID : REDIR_OUT file_name: outfile Command[1] cat REDIR_ID : REDIR_HEREDOC fd: 3 REDIR_ID : REDIR_OUT file_name: outfile -------------------------------------------- minishell$ ``` </pre>

> This feature is for debugging purposes and helps visualize how the parser and executor understand and process the input.

---

