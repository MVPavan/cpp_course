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


//#include <iostream>
//#include <thread>
//#include <vector>
//#include <future>
//#include <mutex>
//
//class Vehicle
//{
//public:
//    Vehicle(int id) : _id(id) {}
//    int getID() { return _id; }
//
//private:
//    int _id;
//};
//
//class WaitingVehicles
//{
//public:
//    WaitingVehicles() {}
//
//    Vehicle popBack()
//    {
//        // perform vector modification under the lock
//        std::unique_lock<std::mutex> uLock(_mutex);
//        _cond.wait(uLock, [this] (){ return !_vehicles.empty(); }); // pass unique lock to condition variable
//
//        // remove last vector element from queue
//        Vehicle v = std::move(_vehicles.back());
//        _vehicles.pop_back();
//
//        return v; // will not be copied due to return value optimization (RVO) in C++
//    }
//
//    void pushBack(Vehicle &&v)
//    {
//        // simulate some work
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
//
//        // perform vector modification under the lock
//        std::lock_guard<std::mutex> uLock(_mutex);
//
//        // add vector to queue
//        std::cout << "   Vehicle #" << v.getID() << " will be added to the queue" << std::endl;
//        _vehicles.push_back(std::move(v));
//        _cond.notify_one(); // notify client after pushing new Vehicle into vector
//    }
//
//private:
//    std::mutex _mutex;
//    std::condition_variable _cond;
//    std::vector<Vehicle> _vehicles; // list of all vehicles waiting to enter this intersection
//};
//
//int main()
//{
//    // create monitor object as a shared pointer to enable access by multiple threads
//    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
//
//    std::cout << "Spawning threads..." << std::endl;
//    std::vector<std::future<void>> futures;
//    for (int i = 0; i < 10; ++i)
//    {
//        // create a new Vehicle instance and move it into the queue
//        Vehicle v(i);
//        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
//    }
//
//    std::cout << "Collecting results..." << std::endl;
//    while (true)
//    {
//        // popBack wakes up when a new element is available in the queue
//        Vehicle v = queue->popBack();
//        std::cout << "   Vehicle #" << v.getID() << " has been removed from the queue" << std::endl;
//    }
//
//    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
//        ftr.wait();
//    });
//
//    std::cout << "Finished!" << std::endl;
//
//    return 0;
//}

//#include <iostream>
//#include <thread>
//#include <vector>
//#include <future>
//#include <mutex>
//#include <algorithm>
//
//class Vehicle
//{
//public:
//    Vehicle(int id) : _id(id) {}
//    int getID() { return _id; }
//
//private:
//    int _id;
//};
//
//class WaitingVehicles
//{
//public:
//    WaitingVehicles() : _numVehicles(0) {}
//
//    int getNumVehicles()
//    {
//        std::lock_guard<std::mutex> uLock(_mutex);
//        return _numVehicles;
//    }
//
//    bool dataIsAvailable()
//    {
//        std::lock_guard<std::mutex> myLock(_mutex);
//        return !_vehicles.empty();
//    }
//
//    Vehicle popBack()
//    {
//        // perform vector modification under the lock
//        std::lock_guard<std::mutex> uLock(_mutex);
//
//        // remove last vector element from queue
//        Vehicle v = std::move(_vehicles.back());
//        _vehicles.pop_back();
//        --_numVehicles;
//
//        return v; // will not be copied due to return value optimization (RVO) in C++
//    }
//
//    void pushBack(Vehicle &&v)
//    {
//        // simulate some work
//
//        // perform vector modification under the lock
//        std::lock_guard<std::mutex> uLock(_mutex);
//
//        // add vector to queue
//        std::cout << "   Vehicle #" << v.getID() << " will be added to the queue" << std::endl;
//        _vehicles.emplace_back(std::move(v));
//        ++_numVehicles;
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
//
//    }
//
//private:
//    std::vector<Vehicle> _vehicles; // list of all vehicles waiting to enter this intersection
//    std::mutex _mutex;
//    int _numVehicles;
//};
//
//int main()
//{
//    // create monitor object as a shared pointer to enable access by multiple threads
//    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
//
//    std::cout << "Spawning threads..." << std::endl;
//    std::vector<std::future<void>> futures;
//    for (int i = 0; i < 10; ++i)
//    {
//        // create a new Vehicle instance and move it into the queue
//        Vehicle v(i);
//        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
//    }
//
//    std::cout << "Collecting results..." << std::endl;
//    while (true)
//    {
//        if (queue->dataIsAvailable())
//        {
//            Vehicle v = queue->popBack();
//            std::cout << "   Vehicle #" << v.getID() << " has been removed from the queue" << std::endl;
//
//            if(queue->getNumVehicles()<=0)
//            {
//                std::this_thread::sleep_for(std::chrono::milliseconds(200));
//                break;
//            }
//        }
//    }
//
//    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
//        ftr.wait();
//    });
//
//    std::cout << "Finished : " << queue->getNumVehicles() << " vehicle(s) left in the queue" << std::endl;
//
//    return 0;
//}

