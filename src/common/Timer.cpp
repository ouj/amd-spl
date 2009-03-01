#include "Timer.h"
//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		Timer.cpp
//!	\date 		1:3:2009   15:37
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains definition of Timer class.
//!
//////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
namespace amdspl
{
    namespace utils
    {
        //////////////////////////////////////////////////////////////////////////
        //!
        //! \return	Constructor.
        //!
        //! \brief	Destroy the Timer class, and initialize the counter.
        //!
        //////////////////////////////////////////////////////////////////////////
        Timer::Timer() : _clocks(0), _start(0)
        {

#ifdef _WIN32

            QueryPerformanceFrequency((LARGE_INTEGER *)&_freq);
#else
            _freq = 1000;
#endif

        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \return	Destructor
        //!
        //! \brief	Destroy the Timer object and cleans up.
        //!
        //////////////////////////////////////////////////////////////////////////
        Timer::~Timer()
        {
            // EMPTY!
        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief	Start the timer. \sa Stop(), Reset().
        //!
        //////////////////////////////////////////////////////////////////////////
        void
            Timer::Start(void)
        {

#ifdef _WIN32
            QueryPerformanceCounter((LARGE_INTEGER *)&_start);
#else
            struct timeval s;
            gettimeofday(&s, 0);
            _start = (i64)s.tv_sec * 1000 + (i64)s.tv_usec / 1000;

#endif

        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief  Stop the timer. \sa Start(), Reset().
        //!
        //////////////////////////////////////////////////////////////////////////
        void
            Timer::Stop(void)
        {
            i64 n;

#ifdef _WIN32
            QueryPerformanceCounter((LARGE_INTEGER *)&n);
#else
            struct timeval s;
            gettimeofday(&s, 0);
            n = (i64)s.tv_sec * 1000 + (i64)s.tv_usec / 1000;
#endif

            n -= _start;
            _start = 0;
            _clocks += n;
        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief	Reset the timer to 0. \sa Start(), Stop().
        //!
        //////////////////////////////////////////////////////////////////////////
        void
            Timer::Reset(void)
        {
            _clocks = 0;
        }

        //////////////////////////////////////////////////////////////////////////
        //!
        //! \return	double Amount of time that has accumulated between 
        //!         the \a Start() and \a Stop() function calls.
        //!
        //! \brief  Return the time that has elapsed between Start() and Stop calls.	
        //!
        //////////////////////////////////////////////////////////////////////////
        double
            Timer::GetElapsedTime(void)
        {
            return (double)_clocks / (double)_freq;
        }
    }
}

