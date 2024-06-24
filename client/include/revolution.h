#include <stdint.h>

#pragma once

#ifdef SEMICOLON
    #define SHOW_ERROR(s) perror(s) SEMICOLON
    #define RETURN_84 return (84) SEMICOLON
#else
    #define SHOW_ERROR(s)
    #define RETURN_84
#endif

#define BRKT_O {

// No operation macro
#define NOOP (void)0

// Error handling macro
#ifdef BRACKET_C
    #define CHECK_BODY(s) SHOW_ERROR(s) RETURN_84
    #define CHECK(v, s) if (v == -1) BRKT_O CHECK_BODY(s) BRACKET_C NOOP
#else
    #define CHECK(v, s)
#endif

// Variable declaration macros
#define NEW(type, name) type name
#define OTH_VAR(name, val) , name = val
