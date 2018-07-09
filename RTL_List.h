/*******************************************************************************
Header file for Queue template class.
*******************************************************************************/
#ifndef _RTL_List_h_
#define _RTL_List_h_

#include <inttypes.h>


template <typename T, int _list_size=10> class List
{
    public: List() : _count(0) { };


    public: bool Add(T item)
    {
        /*
        Interrupts MUST be disabled while an item is being added to ensure stability
        while the list is being manipulated. But, disabling interrupts MUST come
        BEFORE the full list check is done.

        If the full list check is FALSE and an asynchronous interrupt queues an
        item while that check is being made, thus making the list full, the current
        insert operation will then corrupt the list queue (because it will add an item
        to an already full list). So the entire operation, from the full list check
        to completing the insert must be atomic.

        Note that this race condition can only happen when an item is added by normal
        (non-interrupt) code and simultaneously an interrupt also tries to add an item.
        In the case where only normal code is adding items, this can't happen because
        then there are no interrupts that could asynchronously add an item. Conversely,
        if only interrupts are adding items, it can't happen either because further
        interrupts are blocked while the current interrupt is being serviced. In the
        general case, however, we have to assume that items could be added to the list
        both ways. So, to protect against this race condition, we have to disable interrupts.

        Contrast this with the logic in the Remove() method.
        */

        bool added = false;

        noInterrupts(); // ATOMIC BLOCK BEGIN

        if (!IsFull())
        {
            _list[_count++] = item;
            added = true;
        }

        interrupts(); // ATOMIC BLOCK END

        return added;
    }


    public: bool Remove(int index)
    {
        /*
        Interrupts MUST be disabled while an item is being removed to ensure
        stability while the list is being manipulated. HOWEVER, disabling
        interrupts (the call to cli) MUST come AFTER the empty list check.

        If interrupts are suppressed before the empty list check, we pretty much
        lock-up the system. This is because Remove() is normally called inside
        loop(), which means it is called VERY OFTEN.  Most of the time (>99%), the
        list will probably be empty. But that means that we'll have interrupts turned
        off for a significant fraction of the time. We don't want to do that. We only
        want interrupts turned off when we actually have an item to remove.

        Contrast this with the logic in the Add() method.
        */

        if (IsEmpty()) return false;

        bool removed = false;

        noInterrupts(); // ATOMIC BLOCK BEGIN

        if (0 <= index && index < _count)
        {
            memcpy(&_list[index], &list[index + 1], ((_count - index) - 1) * sizeof(*_list));
            _count--;
            removed = true;
        }

        interrupts(); // ATOMIC BLOCK END

        return removed;
    }


    public: bool Remove(T& item)
    {
        bool removed = false;

        for (int i = 0; i < _count; i++)
        {
            if (_list[i] == item)
            {
                removed = Remove(i);
                break;
            }
        }

        return removed;
    }


    public: T Get(int index)
    {
        bool found = false;

        noInterrupts(); // ATOMIC BLOCK BEGIN

        if (0 <= index && index < _count)
        {
            item = _list[index];
            found = true;
        }

        interrupts(); // ATOMIC BLOCK END

        return found;
    }


    public: inline int Count() { return _count; };


    public: inline bool IsFull() { return (_count == _list_size); };


    public: inline bool IsEmpty() { return (_count == 0); };


    public: inline T& operator[](size_t index) { return _list[index]; };


    public: inline const T& operator[](size_t index) const { return _list[index]; };


    private: const int LIST_SIZE = _list_size;
    private: T _list[_list_size];
    private: uint8_t _count;
};

#endif

