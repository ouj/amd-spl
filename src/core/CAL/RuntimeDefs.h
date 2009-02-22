#ifndef _AMDSPL_RUNTIMEEFS_H_
#define _AMDSPL_RUNTIMEEFS_H_

#include "CommonDefs.h"
#include <assert.h>
#include "Runtime.h"
#include "Device.h"
#include "DeviceManager.h"
#include "BufferManager.h"
#include "ProgramManager.h"
#include "LocalBuffer.h"
#include "RemoteBuffer.h"
#include "GlobalBuffer.h"

 // A problem that can be handled.
#define CHECK_CAL_RESULT(result, msg) \
    if (result != CAL_RESULT_OK) \
{ \
    return false; \
}

 // A problem that can be handled.
#define CHECK_CAL_RESULT_ERROR(result, msg) \
    if (result != CAL_RESULT_OK) \
{ \
    fprintf(stderr, (msg)); \
    return false; \
}

// A problem that can be handled.
#define LOG_CAL_RESULT_ERROR(result, msg) \
    if (result != CAL_RESULT_OK) \
{ \
    fprintf(stderr, (msg)); \
}

#endif //_AMDSPL_RUNTIMEEFS_H_