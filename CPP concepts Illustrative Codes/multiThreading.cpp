// Multi-threading example

#include <iostream>
#include <thread>
#include <chrono>	// for sleep function

void doWork(){		
	
	// prints numbers 10-15 at a gap of 1s
	for (int i=10; i<=15; i++){
		std::cout<<i<<std::endl;
		std::this_thread::sleep_for (std::chrono::seconds(1));
	}	
}

int main() {
	
	std::thread worker(doWork);		// starts the function 'doWork' on a new thread called 'worker'
	
	// prints numbers 1-4 at a gap of 1s
	for (int i=1; i<=4; i++){
		std::cout<<i<<std::endl;
		std::this_thread::sleep_for (std::chrono::seconds(1));
	}
	
	worker.join();					// waits for 'worker' thread to finish and join back into main thread
	
	return 0;
}