#define _POSIX_SOURCE
#include <cstring>
#include <iostream>
#include <valarray>
#include <string>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <thread>
#include <sstream>
#include <syscall.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void threadFunc()
{
	wcout << "My name is Steve and I'm a threadFunc!" << endl;
}

void calculateSum()
{
	wcout << "Time for sum calculations!" << endl;

	//Calculate the sum
	unsigned long sum = 0;
	float i = 1;
	float j = 1;
	int n = 50000;

	for(i = 1 ; i <= n ; i++)
	{
		for(j = 1 ; j <= i ; j++)
		{
			sum += sqrt(i * j);
		}
	}

	wcout << sum << " is the sum of the equation!" << endl;
}

int main(int argc, char const *argv[])
{
	string argInput;
	string optInput;

	if(argc > 2)
	{
		argInput = argv[1];
		optInput = argv[2];
	}

	else
	{
		argInput = argv[1];
		optInput = "0";
	}

	if(argInput == "-i")
	{
		char hostName[HOST_NAME_MAX];
		wcout << "Number of processors: " << get_nprocs() << endl;
		gethostname(hostName, _SC_HOST_NAME_MAX);
		wcout << "Host Name: " << hostName << endl;
		struct utsname unameData;
		uname(&unameData);
		wcout << "Hardware Platform: " << unameData.machine << endl;
		wcout << "Total amount of memory: " << sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE) / 1024 / 1024 << " MB" << endl;
	}

	else if(argInput == "-f")
	{
		if(stoi(optInput) > 0)
		{
			uint64_t pidArray[stoi(optInput)];

			for(int i = 0 ; i < stoi(optInput) ; i++)
			{
				pid_t pid = fork();
				int status;

				if(pid < 0){wcout << "Fork failed... </3" << endl;}

				//Child process
				else if(pid == 0)
				{
					wcout << "This is the child! " << endl;
					wcout << "Child PID is " << (uint64_t) getpid() << " and the parent PID is " << (uint64_t) getppid() << endl;

					pidArray[i] = (uint64_t) getpid();

					exit(535);
				}

				//Father process
				else
				{
					wcout << "This is the parent! " << endl;
					wcout << "Parent PID is " << (uint64_t) getpid() << " and the child PID is " << (uint64_t) pid << endl;
					wcout << "I'm waiting for my child to complete" << endl;

					if(wait(&status) == -1){ wcout << "ERROR :c" << endl; }

					else if(WIFEXITED(status)){ wcout << "The child exited with the status of " << WEXITSTATUS(status) << endl; }

					else{ wcout << "The child did not exit successfully" << endl;}
				}
			}

			calculateSum();
		}

		else{ wcout << "You must assign a value higher than 0" << endl;}
	}

	else if(argInput == "-t")
	{
		if(stoi(optInput) > 0)
		{
			uint64_t idArray[stoi(optInput)];

			for(int i = 0 ; i < stoi(optInput) ; i++)
			{
				thread tfi(threadFunc);
				sleep(1);
				wcout << "My ID is: " << tfi.get_id() << endl;
				wcout << "My Hardware Concurrency is: " << tfi.hardware_concurrency() << endl;

				stringstream ss;
				ss << this_thread::get_id();
				uint64_t id = stoull(ss.str());

				idArray[i] = id;

				if(tfi.joinable()){tfi.join();}
			}

			calculateSum();
		}

		else{ wcout << "You must assign a value higher than 0" << endl;}
	}

	else if(argInput == "-help")
	{
		wcout << "*** HELP ***" << endl;
		wcout << "COMMAND : INFO : OPTIONS" << endl;
		wcout << "-i     : Hardware info     : No avalible options" << endl;
		wcout << "-f     : Fork X amount of processes, get their PID and calculate a sum     : X, the amount of processes" << endl;
		wcout << "-t     : Similar to -f but with threads     : X, an integer" << endl;
	}
}