//#include <iostream>
//#include <thread>
//#include <vector>
//#include <future>
//#include <mutex>
//#include <algorithm>
//
//class Vehicle
//{
//public:
//    Vehicle(int id) : _id(id) {}
//    int getID() { return _id; }
//
//private:
//    int _id;
//};
//
//class WaitingVehicles
//{
//public:
//    WaitingVehicles() {}
//
//    bool dataIsAvailable()
//    {
//        std::lock_guard<std::mutex> myLock(_mutex);
//        return !_vehicles.empty();
//    }
//
//    int vehicleCount(){
//        std::unique_lock<std::mutex> lck(_mutex);
//        return _vehicle_counter;
//    }
//
//    Vehicle popBack()
//    {
//        // perform vector modification under the lock
//        std::lock_guard<std::mutex> uLock(_mutex);
//
//        // remove last vector element from queue
//        Vehicle v = std::move(_vehicles.back());
//        _vehicles.pop_back();
//        _vehicle_counter--;
//        return v; // will not be copied due to return value optimization (RVO) in C++
//    }
//
//    void pushBack(Vehicle &&v)
//    {
//        // simulate some work
//
//        // perform vector modification under the lock
//        std::lock_guard<std::mutex> uLock(_mutex);
//
//        // add vector to queue
//        std::cout << "   Vehicle #" << v.getID() << " will be added to the queue" << std::endl;
//        _vehicles.emplace_back(std::move(v));
//        _vehicle_counter++;
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
//
//    }
//
//private:
//    std::vector<Vehicle> _vehicles; // list of all vehicles waiting to enter this intersection
//    std::mutex _mutex;
//    int _vehicle_counter{0};
//};
//
//int main()
//{
//    // create monitor object as a shared pointer to enable access by multiple threads
//    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
//
//    std::cout << "Spawning threads..." << std::endl;
//    std::vector<std::future<void>> futures;
//    for (int i = 0; i < 10; ++i)
//    {
//        // create a new Vehicle instance and move it into the queue
//        Vehicle v(i);
//        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
//    }
//
//    std::cout << "Collecting results..." << std::endl;
//    while (queue->vehicleCount()>0)
//    {
//        if (queue->dataIsAvailable())
//        {
//            Vehicle v = queue->popBack();
//            std::cout << "   Vehicle #" << v.getID() << " has been removed from the queue" << std::endl;
//        }
//
//    }
//
//    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
//        ftr.wait();
//    });
//
//    std::cout << "Finished processing queue" << std::endl;
//
//    return 0;
//}

//
//#include <iostream>
//#include <thread>
//#include <vector>
//#include <future>
//#include <mutex>
//#include <algorithm>
//
//class Vehicle
//{
//public:
//    Vehicle(int id) : _id(id) {}
//    int getID() { return _id; }
//
//private:
//    int _id;
//};
//
//class WaitingVehicles
//{
//public:
//    WaitingVehicles() {}
//
//    void printIDs()
//    {
//        std::lock_guard<std::mutex> myLock(_mutex); // lock is released when myLock goes out of scope
//        for(auto &v : _vehicles)
//            std::cout << "   Vehicle #" << v.getID() << " is now waiting in the queue" << std::endl;
//
//    }
//
//    void pushBack(Vehicle &&v)
//    {
//        // perform vector modification under the lock
//        std::lock_guard<std::mutex> uLock(_mutex);
//        std::cout << "   Vehicle #" << v.getID() << " will be added to the queue" << std::endl;
//        _vehicles.emplace_back(std::move(v));
//
//        // simulate some work
//        std::this_thread::sleep_for(std::chrono::milliseconds(500));
//    }
//
//private:
//    std::vector<Vehicle> _vehicles; // list of all vehicles waiting to enter this intersection
//    std::mutex _mutex;
//};
//
//int main()
//{
//    // create monitor object as a shared pointer to enable access by multiple threads
//    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
//
//    std::cout << "Spawning threads..." << std::endl;
//    std::vector<std::future<void>> futures;
//    for (int i = 0; i < 10; ++i)
//    {
//        // create a new Vehicle instance and move it into the queue
//        Vehicle v(i);
//        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
//    }
//
//    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
//        ftr.wait();
//    });
//
//    std::cout << "Collecting results..." << std::endl;
//    queue->printIDs();
//
//    return 0;
//}
//

