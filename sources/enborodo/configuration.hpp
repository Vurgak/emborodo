#pragma once

#ifdef EN_SHARED
    #ifdef _WIN32
        #ifdef EN_EXPORTS
            #define EN_API __declspec(dllexport)
        #else
            #define EN_API __declspec(dllimport)
        #endif
    #else
        #define EN_API __attribute__((visibility("default")))
    #endif
#else
    #define EN_API
#endif
