#ifndef _AMDSPL_COMMONDEFS_H_
#define _AMDSPL_COMMONDEFS_H_

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#define SAFE_DELETE(ptr) \
    if ((ptr) != NULL) \
{ \
    delete ptr; \
    ptr = NULL; \
}

#define LOG_ERROR(msg) \
{ \
    fprintf(stderr, (msg)); \
}

#define LOG_TRACE(msg) \
{\
    fprintf(stdout, (msg)); \
}

// Something that can be handled
#define CHECK_CONDITION(condition, msg) \
if (!(condition)) \
{ \
    fprintf(stderr, (msg)); \
    return false; \
}

// An error
#define SET_ERROR(msg) \

#endif //_COMMONDEFS_H_