//#include <iostream>
//#include <thread>
//#include <vector>
//#include <future>
//#include <algorithm>
//#include <mutex>
//
//
//double result;
//std::mutex mutex_flag;
//
//void printResult(int denom)
//{
//    mutex_flag.lock();
//    std::cout << "for denom = " << denom << ", the result is " << result << std::endl;
//    mutex_flag.unlock();
//
//}
//
//void divideByNumber(double num, double denom)
//{
//    mutex_flag.lock();
//
//    try
//    {
//        // divide num by denom but throw an exception if division by zero is attempted
//        if (denom != 0)
//        {
//            result = num / denom;
//
//            std::this_thread::sleep_for(std::chrono::milliseconds(1));
//            printResult(denom);
//
//        }
//        else
//        {
//            throw std::invalid_argument("Exception from thread: Division by zero!");
//        }
//    }
//    catch (const std::invalid_argument &e)
//    {
//        // notify the user about the exception and return
//        std::cout << e.what() << std::endl;
//        return;
//    }
//    mutex_flag.unlock();
//
//}
//
//int main()
//{
//    // create a number of threads which execute the function "divideByNumber" with varying parameters
//    std::vector<std::future<void>> futures;
//    for (double i = -5; i <= +5; ++i)
//    {
//        futures.emplace_back(std::async(std::launch::async, divideByNumber, 50.0, i));
//    }
//
//    // wait for the results
//    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
//        ftr.wait();
//    });
//
//    return 0;
//}

//#include <iostream>
//#include <thread>
//#include <vector>
//#include <future>
//#include <mutex>
//#include<algorithm>
//
//class Vehicle
//{
//public:
//    Vehicle(int id) : _id(id) {}
//    int getID() { return _id; }
//
//private:
//    int _id;
//};
//
//class WaitingVehicles
//{
//public:
//    WaitingVehicles() {}
//
//    // getters / setters
//    void printSize()
//    {
//        _mutex.lock();
//        std::cout << "#vehicles = " << _vehicles.size() << std::endl;
//        _mutex.unlock();
//    }
//
//    // typical behaviour methods
//    void pushBack(Vehicle &&v)
//    {
//        for (size_t i = 0; i < 3; ++i)
//        {
//            if (_mutex.try_lock_for(std::chrono::milliseconds(100)))
//            {
//                _vehicles.emplace_back(std::move(v));
//                //std::this_thread::sleep_for(std::chrono::milliseconds(10));
//                _mutex.unlock();
//                break;
//            }
//            else
//            {
//                std::cout << "Error! Vehicle #" << v.getID() << " could not be added to the vector" << std::endl;
//                std::this_thread::sleep_for(std::chrono::milliseconds(100));
//            }
//        }
//    }
//
//private:
//    std::vector<Vehicle> _vehicles; // list of all vehicles waiting to enter this intersection
//    std::timed_mutex _mutex;
//};
//
//int main()
//{
//    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
//    std::vector<std::future<void>> futures;
//    for (int i = 0; i < 1000; ++i)
//    {
//        Vehicle v(i);
//        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
//    }
//
//    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
//        ftr.wait();
//    });
//
//    queue->printSize();
//
//    return 0;
//}



//#include <iostream>
//#include <thread>
//#include <vector>
//#include <future>
//#include<algorithm>
//#include <mutex>
//
//class Vehicle
//{
//public:
//    Vehicle(int id) : _id(id) {}
//
//private:
//    int _id;
//};
//
//class WaitingVehicles
//{
//public:
//    WaitingVehicles() : _tmpVehicles(0) {}
//
//    // getters / setters
//    void printSize()
//    {
//        _mutex.lock();
//        std::cout << "#vehicles = " << _tmpVehicles << std::endl;
//        _mutex.unlock();
//    }
//
//    // typical behaviour methods
//    void pushBack(Vehicle &&v)
//    {
//        _mutex.lock();
////        _vehicles.push_back(v); // data race would cause an exception
//        _vehicles.emplace_back(v);
//        int oldNum = _tmpVehicles;
//        std::this_thread::sleep_for(std::chrono::microseconds(1)); // wait deliberately to expose the data race
//        _tmpVehicles = oldNum + 1;
//        _mutex.unlock();
//    }
//
//private:
//    std::vector<Vehicle> _vehicles; // list of all vehicles waiting to enter this intersection
//    int _tmpVehicles;
//    std::mutex _mutex;
//};
//
//int main()
//{
//    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
//    std::vector<std::future<void>> futures;
//    for (int i = 0; i < 1000; ++i)
//    {
//        Vehicle v(i);
//        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, v));
//    }
//
//    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
//        ftr.wait();
//    });
//
//    queue->printSize();
//
//    return 0;
//}






