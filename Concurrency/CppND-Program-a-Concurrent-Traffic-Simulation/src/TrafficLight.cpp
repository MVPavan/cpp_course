#include <iostream>
#include <random>
#include "TrafficLight.h"



/* Implementation of class "MessageQueue" */

template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function.

    std::unique_lock<std::mutex> u_lock(_mutex);
    _cond_var.wait(u_lock,[this](){return !_queue.empty();});
    T obj = std::move(_queue.front());
    _queue.pop_front();
    return obj;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.

    std::unique_lock<std::mutex> u_lock(_mutex);
    _queue.clear();
    _queue.emplace_back(std::move(msg));
    _cond_var.notify_one();
}

/* Implementation of class "TrafficLight" */

TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
    while(msg_q.receive() != TrafficLightPhase::green){}
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    std::unique_lock<std::mutex> u_lock(_mutex);
    return _currentPhase;
}

void TrafficLight::setCurrentPhase(TrafficLightPhase phase)
{
    std::unique_lock<std::mutex> u_lock(_mutex);
    _currentPhase = phase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class.
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
[[noreturn]] void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles.

    time_point old_t, new_t;
    const int delay_choice[2] = {4000,6000}; // 4/6 sec in milli-sec format
    std::random_device rd; // TO generate random choice between 4 and 6 secs

    //Lambda function to get current time
    auto current_time = [](){return std::chrono::high_resolution_clock::now();};
    // Lambda function to calculate duration in milli secs
    auto elapsed_time = [&old_t, &new_t](){
        new_t = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(new_t-old_t).count();
    };

    old_t = current_time();
    int delay = delay_choice[rd() % 2];

    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        if(elapsed_time()- delay> 0){
            if(getCurrentPhase() == TrafficLightPhase::red)
                setCurrentPhase(TrafficLightPhase::green);
            else
                setCurrentPhase(TrafficLightPhase::red);
            msg_q.send(std::move(getCurrentPhase()));
            old_t = current_time();
            delay = delay_choice[rd() %2];
        }
    }
}

