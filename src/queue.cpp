#include <mutex>
#include <condition_variable>
#include "queue.h"


template <typename T>
Queue<T>::Queue(int size) : max_size(size){}


template <typename T>
void Queue<T>::Push(T element){
    std::unique_lock<std::mutex> lock(mutex_);
    while (queue_.size() >= max_size){
        // Wait until there's space
        if (!wait_for_push(lock)) return;
    }
    queue_.push(element);
    cv_pop_.notify_one();
}


template <typename T>
T Queue<T>::Pop() {
    std::unique_lock<std::mutex> lock(mutex_);
    // Wait until the queue is not empty
    cv_pop_.wait(lock, [this]{ return !queue_.empty(); });
    T element = queue_.front();
    queue_.pop();
    cv_push_.notify_one();
    return element;
}


template <typename T>
int Queue<T>::Count() const {
    std::unique_lock<std::mutex> lock(mutex_);
    return queue_.size();
}


template <typename T>
int Queue<T>::Size() const {
    return max_size;
}


template <typename T>
bool Queue<T>::wait_for_push(std::unique_lock<std::mutex>& lock) {
    return cv_push_.wait_for(lock, std::chrono::milliseconds(100)) == std::cv_status::no_timeout;
}


template <typename T>
bool Queue<T>::wait_for_pop(std::unique_lock<std::mutex>& lock) {
    return cv_pop_.wait_for(lock, std::chrono::milliseconds(100)) == std::cv_status::no_timeout;
}


template class Queue<int>; // Explicit instantiation of Queue<int>
