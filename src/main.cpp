#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "queue.h"


// Define a macro for easier output formatting
#define PRINT_MSG(msg) std::cout << msg << std::endl


/**
 * @brief Function representing a thread that writes elements to the queue.
 *
 * This function pushes elements onto the provided queue with some delay.
 * Each call to queue.Push() inserts an element into the queue.
 *
 * @param queue Reference to the queue where elements will be pushed.
 */
void writing_thread(Queue<int>& queue) {
    PRINT_MSG("Writing thread started...");

    for (int i = 1; i <= 5; ++i) {
        queue.Push(i);
        PRINT_MSG("Push(" << i << ")");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


/**
 * @brief Function representing a thread that reads elements from the queue.
 *
 * This function pops elements from the provided queue and prints them to the 
 * standard output.
 * Each call to queue.Pop() retrieves an element from the queue.
 */
void reading_thread(Queue<int>& queue) {
    // Ensure some delay before starting to read
    std::this_thread::sleep_for(std::chrono::seconds(2));
    PRINT_MSG("Reading thread started...");

    while (true) {
        int element = queue.Pop();
        // Break loop if Pop() returns 0 (indicating the queue is empty)
        if (element == 0)
            break;
        PRINT_MSG("Pop() -> " << element);
    }
}


/**
 * @brief Main function representing the entry point of the program.
 *
 * This function creates a queue and two threads: one for writing elements to 
 * the queue and another for reading elements from the queue. After both threads 
 * finish their execution, the program joins them and terminates.
 *
 * @return An integer representing the exit status of the program.
 */
int main() {
    PRINT_MSG("Main thread started...");

    // Creates a queue with a maximum size of 2
    Queue<int> queue(2);

    // Creates a thread for writing elements to the queue
    std::thread writer(writing_thread, std::ref(queue));
    // Creates a thread for reading elements from the queue
    std::thread reader(reading_thread, std::ref(queue));
    
    writer.join();  // Waits for the writer thread to finish
    reader.join();  // Waits for the reader thread to finish
    
    PRINT_MSG("Main thread finished...");

    return 0;
}
