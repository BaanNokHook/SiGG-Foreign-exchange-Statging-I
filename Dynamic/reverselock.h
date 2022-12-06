/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_REVERSELOCK_H
#define DYNAMIC_REVERSELOCK_H

/**
 * An RAII-style reverse lock. Unlocks on construction and locks on destruction.
 */
template <typename Lock>
class reverse_lock
{
public:
    explicit reverse_lock(Lock& _lock) : lock(_lock)
    {
        _lock.unlock();
        lock.swap(templock);
    }

    ~reverse_lock()
    {
        templock.lock();
        templock.swap(lock);
    }

private:
    reverse_lock(reverse_lock const&);
    reverse_lock& operator=(reverse_lock const&);

    Lock& lock;
    Lock templock;
};

#endif // DYNAMIC_REVERSELOCK_H
