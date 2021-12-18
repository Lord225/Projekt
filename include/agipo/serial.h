#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <string>
#include <sstream>
#include <array>
#include <optional>
#include <atomic>
#include <functional>
#include "usart.h"
#include "stm32f3xx_it.h"

constexpr size_t BUFFOR_COUNT = 3;

static_assert(std::atomic<bool>::is_always_lock_free == true); // If not, guarded is not safe to use.

template<typename T>
struct weak_mutex
{
    using lock_ref = std::optional<std::reference_wrapper<T>>;
    weak_mutex() = default;

    lock_ref try_lock()
    {
        __disable_irq();

        lock_ref status = std::nullopt;

        bool flag = false;
        
        if(this->is_locked_flag.compare_exchange_weak(flag, true))
            status = std::reference_wrapper(this->stream);

        __enable_irq();
    
        return status;
    }
    
    bool is_locked() const
    { 
        return this->is_locked_flag.load();
    }

    void unlock()
    {
        is_locked_flag.store(false);
    }

private:
    T stream;
    std::atomic<bool> is_locked_flag {false};    
};

class Monitor
{
    static std::array<weak_mutex<std::string>, BUFFOR_COUNT> cout;
public:
    static void flush(UART_HandleTypeDef& channel = huart2, size_t time_out = 5000);
    static void print(std::string message);

    static void timeoutHandler(std::string& stream);
    static void errorHandler(std::string& stream);
    static void outOfStreams();
};

void print(std::string message);

void println(std::string message);

#endif