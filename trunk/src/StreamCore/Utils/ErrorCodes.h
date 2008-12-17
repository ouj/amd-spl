#ifndef _AMDSPL_ERRORCODES_H_
#define _AMDSPL_ERRORCODES_H_

namespace amdspl
{
    ////////////////////////////////////////////////////////////////////////////////
    //!
    //! \enum Represnt all the error codes visible to brook developer.
    //!
    ////////////////////////////////////////////////////////////////////////////////
    enum BRerror
    {
        BR_NO_ERROR = 0,                        // No error
        BR_ERROR_DECLARATION,                   // Error with stream declaration
        BR_ERROR_READ,                          // Error in read method 
        BR_ERROR_WRITE,                         // Error in Write method
        BR_ERROR_KERNEL,                        // Error in Kernel invocation
        BR_ERROR_DOMAIN,                        // Error in domain operator
        BR_ERROR_INVALID_PARAMATER,             // An invalid parameter passed
        BR_ERROR_NOT_SUPPORTED,                 // Feature not supported in brook+ or in the underlying hardware
        BR_ERROR_FORCE_DWORD    = 0x7fffffff,   // force 32-bit size enum
    };
}

#endif //_ERRORCODES_H_
