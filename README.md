# Get next line

<p align="center">
  <img src="https://github.com/ArenKae/ArenKae/blob/main/42%20badges/get_next_linee.png" alt="Gnl 42 project badge"/>
</p>

In this project, we will learn to read from a file descriptor and how to use static variables.
The `get_next_line()` function returns a single line from a given file descriptor. If called in a loop, it returns the entire contents of a file, line by line until it reaches the end of the file. It can be compiled specifying any buffer size.

## Status
✅ Completed on: 18/04/2023
</br>
🏆 Grade: 125/100

## Usage

This utility function is not a stand-alone program : its files must be included in another project.
In the tests/ directory, you will find a main.c to compile a small test program, as well as a testfile.txt.

`cd` into the tests/ directory and compile using :
```bash
gcc main.c ../get_next_line.c ../get_next_line_utils.c && ./a.out
```
The output should be identical to testfile.txt.
</br>

> [!NOTE]
> `BUFFER_SIZE` can be specified at compilation to override the default `BUFFER_SIZE` :
> ```bash
> gcc -D BUFFER_SIZE=42 main.c ../get_next_line.c ../get_next_line_utils.c && ./a.out
> ```

## Bonus part

For the bonus part, the program must be able to manage manage multiple file descriptors at the same time. For example, we want to read from the file descriptors 3, 4 and 5 without losing the reading thread of each file descriptor or returning a line from another fd. For that purpose, the static stash becomes an array of strings instead of a simple char *. The rest of the code is otherwise the same as the mandatory part.

To use the bonus function, `cd` into the tests/ directory and compile using :
```bash
gcc main_bonus.c ../get_next_line_bonus.c ../get_next_line_utils_bonus.c && ./a.out
```
The output should alternate between lowercase (fd1) and uppercase (fd2) versions of the sample text, demonstrating different files being read at the same time.

## About the 'static' keyword in C

In C, the static keyword has different meanings and behavior depending on the context where its used.

### 1. Static Variables Inside a Function (Local Scope)
When declared inside a function, a `static` variable retains its value between function calls. It is initialized only once and lives for the duration of the program.
```c
#include <stdio.h>

void counter() {
    static int count = 0; // Initialized once, keeps value between calls
    count++;
    printf("Count: %d\n", count);
}

int main() {
    counter(); // Count: 1
    counter(); // Count: 2
    counter(); // Count: 3
    return 0;
}
```

### 2. Static Variables Outside Functions (File Scope)
When declared outside of a function (i.e., globally), `static` limits the variable’s visibility to the current file only. This is useful for encapsulation.
```c
static int global_counter = 0; // Only accessible within this file
```
Without `static`, a global variable has external linkage, meaning it can be accessed from other files using `extern`.

### 3. Static Functions
Similarly, prefixing a function with static limits its visibility to the current file.
```c
static void helper_function() {
    // This function can't be accessed from other files
}
```