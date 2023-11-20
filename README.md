# Cooperative Multitasking Thread Library

This is a simple cooperative multitasking thread library implemented in C without using external threading libraries such as pthreads. It uses setjmp/longjmp for context switching.

## Features

- **Create Threads:** Create cooperative threads using `create_thread`.
- **Delete Threads:** Terminate and delete threads using `delete_thread`.
- **Run Threads:** Start the execution of a thread with `run_thread`.
- **Suspend and Resume Threads:** Temporarily halt and resume thread execution with `suspend_thread` and `resume_thread`.
- **Sleep Threads:** Pause the execution of a thread for a specified duration using `sleep_thread`.
- **Show Thread Status:** Check and display the status of a thread with `show_status`.

## Code Overview

- **`ThreadStatus` Enumeration:** Defines different states a thread can be in.
- **`ThreadControlBlock` Structure:** Contains the thread's execution context, stack, and status.
- **`threads` Array:** Array to store multiple thread control blocks.
- **`current_thread` Variable:** Tracks the ID of the currently executing thread.

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
   - The provided `main` function in `cooperative_threads.c` demonstrates the usage of the thread library.

## Limitations

- It lacks the features and performance optimizations of advanced threading libraries.

## Notes

- Threads are scheduled using a timer signal (`SIGALRM`) for context switching.

