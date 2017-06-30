#!/bin/bash
#*******************************************************************************
# JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
#*******************************************************************************
#   NAME
#   mkfMakeTclScriptDependencies - create the makefile to buid a Tcl/TK script
# 
#   SYNOPSIS
#
#        mkfMakeTclScriptDependencies <exeName> <objectList> 
# 
#   DESCRIPTION
#   Utility used by mkfMakefile to create the makefile containing the
#   dependencies of a Tcl/Tk script. They are:
#          - each object file (scripts)
#          - the Makefile 
#
#     ../bin/<exeName>: ... <obj-i>.tcl 
#     <TAB>  -mkfMakeTclScript $(WISH) $(<exeName>_TCLSH) 
#                              <exeName> $(<exeName>_OBJECTS) $(<exeName>_LIBS)
#
#   The rules is written to standard output.
#
#   <exeName>     The name of the target. The file is ../bin/<exeName>
#
#   <objectList>  The list of the script files in the src/ directory.
#                 (Without neither directory nor .tcl suffix)
#
#   <tclLibList>  the list of tcl libraries needed to link.
#                 the library directory name is created as
#                 lib<listMember>.tcl
#
#   FILES
#   $MCSROOT/include/mkfMakefile   
#
#   ENVIRONMENT
#
#   RETURN VALUES
#
#   SEE ALSO 
#   mkfMakefile, Makefile, (GNU) make
#
#   BUGS    
#

if [ $# -ne 2 ]
then
    echo "" >&2
    echo "Usage:  mkfMakeTclScriptDependencies <exeName> <object List>" >&2
    echo "" >&2
    exit 1
fi

exeName=$1
objectList=$2

echo "# Dependency file for Tcl Script: ${exeName}"
echo "# Created automatically by mkfMakeTclScriptDependencies -  `date '+%d.%m.%y %T'`"
echo "# DO NOT EDIT THIS FILE"

#
# define the dependency file dependent to the Makefile
echo "../object/${exeName}.dxt: Makefile"
echo ""

#
# define PHONY the target, so make does not try to make the target
# when no object are specified. (due to the fact that the same list of objects is
# used to build the list of exe both to be produced and to be installed).
echo ".PHONY: ${exeName} "

#
# if the list of objects is not empty, the rule to build the exe is written on output.
if [ "${objectList}" != "" ]
then
    #
    # prepare the list of all objects (full filename)
    for member in ${objectList}
    do
        oList="${oList} ${member}.tcl"
    done

    #
    # create a target with the <name> of the executable (make <name>)
    echo "${exeName}: ../bin/${exeName}"
    echo ""

    #
    # output the rule to build the Tcl file 
    echo "../bin/${exeName}: ${oList} Makefile"
    echo "	@echo \"== Making TCL script: \$(@)\" "
    echo "	\$(AT)mkfMakeTclScript \"\$(TCL_CHECKER)\" \"\$(WISH)\" \"\$(${exeName}_TCLSH)\" \"${exeName}\" \"\$(${exeName}_OBJECTS)\" \"\$(${exeName}_LIBS)\" \$(OUTPUT) "

else
    echo "# ${exeName}_OBJECTS is not defined. Nothing to do here."
    echo "# Makefile should define the action for target  '${exeName}:'"
fi

#
# ___oOo___
