#ifndef log_H
#define log_H
/*******************************************************************************
* JMMC project
*
* "@(#) $Id: log.h,v 1.7 2004-06-21 16:51:34 gzins Exp $"
*
* who       when                 what
* --------  -----------  -------------------------------------------------------
* mella     07-May-2004  created
*
*
*******************************************************************************/

/* The following piece of code alternates the linkage type to C for all
functions declared within the braces, which is necessary to use the
functions in C++-code.
*/
#ifdef __cplusplus
extern "C" {
#endif

/** \file
* Main header file.
*/

/*
* MCS Headers
*/
#include "mcs.h"

/* 
 * Macro
 */

#ifndef __FILE_LINE__
#define logIToStr(a) #a
#define logIToStr2(a) logIToStr(a) 
#define __FILE_LINE__ __FILE__ ":" logIToStr2(__LINE__)
#endif /*!__FILE_LINE__*/

/*
 * Logging level constants
 */

typedef enum {
    logERROR,
    logQUIET,
    logWARNING,
    logINFO,
    logTEST,
    logDEBUG,
    logEXTDBG
} logLEVEL;

/*
 * Log/Verbose/Action Logging Functions
 */
mcsCOMPL_STAT logPrint(const mcsMODULEID modName, logLEVEL level,
                       const char *fileLine, 
                       const char *logText, ...);

mcsCOMPL_STAT logPrintAction(logLEVEL level,
                             const char *logText, ...);


mcsCOMPL_STAT logSetLog(mcsLOGICAL flag);

mcsCOMPL_STAT logSetLogLevel(logLEVEL level);

logLEVEL      logGetLogLevel(void);


mcsCOMPL_STAT logSetVerbose(mcsLOGICAL flag);

mcsCOMPL_STAT logSetVerboseLevel(logLEVEL level);

logLEVEL      logGetVerboseLevel(void);


mcsCOMPL_STAT logSetActionLevel(logLEVEL level);

logLEVEL      logGetActionLevel(void);


mcsCOMPL_STAT logSetPrintDate(mcsLOGICAL flag);

mcsCOMPL_STAT logSetPrintFileLine(mcsLOGICAL flag);

mcsCOMPL_STAT logData(const mcsMODULEID modName, 
                      logLEVEL level,
                      const char *timeStamp,
                      const char *fileLine,
                      const char *buffer);
/*
 * Convenience macros
 */

/* Logging and Verbose */

#define logWarning(format, arg...) \
    logPrint(MODULE_ID, logWARNING, __FILE_LINE__, format, ##arg)

#define logInfo(format, arg...) \
    logPrint(MODULE_ID, logINFO, __FILE_LINE__, format, ##arg)

#define logTest(format, arg...) \
    logPrint(MODULE_ID, logTEST, __FILE_LINE__, format, ##arg)

#define logDebug(format, arg...) \
    logPrint(MODULE_ID, logDEBUG, __FILE_LINE__, format, ##arg)

#define logExtDbg(format, arg...) \
    logPrint(MODULE_ID, logEXTDBG, __FILE_LINE__, format, ##arg)

/* Action logs */
    
#define logAction(level, format, arg...) \
    logPrintAction(level, format, ##arg); \
    logPrint(MODULE_ID, level, __FILE_LINE__, format, ##arg)

#define logWarningAction(format, arg...) \
    logPrintAction(logWARNING, format, ##arg); \
    logPrint(MODULE_ID, logWARNING, __FILE_LINE__, format, ##arg)

#define logInfoAction(format, arg...) \
    logPrintAction(logINFO, format, ##arg); \
    logPrint(MODULE_ID, logINFO, __FILE_LINE__, format, ##arg)

#define logTestAction(format, arg...) \
    logPrintAction(logTEST, format, ##arg); \
    logPrint(MODULE_ID, logTEST, __FILE_LINE__, format, ##arg)

#define logDebugAction(format, arg...) \
    logPrintAction(logDEBUG, format, ##arg); \
    logPrint(MODULE_ID, logDEBUG, __FILE_LINE__, format, ##arg)

#define logExtDbgAction(format, arg...) \
    logPrintAction(logEXTDBG, format, ##arg); \
    logPrint(MODULE_ID, logEXTDBG, __FILE_LINE__, format, ##arg)

#ifdef __cplusplus
};
#endif
  
#endif /*!log_H*/
