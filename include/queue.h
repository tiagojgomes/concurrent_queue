#ifndef QUEUE_H
#define QUEUE_H

#include <queue>


/**
 * @brief A multi-threaded queue implementation in C++.
 *
 * This class provides a thread-safe queue that supports simultaneous push and 
 * pop operations by different threads. It uses mutexes and condition variables 
 * to synchronize access to shared resources.
 *
 * @tparam T The type of elements stored in the queue.
 */
template <typename T>
class Queue {
public:
    /**
     * @brief Constructor for the Queue class.
     *
     * Initializes the maximum size of the queue.
     *
     * @param size Maximum size of the queue.
     */
    Queue(int size);


    /**
     * @brief Pushes an element onto the queue.
     *
     * This method blocks the calling thread if the queue is full until space 
     * becomes available.
     *
     * @param element The element to be added to the queue.
     */
    void Push(T element);


    /**
     * @brief Pops an element from the queue.
     *
     * This method blocks the calling thread if the queue is empty until an 
     * element becomes available.
     *
     * @return The element popped from the queue.
     */
    T Pop();


    /**
     * @brief Returns the current number of elements in the queue.
     *
     * @return The number of elements in the queue.
     */
    int Count() const;


    /**
     * @brief Returns the maximum size of the queue.
     *
     * @return The maximum size of the queue.
     */
    int Size() const;


private:
    std::queue<T> queue_;   // The internal queue to store elements.
    mutable std::mutex mutex_;  // Mutex for ensuring exclusive access to shared resources.
    std::condition_variable cv_pop_;    // Condition variable for pop operations.
    std::condition_variable cv_push_;   // Condition variable for push operations.
    int max_size;   // Maximum size of the queue.

    /**
     * @brief Waits for a push operation for a specified time.
     *
     * @param lock Unique lock associated with the mutex.
     * @return True if the push operation is successful within the time limit, 
     * false otherwise.
     */
    bool wait_for_push(std::unique_lock<std::mutex>& lock);
    
    /**
     * @brief Waits for a pop operation for a specified time.
     *
     * @param lock Unique lock associated with the mutex.
     * @return True if the pop operation is successful within the time limit, 
     * false otherwise.
     */
    bool wait_for_pop(std::unique_lock<std::mutex>& lock);
};

#endif // QUEUE_H
