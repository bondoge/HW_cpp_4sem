#include <iostream>
#include <chrono>


template <typename T>
class timer
{
private:
	std::chrono::steady_clock::time_point start;
	int past = 0;
	bool f = true;

public:
	timer(): start(std::chrono::steady_clock::now()) {}
	~timer()
	{
		if (f){
			std::cout << std::chrono::duration_cast<T>(std::chrono::steady_clock::now() - start).count() + past << std::endl;
		}
		else{
			std::cout << past << std::endl;
		}
	}

	void pause()
	{
		past += std::chrono::duration_cast<T>(std::chrono::steady_clock::now() - start).count();
		f = false;
	}

	void resume()
	{
		if (!f){
			start = std::chrono::steady_clock::now();
			f = true;
		}
	}
};

