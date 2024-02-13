#include "gtest/gtest.h"
#include "queue.h"


/**
 * @brief Tests the Push and Pop methods of the Queue class.
 *
 * This test case creates a Queue object, pushes two elements into it, 
 * and then checks if the elements are popped in the correct order.
 */
TEST(QueueTest, PushPopTest) {
    Queue<int> queue(2);
    queue.Push(1);
    queue.Push(2);
    EXPECT_EQ(queue.Pop(), 1);
    EXPECT_EQ(queue.Pop(), 2);
}


/**
 * @brief Tests the Size and Count methods of the Queue class.
 *
 * This test case creates a Queue object, pushes two elements into it,
 * and then checks if the size and count of the queue are correct.
 */
TEST(QueueTest, SizeTest) {
    Queue<int> queue(2);
    queue.Push(1);
    queue.Push(2);
    EXPECT_EQ(queue.Size(), 2);
    EXPECT_EQ(queue.Count(), 2);
}
