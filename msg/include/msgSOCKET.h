#ifndef msgSOCKET_H
#define msgSOCKET_H
/*******************************************************************************
 * JMMC project
 *
 * "@(#) $Id: msgSOCKET.h,v 1.15 2005-09-12 13:01:24 scetre Exp $"
 *
 * History
 * -------
 * $Log: not supported by cvs2svn $
 * Revision 1.14  2005/02/14 07:59:01  gzins
 * Minor documentation changes
 *
 * Revision 1.13  2005/02/04 15:57:06  lafrasse
 * Massive documentation review an refinment (also added automatic CVS log inclusion in every files)
 *
 * Revision 1.12  2005/01/24 15:39:54  gzins
 * Added CVS logs as modification history
 *
 * gzins     22-Dec-2004  Replaced msgMESSAGE.h file inclusion by msgMESSAGE
 *                        class declaration
 * gzins     06-Dec-2004  Declared copy constructor as private method
 * gzins     06-Dec-2004  Declared copy constructor as public method
 * lafrasse  03-Dec-2004  Changed port number type from mcsINT32 to mcsUINT16
 * lafrasse  23-Nov-2004  Comment refinments, and includes cleaning
 * scetre    19-Nov-2004  Created
 *
 ******************************************************************************/

/**
 * \file
 * Declaration of msgSOCKET class 
 */

#ifndef __cplusplus
#error This is a C++ include file and cannot be used from plain C
#endif

/*
 * System Headers 
 */
#include <string>
#include <arpa/inet.h>

/*
 * MCS Headers 
 */
#include "mcs.h"

/*
 * Local Headers 
 */
class msgMESSAGE;


/*
 * Constant declaration
 */

const int MAXCONNECTIONS = 5;
const int MAXRECV        = 500;


/*
 * Class declaration
 */

/**
 * Class wrapping IPv4 BSD socket.
 * 
 * Provides methods to :
 * \li create a socket;
 * \li send data through a socket;
 * \li received data through a socket;
 * \li close a socket.
 */
class msgSOCKET
{

public:
    // Brief description of the constructor
    msgSOCKET();

    // Brief description of the destructor
    virtual ~msgSOCKET();

    // Common initialisation
    virtual mcsCOMPL_STAT Create       (void);

    // Accessors
    virtual mcsINT32      GetDescriptor(void);
    virtual mcsLOGICAL    IsConnected  (void);

    // Server initialisation
    virtual mcsCOMPL_STAT Bind         (const mcsUINT16 port);
    virtual mcsCOMPL_STAT Listen       (void);
    virtual mcsCOMPL_STAT Accept       (msgSOCKET &socket) const;

    // Client initialization
    virtual mcsCOMPL_STAT Connect      (const std::string host,
                                        const mcsUINT16   port);

    // String-related Transmission
    virtual mcsCOMPL_STAT Send         (const std::string  string) const;
    virtual mcsCOMPL_STAT Receive      (      std::string& string) const;
    virtual mcsCOMPL_STAT Receive      (std::string& string,
                                        mcsINT32 timeoutInMs);

    // msgMESSAGE-related Transmission
    virtual mcsCOMPL_STAT Send         (msgMESSAGE &msg);
    virtual mcsCOMPL_STAT Receive      (msgMESSAGE &msg, mcsINT32 timeoutInMs);

    virtual mcsCOMPL_STAT Close        (void);

protected:
    
private:
    // Declaration of copy const and assignment operator as private methods,
    // in order to it them from the users.
    msgSOCKET(const msgSOCKET &socket);
    msgSOCKET& operator=(const msgSOCKET&);

    mcsINT32    _descriptor;  // Socket Descriptor
    sockaddr_in _address;     // Socket Data Structure
};

#endif /*!msgSOCKET_H*/

/*___oOo___*/
