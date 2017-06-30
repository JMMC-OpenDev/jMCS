#!/bin/bash
#*******************************************************************************
# JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
#*******************************************************************************
#   NAME
#   mkfMakeJavaDependencies - create the makefile to build an executable
# 
#   SYNOPSIS
#
#   mkfMakeJavaDependencies <jarfile> 
# 
#   DESCRIPTION
#   Utility used by mkfMakefile to create the makefile to build a Java 
#   Jarfile, based upon the java compiler and the jar archival tool.
#   It is not intended to be used as a standalone command.
#
#
#   (1) see also GNU Make 3.64, 4.3.5 pag 37
#
#
#   The .djar itself depends to Makefile.
#
#   The rules is written to standard output.
#
#   <jarfile>     The name of the destination jarfile
#                 (Without directory)
#
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

javaName=$1
class=$2

destDir=../bin/

echo "# Dependency file for program: ${javaName}"
echo "# Created automatically by mkfMakeJavaDependencies -  `date '+%d.%m.%y %T'`"
echo "# DO NOT EDIT THIS FILE"
echo "../object/${javaName}.djava: Makefile"
echo ""

if [ "${JAVA}" == "" ]
then
    JAVA=java
fi


# define the dependency file dependent to the Makefile
echo "../bin/${javaName}: Makefile"
echo "	@echo \"== Making ${javaName}\""
echo "	@mkfMakeJavaExecutable ../bin/${javaName} ${class}"

# ___oOo___
