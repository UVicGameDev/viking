#ifndef UNITTEST_HPP_INCLUDED
#define UNITTEST_HPP_INCLUDED

#include <string>
#include <iostream>

// public stuff of this module
#define TESTASSERT(cond) \
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
	std::cout << "Passed " << _numSuccesses << "/" << (_numSuccesses+_numFailures) << " (" << static_cast<float>(100*_numSuccesses)/(_numFailures+_numSuccesses) << "%) of tests." << std::endl;
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
