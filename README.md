# Cooperative Multitasking Thread Library

This is a simple cooperative multitasking thread library implemented in C without using external threading libraries such as pthreads. It uses setjmp/longjmp for context switching.

## Features

- Create threads
- Delete threads
- Run threads
- Suspend and resume threads
- Sleep threads
- Show the status of threads

## Usage

1. **Compilation:**
   - Compile the code using a C compiler (e.g., gcc).

     ```bash
     gcc -o cooperative_threads cooperative_threads.c
     ```

2. **Execution:**
   - Run the compiled executable.

     ```bash
     ./cooperative_threads
     ```

3. **Example:**
   - The provided `main` function demonstrates the usage of the thread library.

4. **Functionality:**
   - Threads are created using `create_thread`.
   - Threads are scheduled and switched using `scheduler`.
   - Threads can be run, suspended, resumed, or put to sleep using various functions.
   - The status of threads can be shown using `show_status`.
   - Threads are deleted using `delete_thread`.

## Limitations

- This library is a simple implementation for educational purposes and hence lacks the features and performance of more robust threading libraries like pthreads.



- The library uses a timer signal (`SIGALRM`) for context switching between threads.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
