#ifndef gwtPrivate_H
#define gwtPrivate_H
/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/

/**
 * \file
 * Brief description of the header file, which ends at this dot.
 */

/* The following piece of code alternates the linkage type to C for all 
functions declared within the braces, which is necessary to use the 
functions in C++-code.
*/
#ifdef __cplusplus
extern "C" {
#endif


/*
 * Module name
 */
#define MODULE_ID "gwt"

#define gwtUNINITIALIZED_WIDGET_NAME "notInitedWidget"

#ifdef __cplusplus
}
#endif


#endif /*!gwtPrivate_H*/

/*___oOo___*/
