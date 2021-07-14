#include <iostream>
#include <thread>
#include <vector>

class LazySingleton
{
private:
    //static LazySingleton *instance;
    LazySingleton() {}

    LazySingleton(const LazySingleton&) = delete;
    LazySingleton& operator=(const LazySingleton&) = delete;

public:
    static LazySingleton* getInstance()
    {
        static LazySingleton instance;
        return &instance;
    }
};
//LazySingleton *LazySingleton::instance = nullptr;

int main()
{
    // 多线程单例
    std::vector<std::thread> workers;
    for (int i = 0; i < 5; ++i)
    {
        workers.push_back(std::thread([]()
        {
            // 令当前线程睡眠
            std::this_thread::sleep_for(std::chrono::seconds(1));
            LazySingleton* instance = LazySingleton::getInstance();
            std::cout << instance << std::endl;
        }));
    }
    for (int i = 0; i < 5; ++i)
    {
        workers[i].join();
    }

    // 单线程单例
    // LazySingleton *instance1 = LazySingleton::getInstance();
    // LazySingleton *instance2 = LazySingleton::getInstance();

    // std::cout << instance1 << std::endl;
    // std::cout << instance2 << std::endl;
    return 0;
}