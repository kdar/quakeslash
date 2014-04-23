#include "event.h"

#include <iostream>
#include <string>

#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>
#include <boost/bind.hpp>

#include "sigc++/sigc++.h"
#include <Windows.h>

int sum = 0;

class EventHandler : public events::AutoTracked
{
public:
	void AddToSum(int n) { sum += n; }

	events::ConnectionSet connectionSet;
};

class SignalHandler/* : public boost::signals::trackable*/
{
public:
	void AddToSum(int n) { sum += n; }
};

class SigCHandler : public sigc::trackable
{
public:
	void AddToSum(int n) { sum += n; }
};

static const int NUM_TRIALS = 10000000;
static const int NUM_HANDLERS = 10;

void AddToSum(int n)
{
	sum += n;
}

int main()
{

	{
		DWORD startTime = timeGetTime();
		std::cout << "Computing using Events...";
		events::Event<int> e;

		std::vector<EventHandler> handlers(NUM_HANDLERS);
		for(std::vector<EventHandler>::iterator ih = handlers.begin(), eh = handlers.end(); ih != eh; ++ih)
		{
//			ih->connectionSet.Add(e.Register(*ih, &Handler::AddToSum));
			e.AutoRegister(*ih, &EventHandler::AddToSum);
		}

		for(int i=0; i<NUM_TRIALS; i++)
		{
			e.Invoke(i);
		}
		DWORD endTime = timeGetTime();

		std::cout << sum << ". Computation time: " << endTime - startTime << "ms." << std::endl;
	}

	
	sum = 0;

	{
		std::cout << "Computing using Boost Signals...";

		DWORD startTime = timeGetTime();
		boost::signal<void(int)> s;
		std::vector<SignalHandler> handlers(NUM_HANDLERS);
		for(std::vector<SignalHandler>::iterator ih = handlers.begin(), eh = handlers.end(); ih != eh; ++ih)
		{
			s.connect(boost::bind(&SignalHandler::AddToSum, &*ih, _1));
		}

		for(int i=0; i<NUM_TRIALS; i++)
		{
			s(i);
		}

		DWORD endTime = timeGetTime();

		std::cout << sum << ". Computation time: " << endTime - startTime << "ms." << std::endl;
	}

	sum = 0;

	{
		std::cout << "Computing using SigC++...";

		DWORD startTime = timeGetTime();
		sigc::signal<void, int> s;
		std::vector<SigCHandler> handlers(NUM_HANDLERS);
		for(std::vector<SigCHandler>::iterator ih = handlers.begin(), eh = handlers.end(); ih != eh; ++ih)
		{
			s.connect(sigc::ptr_fun(&AddToSum));
		}

		for(int i=0; i<NUM_TRIALS; i++)
		{
			s.emit(i);
		}

		DWORD endTime = timeGetTime();

		std::cout << sum << ". Computation time: " << endTime - startTime << "ms." << std::endl;
	}
}
