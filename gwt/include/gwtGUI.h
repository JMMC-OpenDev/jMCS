#ifndef gwtGUI_H
#define gwtGUI_H
/*******************************************************************************
 * JMMC project
 *
 * "@(#) $Id: gwtGUI.h,v 1.3 2005-02-15 12:17:52 gzins Exp $"
 *
 * History
 * -------
 * $Log: not supported by cvs2svn $
 * mella     14-Sep-2004  Created
 *
 ******************************************************************************/

/**
 * \file
 * gwtGUI class declaration file.
 */


#ifndef __cplusplus
#error This is a C++ include file and cannot be used from plain C
#endif

//class gwtWIDGET;
//class gwtWINDOW;

#include "gwtWIDGET.h"
#include "gwtWINDOW.h"
#include "msgSOCKET_CLIENT.h"

/*
 * Class declaration
 */

/** 
 * Main Graphical User Interface class.
 * The gwtGUI is the central point of any GUI that uses the gui module.
 * This class handles local widgets and communication with the remote displayer.
 * It is linked to the remote displayer using a socket connection. This
 * connection is used by the event handler.
 */
class gwtGUI
{
public:
    gwtGUI();
    virtual ~gwtGUI();
    virtual mcsCOMPL_STAT ConnectToRemoteGui(const string hostname, const int port, const string procname);
    virtual void SetStatus(bool valid, string message);
    virtual void Send(string xmlStr);
    virtual int GetSd();
    virtual void RegisterXmlProducer(gwtXML_PRODUCER *producer);
    virtual void ReceiveData(string data);
    /** 
     * typedef for map of windows
     */
    typedef map<string, gwtXML_PRODUCER *> gwtMAP_STRING2PRODUCER;
protected:
    gwtMAP_STRING2PRODUCER _children; 
private:
    msgSOCKET_CLIENT *_clientSocket;
    virtual void DispatchGuiReturn(string widgetid, string data);
};

#endif /*!gwtGUI_H*/

/*___oOo___*/
