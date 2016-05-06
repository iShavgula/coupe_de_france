#ifndef EXECTIMER_H
#define EXECTIMER_H

#include <cstdlib>
#include <ctime>

class ExecTimer {

        private :
                int current;
                int start;

                ExecTimer& operator= (const ExecTimer&){}
                ExecTimer (const ExecTimer&){}

                static ExecTimer instance;
                ExecTimer();
                ~ExecTimer();

        public :
                static ExecTimer& Instance();

                void reset();
                void resetStart();
                int timePassed();
                int totalTimePassed();
};

/* BRAIN_H_GUARD */
#endif
