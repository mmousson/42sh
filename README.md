# 42sh

42sh School Project.

Authors:
- Mallory Mousson (mmousson)
- Robin Oliveira (roliveir10)
- Octave Boutrolle (oboutrol)
- Heidy Ben Yahia (Policonickolu)

Through 25.000 lines of pure C, we discovered the “behind the scenes” of a shell. More
specifically, we explored the process’ synchronisation creation with functions such as
fork and wait. We also discovered inter-process communication, using pipes, as well as
redirections and line edition, using the termcaps library.

No crash, no memory leaks / memory errors were allowed.
One of the most difficult and impressive project of the entire cursus.
Achieving this was a milestone at 42.

Mandatory part:
- Command prompt with complete line edition
- Run commands with their parameters and PATH monitoring.
- Error monitoring, without using errno, and return values of commands.
- Builtins `cd`, `echo`, `exit`, `env` with all the options enounced by the POSIX standard.
- Support of redirection and agregation operators `>`, `>>`, `<` and `<<`.
- Support of pipe creation and synchronization with `|`.
- Support of logical operators `&&`and `||` and simple separator `;`.
- Job control monitoring, with buitl-ins `jobs`, `fg`, `bg` (with all their POSIX options) and the `&` operator.
- A correct handling of all signals.
- A complete handling of internal shell variables and variable exportation through `export` builtin.

# Modular Part (at least 6 additional features were required to validate the project).

Optional feature highly appreciated:
- All shell's functionnalities implemented in full compliance with the POSIX standard.
- Dynamic autocompletion of commands' options

## Inhibitors
- `"` (double quote)
- `'` (simple quote)
- `\` (backslash)

## Compound Commands ( with `()` and `{}`)

- **With `( commands-list )`** Execute the commands in a subshell environment. Variable assignments and built-in commands that affect the environment shall not remain in effect after the list finishes.
- **With `{ commands-list }`** Execute compound-list in the current process environment.

## Line editing

Keys|Functions|
:-:|:--
<kbd>Opt</kbd>+<kbd>C</kbd><br><kbd>Opt</kbd>+<kbd>X</kbd><br><kbd>Opt</kbd>+<kbd>V</kbd>|Copy<br>Cut<br>Paste
<kbd>Opt</kbd>+<kbd><</kbd><br><kbd>Opt</kbd>+<kbd>></kbd>|Move per words.
<kbd>Opt</kbd>+<kbd>^</kbd><br><kbd>Opt</kbd>+<kbd>v</kbd>|Move per line.
<kbd>Ctrl</kbd>+<kbd>C</kbd>|Terminate/Kill current foreground process.
<kbd>Ctrl</kbd>+<kbd>Z</kbd>|Suspend/Stop current foreground process.

## History

Keys|Functions|
:-:|:--
<kbd>^</kbd><br><kbd>v</kbd>|Browse the history.
<kbd>Ctrl</kbd>+<kbd>R</kbd>|Research function.
`!!`|Retype the last command.
`!n`|Retype the `n`(numerical value) command from the begin of history.
`!-n`|Retype the `-n`(numerical value) command from the last command.
`!name`|Search for a command beginning with `name`.
`!?name`|Search for a command which contain `name`.

## Job Control

Commands|Functions|
:-:|:--
`jobs`|List all the current running jobs.
`fg`|Bring the most recent process to foreground.
`fg n`|Bring the specified jobs to foreground where `n` is the numerical value of the process found in `jobs`.

## Autocompletion

Output is colored upon type.
Autocompletion works with binary, path and env variable.
Navigation through available options is done with <kbd>Tab</kbd> and <kbd>Shift</kbd>+<kbd>Tab</kbd><br>

Commands|Functions|
:-:|:--
`$> l[tab]`|Search for binary.
`$> ls s[tab]`|Search for path/files.
`$> $[tab]`|Search for variables in `env`.

## Globbing

Pattern|Behavior|
:-:|:--
`*`|Everything.
`**`|Match directory and sub-directory.
`?`|Single char.
`[a-z]`|Match range from `a` to `z`.
`[!a-z]` `[^a-z]`|Exclude range from `a` to `z`.
`{ab, ac}`|Match `ab` or `ac`.

## Arithmetic Expansion

Operators|Behavior|
:-:|:--:
`+ / -`|Addition / Soustraction
`++ / --`|Incrementing / Decrementing
`* / %`|Multiplication / Modulo
`/`|Division
`<= / >= / < / >`|Comparison
`== / !=`|Equality / Differencies
`&& / \|\|`|Logical AND / OR

## Tilde expansion and additional parameter formats

|                    |       parameter      |       parameter      |       parameter      |
| :----------------: |  :----------------:  |  :----------------:  |  :----------------:  |
|                    |   Set and not NULL   |     Set but NULL     |         UNSET        |
| ${parameter:-word} | substitute parameter | substitute word      | substitute word      |
| ${parameter-word}  | substitute parameter | substitute null      | substitute word      |
| ${parameter:=word} | substitute parameter | assign word          | assign word          |
| ${parameter=word}  | substitute parameter | substitute null      | assign word          |
| ${parameter:?word} | substitute parameter | error, exit          | error, exit          |
| ${parameter?word}  | substitute parameter | substitute null      | error, exit          |
| ${parameter:+word} | substitute word      | substitute null      | substitute null      |
| ${parameter+word}  | substitute word      | substitute word      | substitute null      |

## Hash table

The shell's hash table stores the full path to the binary corresponding to a command, preventing to do a full research
through the PATH environment variable over and over again each time the command is typed-in.

Commands|Functions|
:-:|:--
`hash`|List the content of the hash table.
`hash -r`|Clear the memory of the hash table.

## `Vi` and `Readline` editing modes

- **Vi**: #, , v, j, k, l, h, w, W, e E b B ˆ $ 0 |, f, F, ;, ,, a, A, i, I, r, R, c, C, S, x, X, d, D, y, y, Y, p, P, u, U.
- **Readline**: C-b, C-f, C-p, C-n, C-_, C-t, A-t.

## Alias Management

An alias definition provides a string value that shall replace a command name when it is encountered.
Alias management is achieved with the `alias` and `unalias` builtins utilities (all POSIX options).
