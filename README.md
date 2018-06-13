# Simple-Shell
Executing UNIX commands using a simple shell.

This project consists of designing a C program to serve as a shell interface with parent and child processes running concurrently. 

The project consists of two main parts: Creating a child process, and Creating a history feature.

## Make file
The code can be compiled to produce output and cleaned to remove the output using make

```
$ make
gcc -pthread shell.c -o shell
$ ./shell
//for cleaning the output
$ make clean
rm -f main
```


## Error handling:
Code is capable of handling the input error cases such as non-existing commands or no commands in history.


## How to use
for commands
```
./shell.o
ls -l
ps 
date
```
for history
```
!!
//the most recent command in history
!4
//the forth recent command in history
```
for a child process
```
& 
```

## Built With

* [GCC](https://gcc.gnu.org/) - The GNU Compiler Collection
* [Ubuntu 16.04 LTS](releases.ubuntu.com/16.04/) - Xenial Xerus

## Author

* **Ahmed Wael** - [Github](https://github.com/ahmedwael19)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.


