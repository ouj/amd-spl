#ifndef _TIMER_H_
#define _TIMER_H_
//////////////////////////////////////////////////////////////////////////
//!
//!	\file 		Timer.h
//!	\date 		1:3:2009   15:37
//!	\author		Jiawei Ou
//!	
//!	\brief		Contains declaration of Timer class.
//!
//////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
//! \brief	    Maps the windows 64 bit integer to a uniform name
typedef __int64 i64 ;
#else
//! \brief	    Maps the linux 64 bit integer to a uniform name
typedef long long i64;
#endif

namespace amdspl
{
    namespace utils
    {
        //////////////////////////////////////////////////////////////////////////
        //!
        //! \brief	Timer that provides a fairly accurate timing mechanism for 
        //!         both windows and linux. 
        //!
        //! \warning Not thread safe. 
        //!
        //////////////////////////////////////////////////////////////////////////
        class Timer {
        public:
            Timer();
            ~Timer();
            void Start(void);
            void Stop(void);
            void Reset(void);
            double GetElapsedTime(void);
        private:
            //! \brief	Stores the CPU frequency.
            i64 _freq;
            //! \brief	Stores the time has elapsed.
            i64 _clocks;
            //! \brief	Stores the starting time.
            i64 _start;
        };
    }
}

#endif // _TIMER_H_

