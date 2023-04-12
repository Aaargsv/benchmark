#ifndef TIMER_H
#define TIMER_H
#include <iostream>
#include <chrono>
#include <string>

class Timer {
public:
	Timer(const std::string &name):name(name)
	{
		start = std::chrono::high_resolution_clock::now();
	}
	
	~Timer() 
	{
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = end - start;
		std::cout << name <<": ";
		std::cout << duration.count() << "s\n";
	}

    void run()  
	{
        start = std::chrono::high_resolution_clock::now();
    }

    void stop()  
	{
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        std::cout << name <<": ";
        std::cout << duration.count() << "s\n";
    }

private:
	std::chrono::time_point<std::chrono::high_resolution_clock > start, end;
	std::string name;
};

#endif