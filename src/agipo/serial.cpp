#include "agipo/serial.h"

std::array<weak_mutex<std::string>, BUFFOR_COUNT> Monitor::cout;

void print(std::string message){
    Monitor::print(message);
}

void println(std::string message){
    message += '\n';
    print(message);
}

void Monitor::flush(UART_HandleTypeDef& channel, size_t time_out)
{
    for(auto& guarded_stream : cout)
    {
        auto opt = guarded_stream.try_lock();
        if(opt.has_value()) {
            std::string& stream = *opt;
            if(stream.size() != 0)
            {
                auto state = HAL_UART_Transmit(&channel, (uint8_t *)stream.c_str(), stream.length(), time_out);
                
                switch (state)
                {
                case HAL_StatusTypeDef::HAL_OK:
                    stream.clear();
                    break;
                case HAL_StatusTypeDef::HAL_TIMEOUT:
                    timeoutHandler(stream);
                    break;
                case HAL_StatusTypeDef::HAL_BUSY:
                    HardFault_Handler();
                    break;
                case HAL_StatusTypeDef::HAL_ERROR:
                default:
                    errorHandler(stream);
                    break;
                }
            }
            guarded_stream.unlock();
        }
    }
}   
void Monitor::print(std::string message)
{
    for(auto& guarded_stream : cout)
    {
        auto opt = guarded_stream.try_lock();
        if(opt.has_value())
        {
            std::string& stream = *opt;
            stream += message;
            guarded_stream.unlock();
            return;
        }
    }
    // No stream avalible
    outOfStreams();
}

void Monitor::timeoutHandler(std::string& stream)
{
    print("UART Error: Cannot flush stream of " + std::to_string(stream.size()) + " Bytes (Timeout)");
    stream.clear();
}
void Monitor::errorHandler(std::string& stream)
{
    print("UART Error: Cannot flush stream of " + std::to_string(stream.size()) + " Bytes (Other Error)");
    stream.clear();
}
void Monitor::outOfStreams()
{
    HardFault_Handler();
}