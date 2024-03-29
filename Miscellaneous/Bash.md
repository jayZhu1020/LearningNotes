# Bash scripting

## Intro to Bash
**Shell:** A shell is a macro processor or a command language interpreter that primarily translates the commands, written by the user in the terminal, into system actions that are executed, which can also automatically run in programs called shell scripts. A shell is an environment provided for the user to interact with the machine.

**Type of UNIX shells:**

1. **Bourne Shell** that has default prompt #
2. **C Shell** that has default prompt %

**Type of shells by interaction method:**

1. **Command Line Shell:** can be accessed by terminal
2. **Graphical Shell:** can be accessed by a graphical interface

**Types of Linux Shells:**
* BASH
* CSH
* KSH
* TCSH
* ZSH
* Fish

## Meta data about the interpreter
Finding the interpreter
```shell
ps $$
```

Finding the execution path of the interpreter
```shell
echo $SHELL
```

Switch to bash shell interpreter
```shell
chsh -s /bin/bash
```

Getting command information
```shell
man <command>
info <command>
```

Display the calendar
```shell
cal
```
Display the date
```shell
date
```

## BASH use case
Following are some of the common applications of Bash:
* File manipulation
* Program execution
* Creating your power tools/utilities
* Automating command input or entry
* Customizing administrative tasks
* Creating simple applications
* Creating customized power utilities
* Printing text

When not to use Bash?
* Need direct access to system hardware or external peripherals
* Need data structures, such as linked lists, graphs or trees
* Need to generate or manipulate graphics or GUIs
* Need native support for multi-dimensional arrays
* Need port or socket I/O
* Extensive file operations (Bash is limited to serial file access, and that only in a clumsy and inefficient line-by-line fashion)
* Where cross-platform portability is required
* Resource-intensive tasks, especially where speed is an important factor (sorting, recursion, hashing, etc.)

# Command Line
**command-line interface (CLI):** A command-line interface (CLI) or a command line interpreter or shell is simply a mean for the user to interact with the system in the form of progressive and sequential commands.

Get username
```shell
whoami
```

**Shortcuts**
1. `Ctrl + H`: delete the letter starting at the cursor
2. `Ctrl + W`: delete the word starting at the cursor
3. `TAB`: auto complete
4. `Ctrl + U`: clear the line
5. `Ctrl + C`: cancel currently running commands
6. `Ctrl + L`: clear the screen
7. `Ctrl + A`: move to the start of the command line
8. `Ctrl + E`: move to tje end of the command line
9. `Alt + LEFTARROW`: move back one word
10. `Alt + RIGHTARROW`: move forward one word 

**Special Characters**
1. `/`: used for directory
2. ``: used as escape character
3. `#`: starts a comment
4. `.`: returns the current directory
5. `..`: returns the parent directory
6. `~`: returns the home directory
7. `~+`: returns the current working directory
8. `~-`: returns the previous working directory
9. `*`, `[]`, `?`: regular expression matching, any occurance, fixed occurance, one occurance
10. `|`: output for the left command feeds into the right command as input
11. `<`: redirect a file as an input to a program.
12. `>`: redirect the output of “script name” to “file filename”. Overwrite filename if it already exists.
13. `>>`: Redirect and append the output of the command to the end of the file.
14. `&`: Execute a job in the background and immediately get your shell back.
15. `&&`: “AND logical operator”. It returns (success) only if both the linked test conditions are true.
16. `;`: “Command separator”. Allows you to execute multiple commands in a single line.

Get manual for some comand
```console
$ man COMMAND
```

Prints argument to terminal
```console
$ echo [options] [strings]
```

Clear command line
```console
$ clear
```

Pause the command for some n seconds
```console
$ sleep n
```

Retrieve files
```console
$ ls [options] 
```
common options:
`-a`: also displays hidden directories. `-s`: shows the size of files.

create directory
```console
$ mkdir [directory names]
```

deleting empty directory
```console
$ rmdir [directory names]
```

create new files
```console
$ touch [option] [file_name(s)]
```
common options:
`-a`: change the access time of the files
`-m`: change the mofication time of the files

remove files
```console
$ rm [options] [file_name(s)]
```
common options:
`-r`: recursive, recursively delete directories
`-f`: force delete without warning
`-i`: delete with user confirmation

get word count
```console
$ wc [option] [file]
```
wc diaplays `[number of lines] [number of words] [number of characters]`
common options:
`-m`: print character counts
`-c`: print byte counts
`-l`: print newline counts
`-w`: print word count

concatenation, file reading and file creation
```console
$ cat [option] [file_name(s)]
```

concatenate files
```console
$ cat file1 file2 ... filen
```

file reading
```console
$ cat [file_name(s)] // To print contents of file

$ cat [file_name] > [file_name] // To redirect content to another file

$ cat [file_name] | less // To filter the content to be displayed with piping
```

file creation
```console
$ cat > [new_file_name]  // To create new file or overwrite if file already exists

$ cat >> [existing_file_name] // To preserve previous file if it already exists by appending any new text
```

move and rename
```console
$ mv [options] [source] [destination]
```

Create soft Link
```console
$ ln -s <source_name> <link_name>
```

Create hard Link
```console
$ ln <source_name> <link_name>
```

Check current directory
```console
$ pwd
```

Navigate between directories
```console
$ cd [option] [directory_name]
```

Copy files in Bash
```console
$ cp [option] [file_name] new_file_name
```
Option:
`-r`: recursively copy

Zip files in bash
```console
$ tar [option(s)] [archive_file_name] [file_name(s)]
```
This command requires a option to run
`-c`: creates an archive
`-x`: extracts an archive
`-f`: creates archive with the same name
`-t`: displays the files archive
`-z`: creates archive with `gzip`
`-r`: update the archive file with new files
`-v`: verbose

Alternative command:
```console
$ gzip [option(s)] [file_name(s)]
```
Options:
`-k`: compress files in original form
`-d`: devompress gzip files

**Searching an Locating**
search for the locations of files and directories.
```console
$ locate [options] name(s)
```
Options:
`-q`: suppress error messages
`-n x`: limit the result to `x` numbers
`-i`: case insensitive search

```console
$ find [path...] [expression]
```
`-type f`	Selects files.
`-type d`	Selects directories.
`-name`	True if the base of the file name (the path with the leading directories removed) matches shell pattern pattern.

