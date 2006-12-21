#ifndef sdbENTRY_H
#define sdbENTRY_H
/*******************************************************************************
 * JMMC project
 *
 * "@(#) $Id: sdbSYNC_ENTRY.h,v 1.4 2006-12-21 15:03:08 lafrasse Exp $"
 *
 * History
 * -------
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2006/02/22 17:05:43  lafrasse
 * Added security check to disable semaphores use in case of  bad initialization
 *
 * Revision 1.2  2005/12/22 14:10:35  lafrasse
 * Added a way to release all the created semaphores used by sdbENTRY
 *
 * Revision 1.1  2005/12/20 13:52:34  lafrasse
 * Added preliminary support for INTRA-process action log
 *
 ******************************************************************************/

/**
 * @file
 * Declaration of sdbENTRY class.
 */

#ifndef __cplusplus
#error This is a C++ include file and cannot be used from plain C
#endif


/*
 * MCS header
 */
#include "mcs.h"
#include "thrd.h"


/*
 * Class declaration
 */

/**
 * !!! NOT YET DOCUMENTED cause THIS IMPLEMENTATION IS TEMPORARY !!!
 * 
 * Brief description of the class, which ends at this dot.
 * 
 * OPTIONAL detailed description of the class follows here.
 *
 * @usedfiles
 * OPTIONAL. If files are used, for each one, name, and usage description.
 * @filename fileName1 :  usage description of fileName1
 * @filename fileName2 :  usage description of fileName2
 *
 * @env
 * OPTIONAL. If needed, environmental variables accessed by the class. For
 * each variable, name, and usage description, as below.
 * @envvar envVar1 :  usage description of envVar1
 * @envvar envVar2 :  usage description of envVar2
 * 
 * @warning OPTIONAL. Warning if any (software requirements, ...)
 *
 * @ex
 * OPTIONAL. Code example if needed
 * \n Brief example description.
 * @code
 * Insert your code example here
 * @endcode
 *
 * @sa OPTIONAL. See also section, in which you can refer other documented
 * entities. Doxygen will create the link automatically.
 * @sa modcppMain.C
 * 
 * @bug OPTIONAL. Bugs list if it exists.
 * @bug For example, description of the first bug
 * @bug For example, description of the second bug
 * 
 * @todo OPTIONAL. Things to forsee list, if needed. For example, 
 * @todo add other methods, dealing with operations.
 * 
 */
class sdbENTRY
{
public:
    // Class constructor
    sdbENTRY();

    // Class destructor
    virtual ~sdbENTRY();

    mcsCOMPL_STAT  Init    (void);
    mcsCOMPL_STAT  Destroy (void);
    mcsCOMPL_STAT  Write   (const char*       message,
                            const mcsLOGICAL  lastMessage);
    mcsCOMPL_STAT  Wait    (      char*       message,
                                  mcsLOGICAL* lastMessage);

protected:
    
private:
    // Declaration of copy constructor and assignment operator as private
    // methods, in order to hide them from the users.
    sdbENTRY(const sdbENTRY&);
    sdbENTRY& operator=(const sdbENTRY&);

    thrdSEMAPHORE  _emptyBufferSemaphore;
    thrdSEMAPHORE  _fullBufferSemaphore;

    mcsSTRING256   _buffer;

    mcsLOGICAL     _initSucceed;
    mcsLOGICAL     _lastMessage;
};

#endif /*!sdbENTRY_H*/

/*___oOo___*/
