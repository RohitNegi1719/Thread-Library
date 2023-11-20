#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define MAX_THREADS 100
#define STACK_SIZE 4096

typedef enum {
    READY,
    RUNNING,
    SUSPENDED,
    SLEEPING,
    TERMINATED
} ThreadStatus;

typedef struct {
    jmp_buf context;
    char stack[STACK_SIZE];
    ThreadStatus status;
} ThreadControlBlock;

ThreadControlBlock threads[MAX_THREADS];
int current_thread = -1;

void scheduler(int signal) {
    if (current_thread != -1)
        threads[current_thread].status = READY;

    do {
        current_thread = (current_thread + 1) % MAX_THREADS;
    } while (threads[current_thread].status != READY);

    threads[current_thread].status = RUNNING;
    longjmp(threads[current_thread].context, 1);
}

void thread_function() {
    int thread_id = current_thread;

    printf("Thread %d is running.\n", thread_id);

    // Simulate some work
    sleep(2);

    printf("Thread %d finished.\n", thread_id);

    threads[thread_id].status = TERMINATED;

    scheduler(SIGALRM); // Switch to the next thread
}

int create_thread() {
    static int thread_id_counter = 0;

    if (thread_id_counter >= MAX_THREADS) {
        printf("Error: Maximum number of threads reached.\n");
        return -1;
    }

    int thread_id = thread_id_counter++;

    if (setjmp(threads[thread_id].context) == 0) {
        threads[thread_id].status = READY;
        signal(SIGALRM, scheduler);
        alarm(1); // Set timer for context switch
        return thread_id;
    } else {
        thread_function();
        return -1; // This line is never reached
    }
}

void delete_thread(int thread_id) {
    if (thread_id < 0 || thread_id >= MAX_THREADS) {
        printf("Error: Invalid thread ID.\n");
        return;
    }

    if (threads[thread_id].status != TERMINATED) {
        printf("Error: Thread %d is not terminated.\n", thread_id);
        return;
    }

    printf("Thread %d deleted.\n", thread_id);
}

void run_thread(int thread_id) {
    if (thread_id < 0 || thread_id >= MAX_THREADS) {
        printf("Error: Invalid thread ID.\n");
        return;
    }

    threads[thread_id].status = RUNNING;
    longjmp(threads[thread_id].context, 1);
}

void suspend_thread(int thread_id) {
    if (thread_id < 0 || thread_id >= MAX_THREADS) {
        printf("Error: Invalid thread ID.\n");
        return;
    }

    threads[thread_id].status = SUSPENDED;
    scheduler(SIGALRM); // Switch to the next thread
}

void resume_thread(int thread_id) {
    if (thread_id < 0 || thread_id >= MAX_THREADS) {
        printf("Error: Invalid thread ID.\n");
        return;
    }

    threads[thread_id].status = READY;
    scheduler(SIGALRM); // Switch to the next thread
}

void sleep_thread(int thread_id, int seconds) {
    if (thread_id < 0 || thread_id >= MAX_THREADS) {
        printf("Error: Invalid thread ID.\n");
        return;
    }

    threads[thread_id].status = SLEEPING;
    alarm(seconds);
    scheduler(SIGALRM); // Switch to the next thread
}

void show_status(int thread_id) {
    if (thread_id < 0 || thread_id >= MAX_THREADS) {
        printf("Error: Invalid thread ID.\n");
        return;
    }

    switch (threads[thread_id].status) {
        case READY:
            printf("Thread %d is ready.\n", thread_id);
            break;
        case RUNNING:
            printf("Thread %d is running.\n", thread_id);
            break;
        case SUSPENDED:
            printf("Thread %d is suspended.\n", thread_id);
            break;
        case SLEEPING:
            printf("Thread %d is sleeping.\n", thread_id);
            break;
        case TERMINATED:
            printf("Thread %d has terminated.\n", thread_id);
            break;
    }
}

int main() {
    int thread1 = create_thread();
    int thread2 = create_thread();

    run_thread(thread1);
    sleep_thread(thread1, 2);
    show_status(thread1);

    suspend_thread(thread1);
    show_status(thread1);

    resume_thread(thread1);
    show_status(thread1);

    delete_thread(thread1);
    delete_thread(thread2);

    return 0;
}
