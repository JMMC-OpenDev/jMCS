<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="text" omit-xml-declaration="yes" indent="no"/>

<!--
    ********************************************************************************
    JMMC project

    "@(#) $Id: cmdCdfToCppCB.xsl,v 1.1 2005-05-31 14:56:53 mella Exp $"

    History
    ~~~~~~~
    $Log: not supported by cvs2svn $
    ********************************************************************************
-->
    
    <xsl:param name="moduleName"/>
    <xsl:param name="cdfFilename"/>
    
    <xsl:variable name="autoGeneratedC"><xsl:text>/*
 * 
 * This file has been automatically generated
 * 
 * !!!!!!!!!!!  DO NOT MANUALLY EDIT THIS FILE  !!!!!!!!!!!
 */

 </xsl:text>
</xsl:variable>

    <!-- ********************************************************* -->
    <!-- This TEMPLATE is the main part                            -->
    <!-- it calls one main template for each cmd nodes             -->
    <!-- INPUT : the module name                                   -->
    <!-- OUTPUT: the generated files  usind <mod><MNEMO>CB.C       -->
    <!-- ********************************************************* -->
    <xsl:template match="/">
 
        <xsl:for-each select="/cmd">
            <xsl:variable name="properModuleName"><xsl:call-template name="convertcase">
                    <xsl:with-param name="toconvert" select="$moduleName"/>
                    <xsl:with-param name="conversion">proper</xsl:with-param>
            </xsl:call-template></xsl:variable>    
            <xsl:variable name="properMnemonic"><xsl:call-template name="convertcase">
                    <xsl:with-param name="toconvert" select="./mnemonic"/>
                    <xsl:with-param name="conversion">proper</xsl:with-param>
            </xsl:call-template></xsl:variable>   
            <xsl:variable name="CBName" select="concat($properModuleName,$properMnemonic,'CB')"/>
            <xsl:document href="{concat($CBName,'.cpp')}" method="text">
            <xsl:value-of select="$autoGeneratedC"/>
            <xsl:call-template name="cmdCppCB">
                <xsl:with-param name="CBName" select="$CBName"/>
            </xsl:call-template>
            </xsl:document> 
        </xsl:for-each>
    </xsl:template>
        
    <!-- ********************************************************* -->
    <!-- This TEMPLATE is the main part to generate the c++ header -->
    <!-- file from a given command node.                           -->
    <!-- ********************************************************* -->
    <xsl:template name="cmdCppCB">
/**
 * \file
 * Generated for <xsl:value-of select="$CBName"/> callback definition.
 */
 
 
/*
 * System Headers
 */
#include &lt;iostream&gt;
using namespace std;

/*
 * MCS Headers
 */
#include "mcs.h"
#include "log.h"

/*
 * Local Headers
 */
#include "<xsl:value-of select="$moduleName"/>.h"
#include "<xsl:value-of select="$moduleName"/>Private.h"

/*
 * Public methods
 */
 
/*
 * Callback for <xsl:value-of select="$CBName"/> command.
 *
 * \return an evhCB completion status code (evhCB_SUCCESS or evhCB_FAILURE)
 */
 evhCB_COMPL_STAT replaceByClassName::<xsl:value-of select="$CBName"/>(msgMESSAGE &amp;msg, void *)
 {
    logExtDbg("replaceByClassName::<xsl:value-of select="$CBName"/>()");
    
    //  <xsl:value-of select="./mnemonic"/> command
    <xsl:value-of select="$moduleName"/><xsl:value-of select="./mnemonic"/>_CMD <xsl:value-of select="$moduleName"/><xsl:call-template name="convertcase">
                    <xsl:with-param name="toconvert" select="./mnemonic"/>
                    <xsl:with-param name="conversion">proper</xsl:with-param>
            </xsl:call-template>Cmd(msg.GetCommand(), msg.GetBody());

    // Parse command
    if (<xsl:value-of select="$moduleName"/><xsl:call-template name="convertcase">
                    <xsl:with-param name="toconvert" select="./mnemonic"/>
                    <xsl:with-param name="conversion">proper</xsl:with-param>
            </xsl:call-template>Cmd.Parse() == mcsFAILURE)
    {
        return evhCB_NO_DELETE | evhCB_FAILURE;
    }

    return evhCB_SUCCESS;
 }

/*___oOo___*/
</xsl:template>

  <xsl:variable name="lcletters">abcdefghijklmnopqrstuvwxyz</xsl:variable>

  <xsl:variable name="ucletters">ABCDEFGHIJKLMNOPQRSTUVWXYZ</xsl:variable>

  <xsl:template name='convertcase'>
    <xsl:param name='toconvert' />

    <xsl:param name='conversion' />

    <xsl:choose>
      <xsl:when test='$conversion="lower"'>
        <xsl:value-of
        select="translate($toconvert,$ucletters,$lcletters)" />
      </xsl:when>

      <xsl:when test='$conversion="upper"'>
        <xsl:value-of
        select="translate($toconvert,$lcletters,$ucletters)" />
      </xsl:when>

      <xsl:when test='$conversion="proper"'>
        <xsl:call-template name='convertpropercase'>
          <xsl:with-param name='toconvert'>
            <xsl:value-of
            select="translate($toconvert,$ucletters,$lcletters)" />
          </xsl:with-param>
        </xsl:call-template>
      </xsl:when>
      
      <xsl:when test='$conversion="upfirst"'>
        <xsl:call-template name='convertpropercase'>
          <xsl:with-param name='toconvert'>
            <xsl:value-of
                select="$toconvert" />
          </xsl:with-param>
        </xsl:call-template>
      </xsl:when>

      <xsl:otherwise>
        <xsl:value-of select='$toconvert' />
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template name='convertpropercase'>
    <xsl:param name='toconvert' />

    <xsl:if test="string-length($toconvert) > 0">
      <xsl:variable name='f'
      select='substring($toconvert, 1, 1)' />

      <xsl:variable name='s' select='substring($toconvert, 2)' />

      <xsl:call-template name='convertcase'>
        <xsl:with-param name='toconvert' select='$f' />

        <xsl:with-param name='conversion'>upper</xsl:with-param>
      </xsl:call-template>

      <xsl:choose>
        <xsl:when test="contains($s,' ')">
        <xsl:value-of select='substring-before($s," ")' />

          
        <xsl:call-template name='convertpropercase'>
          <xsl:with-param name='toconvert'
          select='substring-after($s," ")' />
        </xsl:call-template>
        </xsl:when>

        <xsl:otherwise>
          <xsl:value-of select='$s' />
        </xsl:otherwise>
      </xsl:choose>
    </xsl:if>
  </xsl:template>

</xsl:stylesheet>
