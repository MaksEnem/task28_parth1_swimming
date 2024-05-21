#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>
#include <algorithm>

std::mutex printResult;

void toSwim(std::string inName, int inSpeed, int & inTime)
{
	int distance = 0;	

	while (distance < 100)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		distance += inSpeed;
		++inTime;
		printResult.lock();
		if (distance > 100)
		{
			distance = 100;
		}
		std::cout << "Name: " << inName << " " << "distance: " << distance <<  std::endl;
		printResult.unlock();
	}	
}

void sortResult(int arrTime[], std::string arrName[])
{
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 5 - i; ++j)
		{
			if (arrTime[j] > arrTime[j + 1])
			{
				std::swap(arrTime[j], arrTime[j + 1]);
				std::swap(arrName[j], arrName[j + 1]);
			}
		}
	}
}

void printResultSwimmers(int arrTime[], std::string arrName[])
{
	std::cout << "Swim results: " << std::endl;

	for (int i = 0; i < 6; ++i)
	{
		std::cout << "Swimmer's name: " << arrName[i] << ". Swimmer's result: " << arrTime[i] << " sec." << std::endl;
	}
}
int main()
{
	std::string arrName[6];
	int arrSpeed[6];
	int arrTime[6] = { 0 };	

	for (int i = 0; i < 6; ++i)
	{
		std::cout << "Enter swimmer's name: ";
		//std::cin >> arrName[i];	
		arrName[i] = 'a' + i;
		std::cout << "Enter swimmer speed: ";
		//std::cin >> arrSpeed[i];	
		arrSpeed[i] = 8 + i;
	}

	std::thread swimming0(toSwim, arrName[0], arrSpeed[0], std::ref(arrTime[0]));
	std::thread swimming1(toSwim, arrName[1], arrSpeed[1], std::ref(arrTime[1]));
	std::thread swimming2(toSwim, arrName[2], arrSpeed[2], std::ref(arrTime[2]));
	std::thread swimming3(toSwim, arrName[3], arrSpeed[3], std::ref(arrTime[3]));
	std::thread swimming4(toSwim, arrName[4], arrSpeed[4], std::ref(arrTime[4]));
	std::thread swimming5(toSwim, arrName[5], arrSpeed[5], std::ref(arrTime[5]));

	swimming0.join();
	swimming1.join();
	swimming2.join();
	swimming3.join();
	swimming4.join();
	swimming5.join();		

	sortResult(arrTime, arrName);

	printResultSwimmers(arrTime, arrName);
	
	return 0;
}