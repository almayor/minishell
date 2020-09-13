# minishell

*This project is part of the official curriculum at [School 42](https://en.wikipedia.org/wiki/42_(school)).*

## Disclaimer

> In [School 42](https://en.wikipedia.org/wiki/42_(school)), almost every project must be written to comply with. coding standard (also known as the "[Norm](./docs/subjects/norme.en.pdf)"). As a result, the implementation of certain parts may appear strange.


## Overview

* [Official instructions](docs/subjects/minishell.en.pdf)
* A personal implementation of a Linux shell with minimal functionality
	* builtins: `cd`, `env`, `setenv`, `unsetenv`, `echo`, `exit`
	* separation of commands with `;`
	* history and autocompletion
	* management of `SIGINT`
* Only the following functions are allowed
	* `malloc`, `free`
	* `access`
	* `open`, `close`, `read`, `write`
	* `opendir`, `readdir`, `closedir`
	* `getcwd`, `chdir`
	* `stat`, `lstat`, `fstat`
	* `fork`, `execve`
	* `wait`, `waitpid`, `wait3`, `wait4`
	* `signal`, `kill`

## Run

To compile, run

```sh
git clone https://github.com/almayor/minishell
cd minishell
git submodule --init --recursive
make
```

## Resources

* <https://brennan.io/2015/01/16/write-a-shell-in-c/>

## Acknowledgements

We are grateful to the entire team behind School 42 and its [Moscow branch](https://21-school.ru
), as well as to my fellow students for help and support.

---
If you have any questions, please contact me on Github.
