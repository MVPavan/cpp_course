//
// Created by pavanmv on 25/01/22.
//

#include <algorithm>
#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <deque>



template <typename T>
class MessageQueue
{
public:
    void send(T &&obj) {
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::unique_lock<std::mutex> u_lock(_mtx);
        std::cout << "Message : " << obj << " added to the DQ ..." << std::endl;
        _messages.emplace_back(std::move(obj));
        _cond_var.notify_one();
    }

    T receive(){
//        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        std::unique_lock<std::mutex> u_lock(_mtx);
        _cond_var.wait(u_lock,[this](){return !_messages.empty();});
        T obj = std::move(_messages.front());
        _messages.pop_front();
        std::cout << "Message : " << obj << " obtained from DQ" << std::endl;
        return obj;
    }

    bool checkMsgEmpty(){
        std::unique_lock<std::mutex> u_lock(_mtx);
        return _messages.empty();
    }

private:
    std::deque<T> _messages;
    std::mutex _mtx;
    std::condition_variable _cond_var;
};

int main(){
    auto mq = std::make_shared<MessageQueue<std::string>>();
    std::cout << "Spawning threads..." << std::endl;
    std::vector<std::future<void>> _futures;
    for(size_t i=0; i<10 ; i++){
        std::string str_obj{"MID - " + std::to_string(i)};
        _futures.emplace_back(std::async(std::launch::async, &MessageQueue<std::string>::send, mq, std::move(str_obj) ));
    }

    for(auto &ftr: _futures) {
        while ([&ftr]() {
            auto status = ftr.wait_for(std::chrono::nanoseconds(1));
            return status != std::future_status::ready;
        }() || !mq->checkMsgEmpty()
                ){
            mq->receive();
        }
    }

    std::for_each(_futures.begin(), _futures.end(), [](std::future<void> &ftr) {
        auto status = ftr.wait_for(std::chrono::nanoseconds(1));
        if(status != std::future_status::ready){
            std::cout << "Oops!!" <<std::endl;
        }
    });

    std::cout << "Successfully Came out of Loop!" << std::endl;
    return 0;
}
