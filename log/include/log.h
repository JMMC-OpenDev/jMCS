#ifndef log_H
#define log_H
/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/

/* The following piece of code alternates the linkage type to C for all
functions declared within the braces, which is necessary to use the
functions in C++-code.
*/
#ifdef __cplusplus
extern "C" {
#endif

/** \file
* Main header file, holding all the public APIs of this module.
*/


/*
* MCS Headers
*/
#include "mcs.h"


/*
 * Logging level constants
 */
typedef enum
{
    logERROR = -1,
    logQUIET,
    logWARNING,
    logINFO,
    logTEST,
    logDEBUG,
    logTRACE
} logLEVEL;

/*
 * Define logging definition structure 
 */
typedef struct {
        mcsSTRING256 logManagerHostName;
        mcsUINT32   logManagerPortNumber;
        mcsLOGICAL  log;
        mcsLOGICAL  verbose;
        logLEVEL    logLevel;
        logLEVEL    verboseLevel;
        logLEVEL    actionLevel;
        mcsLOGICAL  printDate;
        mcsLOGICAL  printFileLine;
        mcsLOGICAL  printThreadName;
} logRULE;

/*
 * Pubic functions declaration
 */

/*
 * File and Stdout logging functions
 */
mcsCOMPL_STAT logSetLogManagerHostName(mcsSTRING256);
mcsCOMPL_STAT logSetLogManagerPortNumber(mcsUINT32);


mcsCOMPL_STAT logEnableFileLog(void);
mcsCOMPL_STAT logDisableFileLog(void);
mcsCOMPL_STAT logSetFileLogLevel(logLEVEL);
logLEVEL      logGetFileLogLevel(void);


mcsCOMPL_STAT logEnableStdoutLog(void);
mcsCOMPL_STAT logDisableStdoutLog(void);
mcsCOMPL_STAT logSetStdoutLogLevel(logLEVEL);
logLEVEL      logGetStdoutLogLevel(void);

mcsCOMPL_STAT logClearStdoutLogAllowedModList(void);
mcsCOMPL_STAT logAddToStdoutLogAllowedModList(char*);


mcsCOMPL_STAT logSetPrintDate(mcsLOGICAL);
mcsLOGICAL    logGetPrintDate(void);
mcsCOMPL_STAT logSetPrintFileLine(mcsLOGICAL);
mcsLOGICAL    logGetPrintFileLine(void);
mcsCOMPL_STAT logSetPrintThreadName(mcsLOGICAL);
mcsLOGICAL    logGetPrintThreadName(void);


mcsCOMPL_STAT logPrint(const mcsMODULEID modName, const logLEVEL level, char* timeStamp, 
                       const char* fileLine, const char* logFormat, ...);

void logGetTimeStamp(mcsSTRING32);


/* Global pointing to the default log library configuration */
extern logRULE* logRulePtr;

/*
 * Convenience macros
 */

/**
 * Check given logLevel; return true if the given logLevel is enabled
 * if (doLog(logLEVEL)) { logPrint(...); }
 */
#define doLog(level) \
    (((logRulePtr->verbose == mcsTRUE) && (level <= logRulePtr->verboseLevel)) \
 || ((logRulePtr->log == mcsTRUE) && (level <= logRulePtr->logLevel)))

/**
 * Log informations about errors (to the least detailed log level).
 *
 * All informations given to this macro are logged on the logERROR level, and
 * all the more detailed levels.
 */
#define logError(format, arg...) \
    if (doLog(logERROR)) { \
        logPrint(MODULE_ID, logERROR, NULL, __FILE_LINE__, format, ##arg); \
    }

/**
 * Log informations about important messages.
 *
 * All informations given to this macro are logged on the logQUIER level, and
 * all the more detailed levels.
 */
#define logQuiet(format, arg...) \
    if (doLog(logQUIET)) { \
        logPrint(MODULE_ID, logQUIET, NULL, __FILE_LINE__, format, ##arg); \
    }

/**
 * Log informations about abnormal events.
 *
 * All informations given to this macro are logged on the logWARNING level, and
 * all the more detailed levels.
 */
#define logWarning(format, arg...) \
    if (doLog(logWARNING)) { \
        logPrint(MODULE_ID, logWARNING, NULL, __FILE_LINE__, format, ##arg); \
    }

/** 
 * Log informations about major events (eg when operational mode is modified).
 *
 * All informations given to this macro are logged on the logINFO level, and
 * all the more detailed levels.
 */
#define logInfo(format, arg...) \
    if (doLog(logINFO)) { \
        logPrint(MODULE_ID, logINFO, NULL, __FILE_LINE__, format, ##arg); \
    }

/** 
 * Log relevant informations used for software test activities.
 *
 * All informations given to this macro are logged on the logTEST level, and
 * all the more detailed levels.
 */
#define logTest(format, arg...) \
    if (doLog(logTEST)) { \
        logPrint(MODULE_ID, logTEST, NULL, __FILE_LINE__, format, ##arg); \
    }

/**
 * Log debugging informations.
 *
 * All informations given to this macro are logged on the logDEBUG level, and
 * all the more detailed levels.
 */
#define logDebug(format, arg...) \
    if (doLog(logDEBUG)) { \
        logPrint(MODULE_ID, logDEBUG, NULL, __FILE_LINE__, format, ##arg); \
    }

/**
 * Log function/method trace.
 *
 * This level is dedicated to add the name of each called function to the
 * logTRACE level log, in order to effectively trace each function call.
 *
 * This macro \em must be the first call (i.e. at the beginning) of each
 * function, in order to log their name.
 *
 * All informations given to this macro are logged on the logTRACE level.
 */
#define logTrace(format, arg...) \
    if (doLog(logTRACE)) { \
        logPrint(MODULE_ID, logTRACE, NULL, __FILE_LINE__, format, ##arg); \
    }

/* OBSSOLETE - Kept for backward-compatibility = TODO : REPLACE BY logTrace macro */
#define logExtDbg logTrace

/* OBSSOLETE - Kept for backward-compatibility = TODO : REPLACE BY logTrace macro */
#define logEXTDBG logTRACE


#ifdef __cplusplus
};
#endif

  
#endif /*!log_H*/


/*___oOo___*/
