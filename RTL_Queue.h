/*******************************************************************************
Header file for Queue template class.
*******************************************************************************/
#ifndef _Queue_h_
#define _Queue_h_

#include <inttypes.h>


template <typename T, uint8_t _queue_size=10> class Queue
{
    public: Queue() : _queueHead(0), _queueTail(0), _queueCount(0) { };


    public: bool Add(T item)
    {
        /*
        Interrupts MUST be disabled while an item is being queued to ensure stability
        while the queue is being manipulated. But, disabling interrupts MUST come
        BEFORE the full queue check is done.

        If the full queue check is FALSE and an asynchronous interrupt queues an
        item while that check is being made, thus making the queue full, the current
        insert operation will then corrupt the queue (because it will add an item to
        an already full queue). So the entire operation, from the full queue check to
        completing the insert must be atomic.

        Note that this race condition can only happen when an item is queued by normal
        (non-interrupt) code and simultaneously an interrupt also tries to queue an item.
        In the case where only normal code is queueing items, this can't happen because
        then there are no interrupts that could asynchronously queue an item. Conversely,
        if only interrupts are queueing items, it can't happen either because further
        interrupts are blocked while the current interrupt is being serviced. In the
        general case, however, we have to assume that items could enter the queue both
        ways. So, to protect against this race condition, we have to disable interrupts.

        Contrast this with the logic in the Remove() method.
        */

        bool isQueued = false;
        int  i = _queueTail;

        noInterrupts();                 // ATOMIC BLOCK BEGIN

        if (_queueCount <= EVENT_QUEUE_SIZE)
        {
            _queue[_queueTail] = item;
            _queueTail = (_queueTail + 1) % EVENT_QUEUE_SIZE;
            _queueCount++;

            isQueued = true;
        }

        interrupts();                   // ATOMIC BLOCK END

        return isQueued;
    }


    public: bool Remove(T& item)
    {
        /*
        Interrupts MUST be disabled while an item is being de-queued to ensure
        stability while the queue is being manipulated. HOWEVER, disabling
        interrupts (the call to cli) MUST come AFTER the empty queue check.

        There is no harm if the empty check produces an "incorrect" TRUE response
        while an asynchronous interrupt queues. It will just pick up that item
        the next time Dequeue() is called.

        If interrupts are suppressed before the empty queue check, we pretty much
        lock-up the system. This is because Dequeue() is normally called inside
        loop(), which means it is called VERY OFTEN.  Most of the time (>99%), the
        item queue will be empty. But that means that we'll have interrupts turned
        off for a significant fraction of the time. We don't want to do that. We only
        want interrupts turned off when we actually have an item to de-queue.

        Contrast this with the logic in the Queue() method.
        */

        if (_queueHead == _queueTail) return false;

        noInterrupts();                 // ATOMIC BLOCK BEGIN

        item = _queue[_queueHead];
        _queueHead = (_queueHead + 1) % EVENT_QUEUE_SIZE;
        _queueCount--;

        interrupts();                   // ATOMIC BLOCK END

        return true;
    }


    public: inline bool Peek(T& item)
    {
        if (!IsEmpty())
        {
            noInterrupts();             // ATOMIC BLOCK BEGIN
            item = _queue[_queueHead];
            interrupts();               // ATOMIC BLOCK END
            return true;
        }

        return false;
    };


    public: inline bool IsFull() { return (_queueCount == _queue_size); };


    public: inline bool IsEmpty() { return (_queueCount == 0); };


    private: const uint8_t EVENT_QUEUE_SIZE = _queue_size;
    private: T _queue[_queue_size];
    private: uint8_t _queueHead;
    private: uint8_t _queueTail;
    private: uint8_t _queueCount;
};

#endif

