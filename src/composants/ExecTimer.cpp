#include "ExecTimer.h"

using namespace std;

ExecTimer ExecTimer::instance=ExecTimer();

ExecTimer::ExecTimer()
{
        current = (double)clock();
        start = (double)clock();
        reset();
}

ExecTimer::~ExecTimer()
{
}

ExecTimer& ExecTimer::Instance()
{
    return instance;
}

void ExecTimer::reset() {
        current = (double)clock();
}

void ExecTimer::resetStart() {
        start = (double)clock();
}

int ExecTimer::timePassed() {
        return (double)(clock() - current)/CLOCKS_PER_SEC;
}

int ExecTimer::totalTimePassed() {
        return (double)(clock() - start)/CLOCKS_PER_SEC;
}