//#include <iostream>
//#include <thread>
//#include <future>
//
//class Vehicle
//{
//public:
//    //default constructor
//    Vehicle() : _id(0), _name(new std::string("Default Name"))
//    {
//        std::cout << "Vehicle #" << _id << " Default constructor called" << std::endl;
//    }
//
//    //initializing constructor
//    Vehicle(int id, std::string name) : _id(id), _name(new std::string(name))
//    {
//        std::cout << "Vehicle #" << _id << " Initializing constructor called" << std::endl;
//    }
//
//    // copy constructor
//    Vehicle(Vehicle const &src)
//    {
//        // QUIZ: Student code STARTS here
//        _id = src._id;
//        if (src._name != nullptr)
//        {
//            _name = new std::string;
//            *_name = *src._name;
//        }
//        // QUIZ: Student code ENDS here
//        std::cout << "Vehicle #" << _id << " copy constructor called" << std::endl;
//    };
//
//    // setter and getter
//    void setID(int id) { _id = id; }
//    int getID() { return _id; }
//    void setName(std::string name) { *_name = name; }
//    std::string getName() { return *_name; }
//
//private:
//    int _id;
//    std::string *_name;
//};
//
//int main()
//{
//    // create instances of class Vehicle
//    Vehicle v0;    // default constructor
//    Vehicle v1(1, "Vehicle 1"); // initializing constructor
//
//    // launch a thread that modifies the Vehicle name
//    std::future<void> ftr = std::async([](Vehicle v) {
//        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work
//        v.setName("Vehicle 2");
//    },v0);
//
//    v0.setName("Vehicle 3");
//
//    ftr.wait();
//    std::cout << v0.getName() << std::endl;
//
//    return 0;
//}
//#include <iostream>
//#include <thread>
//#include <future>
//#include <cmath>
//#include <vector>
//#include <chrono>
//
//void workerFunction(int n)
//{
//    // print system id of worker thread
//    std::cout << "Worker thread id = " << std::this_thread::get_id() << std::endl;
//
//    // perform work
//    for (int i = 0; i < n; ++i)
//    {
//        sqrt(12345.6789);
//    }
//}
//
//int main()
//{
//    // print system id of worker thread
//    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;
//
//    // start time measurement
//    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
//
//    // launch various tasks
//    std::vector<std::future<void>> futures;
//    int nLoops = 1e7, nThreads = 5;
//    futures.reserve(nThreads);
//    for (int i = 0; i < nThreads; ++i)
//    {
//        futures.emplace_back(std::async( std::launch::deferred, workerFunction, nLoops));
//    }
//
//    // wait for tasks to complete
//    for (const std::future<void> &ftr : futures)
//        ftr.wait();
//
//    // stop time measurement and print execution time
//    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
//    std::cout << "Execution finished after " << duration <<" microseconds" << std::endl;
//
//    return 0;
//}

//
//#include <iostream>
//#include <thread>
//#include <future>
//
//void modifyMessage(std::promise<std::string> && prms, std::string message)
//{
//    std::this_thread::sleep_for(std::chrono::milliseconds(4000)); // simulate work
//    std::string modifiedMessage = message + " has been modified";
//    prms.set_value(modifiedMessage);
//}
//
//int main()
//{
//    // define message
//    std::string messageToThread = "My Message";
//
//    // create promise and future
//    std::promise<std::string> prms;
//    std::future<std::string> ftr = prms.get_future();
//
//    // start thread and pass promise as argument
//    std::thread t(modifyMessage, std::move(prms), messageToThread);
//
//    // print original message to console
//    std::cout << "Original message from main(): " << messageToThread << std::endl;
//
//    // retrieve modified message via future and print to console
//    std::string messageFromThread = ftr.get();
//    std::cout << "Modified message from thread(): " << messageFromThread << std::endl;
//
//    // thread barrier
//    t.join();
//
//    return 0;
//}

