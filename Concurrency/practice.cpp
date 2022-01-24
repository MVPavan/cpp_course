#include <iostream>
#include <thread>
#include <future>

class Vehicle
{
public:
    //default constructor
    Vehicle() : _id(0), _name(new std::string("Default Name"))
    {
        std::cout << "Vehicle #" << _id << " Default constructor called" << std::endl;
    }

    //initializing constructor
    Vehicle(int id, std::string name) : _id(id), _name(new std::string(name))
    {
        std::cout << "Vehicle #" << _id << " Initializing constructor called" << std::endl;
    }

    // copy constructor
    Vehicle(Vehicle const &src)
    {
        // QUIZ: Student code STARTS here
        _id = src._id;
        if (src._name != nullptr)
        {
            _name = new std::string;
            *_name = *src._name;
        }
        // QUIZ: Student code ENDS here
        std::cout << "Vehicle #" << _id << " copy constructor called" << std::endl;
    };

    // setter and getter
    void setID(int id) { _id = id; }
    int getID() { return _id; }
    void setName(std::string name) { *_name = name; }
    std::string getName() { return *_name; }

private:
    int _id;
    std::string *_name;
};

int main()
{
    // create instances of class Vehicle
    Vehicle v0;    // default constructor
    Vehicle v1(1, "Vehicle 1"); // initializing constructor

    // launch a thread that modifies the Vehicle name
    std::future<void> ftr = std::async([](Vehicle v) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work
        v.setName("Vehicle 2");
    },v0);

    v0.setName("Vehicle 3");

    ftr.wait();
    std::cout << v0.getName() << std::endl;

    return 0;
}
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

