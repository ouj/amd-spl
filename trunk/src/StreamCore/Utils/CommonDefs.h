#ifndef _AMDSPL_COMMONDEFS_H_
#define _AMDSPL_COMMONDEFS_H_

// MACROS
#define MaxRank 4

// Something that can be handled
#define CHECK_CONDITION(condition, msg) \
if (!(condition)) \
{ \
    return false; \
}

#define SAFE_DELETE(ptr) \
if ((ptr) != NULL) \
{ \
    delete ptr; \
    ptr = NULL; \
}

// An error
#define SET_ERROR(msg) \

#endif //_COMMONDEFS_H_
