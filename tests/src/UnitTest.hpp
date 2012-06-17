#ifndef UNITTEST_HPP_INCLUDED
#define UNITTEST_HPP_INCLUDED

#include <string>
#include <iostream>

// public stuff of this module
#define test_assert(cond) \
	assertTrue("Failed assert: ##cond at line ##__LINE__ in file ##__FILE__", cond)

static void generateReport();

// private stuff of this module
static int _numFailures;
static int _numSuccesses;

static void _addFailure();
static void _addSuccess();

static void assertTrue(const std::string& msg, bool cond)
{
	if (!cond)
	{
		std::cout << msg << std::endl;
		_addFailure();
	}
	else
	{
		_addSuccess();
	}
}

void generateReport()
{
    if (_numSuccesses + _numFailures == 0)
    {
        std::cout << "No tests were performed." << std::endl;
    }
    else
    {
        std::cout << "Passed " << _numSuccesses << "/" << (_numSuccesses+_numFailures) << " (" << (100.0f*_numSuccesses)/(_numFailures+_numSuccesses) << "%) of tests." << std::endl;
    }
}

void _addFailure()
{
	++_numFailures;
}

void _addSuccess()
{
	++_numSuccesses;
}

#endif // UNITTEST_HPP_INCLUDED
