# Minishell

<p align="left">
<img src="https://img.shields.io/badge/STATUS-EN%20DESAROLLO-green">
</p>

Minishell is a school 42 project that consists of recreating a basic shell, taking bash as a reference. This project was done by @crigonza and @ipaelo, two students passionate about programming and learning.

## Objectives

The objective of this project is to learn about the functioning of a shell, from reading and analyzing the user input, to executing and controlling the processes. It also aims to develop skills such as code organization, teamwork and use of tools such as git and makefile.

## Features

Minishell is able to:

- Read and evaluate simple commands, with their arguments and options.
- Handle environment variables, with the commands `export`, `unset` and `env`.
- Execute external programs, looking for them in the `PATH` variable.
- Use redirections `<`, `>` and `>>`, as well as pipes `|`.
- Implement the builtins `echo`, `cd`, `pwd` and `exit`.
- Manage signals `ctrl-C`, `ctrl-D` and `ctrl-\`.
- Expand variables with `$`.

## Installation

To compile minishell, just clone this repository and run the command `make`:

```bash
git clone https://github.com/crigonza/minishell.git
cd minishell
make
```

This will generate an executable called `minishell`, which can be launched with:
```bash
./minishell
```
## Usage
Minishell works similarly to bash, but with some differences. For example, it does not support  special characters `\`, `;`, `*` or `?`. It also does not allow the use of aliases, functions or scripts.

To exit minishell, you can use the command exit or the key combination ctrl-D.

## Examples
Here are some examples of using minishell:
