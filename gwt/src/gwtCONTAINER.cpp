/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/

/**
 * \file
 * Definition of gwtCONTAINER class.
 * 
 */


/* 
 * System Headers 
 */
#include <iostream>
#include <sstream>
using namespace std;


/*
 * MCS Headers 
 */
#include "mcs.h"
#include "log.h"
#include "err.h"


/*
 * Local Headers 
 */
#include "gwtCONTAINER.h"
#include "gwt.h"
#include "gwtPrivate.h"

/*
 * Class constructor
 */

/** 
 * Constructs a new gwtCONTAINER
 */
gwtCONTAINER::gwtCONTAINER ()
{
  logExtDbg ("gwtCONTAINER::gwtCONTAINER()");
}


/*
 * Class destructor
 */



/*
 * Public methods
 */

string gwtCONTAINER::GetXmlBlock()
{
    logExtDbg("gwtCONTAINER::GetXmlBlock()");
    string s;
    // append children content
    gwtMAP_STRING2WIDGET::iterator i = _children.begin();
    while(i != _children.end())
    {
        gwtWIDGET * tmpWidget = i->second;
        string mystring = tmpWidget->GetXmlBlock();
        if ( ! mystring.empty() )
        {
            s.append(mystring);
        }
        i++;
    }
    return s;
}


/** 
 *  Return a widgetId for the given widget.
 *
 * \param widget the widget that request a widgetId. 
 *
 *  \returns the widgetId.
 */
string gwtCONTAINER::GetNewWidgetId(gwtWIDGET *widget)
{
    /* give an id to the wigdet */
  string wid;
  ostringstream osstring;
  // append ancestor at the end of the widget id to make it different in every
  // conatiners
  osstring << "widget_" <<_children.size()<<"@"<<this;
  wid = osstring.str();
  return wid;
}

/**
 * Add the given widget into the container. The widget will get a widget id
 * to make retrieval possible and identification. Containers can also contain
 * containers using this method. 
 *
 * \param widget  The widget to add to the container
 *
 * \return mcsSUCCESS or mcsFAILURE in case of error.
 */
mcsCOMPL_STAT gwtCONTAINER::Add (gwtWIDGET * widget)
{
  logExtDbg ("gwtCONTAINER::Add()");

  string wid(widget->GetWidgetId());
  // check if widget was previously added in one container
  if ( wid.compare(gwtUNINITIALIZED_WIDGET_NAME) == 0)
  {
    wid=GetNewWidgetId(widget);
    widget->SetWidgetId(wid);
  }
  else
  {
    logDebug("not inited widget added was %s",widget->GetXmlBlock().data());
    errAdd(gwtERR_WIDGET_ALREADY_ADDED);
    return mcsFAILURE;
  }
  logDebug ("add new widget referenced by: %s",wid.data());
  
  _children.insert ( make_pair(wid,widget));

  // If the widget is a container, add it to the container list
  if ( widget->IsContainer() == mcsTRUE )
  {
      logDebug ("add new container referenced by: %s", wid.data());
      _containers.insert ( make_pair(wid,(gwtCONTAINER *)widget));
  }

  return mcsSUCCESS;
}

/**
 * Add the given container into the container map. This method must be used
 * instead of Add one for every containers to make retrieval possible and identi
fication.
 *
 * \param container The container to add to the list of containers.
 *
 * \return mcsSUCCESS or mcsFAILURE in case of error.
 * \warning Deprecated: Add method must be used to handle simple or container
 * widgets.
 */
mcsCOMPL_STAT gwtCONTAINER::AddContainer(gwtCONTAINER * container)
{
  logWarning ("gwtCONTAINER::AddContainer() used instead of Add()");
  return Add(container);
}


/**
 * Dispach the Gui return to the widgets. 
 * 
 * \param widgetid  Widget id to transmit.
 * \param data  Associated data to transmit.
 *
 */
void gwtCONTAINER::DispatchGuiReturn(string widgetid, string data)
{
    logExtDbg ("gwtCONTAINER::DispatchGuiReturn()");

    gwtMAP_STRING2WIDGET::iterator iter = _children.find(widgetid);
    if( iter != _children.end() ) 
    {
        // change
        logDebug(" widget [%s] will be updated ", widgetid.data());
        (iter->second)->Changed(data);
    }
    else
    {
        logDebug(" widget [%s] not found at this level", widgetid.data());
        gwtMAP_STRING2CONTAINER::iterator jter = _containers.begin();
        while (jter != _containers.end())
        {
            (jter->second)->DispatchGuiReturn(widgetid, data);
            jter++;
        }
    }
}


mcsLOGICAL gwtCONTAINER::IsContainer()
{
   return mcsTRUE;
}

/*
 * Protected methods
 */




/*
 * Private methods
 */



/*___oOo___*/