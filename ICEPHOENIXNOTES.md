### **Variable expansion and quotes in heredocs**

- **Unquoted delimiter** (e.g., `<< EOF`):

  - The heredoc content **is subject to variable expansion** (`$VAR` is replaced).
  - Example:
    ```bash
    $ cat << EOF
    hello $USER
    EOF
    ```
    → expands `$USER`.

- **Quoted delimiter** (e.g., `<< "EOF"` or `<< 'EOF'`):

  - The heredoc content is **taken literally** (no variable expansion).
  - Example:
    ```bash
    $ cat << "EOF"
    hello $USER
    EOF
    ```
    → prints `hello $USER`.

- **Ctrl+D**:
  - Ends heredoc input immediately.
  - Keeps whatever was typed so far.
  - Does **not cancel the command**.
