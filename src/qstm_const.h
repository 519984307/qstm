#pragma once

#define Q_STM_LOG true
#define Q_STM_LOG_VERBOSE false
#define Q_STM_LOG_SUPER_VERBOSE false

#if Q_STM_LOG_VERBOSE
    #undef Q_STM_LOG
    #define Q_STM_LOG true
#endif

#if Q_STM_LOG_SUPER_VERBOSE
    #undef Q_STM_LOG
    #undef Q_STM_LOG_VERBOSE

    #define Q_STM_LOG true
    #define Q_STM_LOG_VERBOSE true
#endif


#if Q_STM_LOG
    #ifdef QT_DEBUG
        #define Q_STM_LOG_DEBUG true
    #else
        #define Q_STM_LOG_DEBUG false
    #endif

    #ifdef QT_RELEASE
        #define Q_STM_LOG_RELEASE true
    #else
        #define Q_STM_LOG_RELEASE false
    #endif
#else
    #define Q_STM_LOG_DEBUG false
    #define Q_STM_LOG_RELEASE false
#endif