//
//#include <iostream>
//#include <thread>
//#include <vector>
//
//void printHello()
//{
//    // perform work
//    std::cout << "Hello from Worker thread #" << std::this_thread::get_id() << std::endl;
//}
//
//int main()
//{
//    // create threads
//    std::vector<std::thread> threads;
//    for (size_t i = 0; i < 5; ++i)
//    {
//        // copying thread objects causes a compile error
//        /*
//        std::thread t(printHello);
//        threads.push_back(t);
//        */
//
//        // moving thread objects will work
//        threads.emplace_back(std::thread(printHello));
//    }
//
//    // do something in main()
//    std::cout << "Hello from Main thread #" << std::this_thread::get_id() << std::endl;
//
//    // call join on all thread objects using a range-based loop
//    for (auto &t : threads)
//        t.join();
//
//    return 0;
//}



//#include <iostream>
//#include <thread>
//
//class Vehicle
//{
//public:
//    Vehicle() : _id(0) {}
//    void addID(int id) { _id = id; }
//    void printID() const
//    {
//        std::cout << "Vehicle ID=" << _id << std::endl;
//    }
//
//    void setName(std::string name){
//        name = name+"wow";
//        _name = name;
//    }
//    void printName(){
//        std::cout << "Vehicle Name: "<< _name << std::endl;
//    }
//
//private:
//    int _id;
//    std::string _name;
//};
//
//int main()
//{
//    // create thread
//    Vehicle v1, v2, v3;
//    auto v4 = std::make_shared<Vehicle>();
//    std::thread t1 = std::thread(&Vehicle::addID, v1, 1); // call member function on object v
//    std::thread t2 = std::thread(&Vehicle::addID, &v2, 2); // call member function on object v
//    std::thread t3(&Vehicle::addID, v3, 3);
//    std::thread t4(&Vehicle::addID, v4, 4);
//    std::string name_str("I20");
//    std::thread t5(&Vehicle::setName, v4, name_str);
//    // wait for thread to finish
//    t1.join();
//    t2.join();
//    t3.join();
//    t4.join();
//    t5.join();
//
//    // print Vehicle id
//    v1.printID();
//    v2.printID();
//    v3.printID();
//    v4->printID();
//    v4->printName();
//    std::cout<<name_str;
//
//    return 0;
//}

//
//
//#include <iostream>
//#include <thread>
//
//int main()
//{
//    int id = 0; // Define an integer variable
//
//    // starting a first thread (by reference)
//    auto f0 = [&id]() {
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
//        std::cout << "a) ID in Thread (call-by-reference) = " << id << std::endl;
//    };
//    std::thread t1(f0);
//
//    // starting a second thread (by value)
//    std::thread t2([id]() mutable {
//        std::this_thread::sleep_for(std::chrono::milliseconds(50));
//        std::cout << "b) ID in Thread (call-by-value) = " << id << std::endl;
//    });
//
//    // increment and print id in main
//    ++id;
//    std::cout << "c) ID in Main (call-by-value) = " << id << std::endl;
//
//    // wait for threads before returning
//    t1.join();
//    t2.join();
//
//    return 0;
//}


//
//#include <iostream>
//#include <thread>
//
//class Vehicle
//{
//public:
//    explicit Vehicle(int id) : _id(id) {}
//    void operator()() const
//    {
//        std::cout << "Vehicle #" << _id << " has been created" << std::endl;
//    }
//
//private:
//    int _id;
//};
//
//
//int main()
//{
//    // create thread
//    std::thread t((Vehicle(5))); // C++'s most vexing parse
//
//    // do something in main()
//    std::cout << "Finished work in main \n";
//
//    // wait for thread to finish
//    t.join();
//
//    return 0;
//}









//#include <iostream>
//#include <thread>
//
//void threadFunctionEven()
//{
//    std::this_thread::sleep_for(std::chrono::milliseconds(1)); // simulate work
//    std::cout << "Even thread\n";
//}
//
///* Student Task START */
//void threadFunctionOdd()
//{
//    std::this_thread::sleep_for(std::chrono::milliseconds(1)); // simulate work
//    std::cout << "Odd thread\n";
//}
///* Student Task END */
//
//int main()
//{
//    /* Student Task START */
//
//    for(size_t i=0;i<6;i++){
//        if(i%2==0){
//            std::thread t(threadFunctionEven);
//            t.detach();
//        }
//        else{
//            std::thread t(threadFunctionOdd);
//            t.detach();
//        }
//    }
//
//    /* Student Task END */
//
//    // ensure that main does not return before the threads are finished
//    std::this_thread::sleep_for(std::chrono::milliseconds(1)); // simulate work
//
//    std::cout << "End of main is reached" << std::endl;
//    return 0;
//}

