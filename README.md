# pipe-implementation
> This C++ program takes two command line arguments and simulates how pipes (i.e., "cmd1 | cmd2") work in the shell.

## Note: this script was only delevoped with Linux in mind. Attempting to run this script under any other platform may produce unintended results.

## Usage:

```console
$ make
$ ./pipe [cmd1] [cmd2]
```
If an argument is more than one string in length, it has to be surrounded by quotes.
Example: ./pipe "ps -aux" "grep -i sshd".
