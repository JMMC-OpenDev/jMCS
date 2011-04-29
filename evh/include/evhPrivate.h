#ifndef evhPrivate_H
#define evhPrivate_H
/*******************************************************************************
 * JMMC project
 *
 * "@(#) $Id: evhPrivate.h,v 1.3 2005-01-29 15:16:35 gzins Exp $"
 *
 * History
 * -------
 * $Log: not supported by cvs2svn $
 * sccmgr    22-Sep-2004  Created
 *
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
#define MODULE_ID "evh"

/*
 * Maximum number of possible I/O stream descriptors
 */
#define evhMAX_NO_OF_SDS 256

#ifdef __cplusplus
}
#endif


#endif /*!evhPrivate_H*/

/*___oOo___*/