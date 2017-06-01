/*******************************************************************************
 * JMMC project ( http://www.jmmc.fr ) - Copyright (C) CNRS.
 ******************************************************************************/

/* 
 * System Headers 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * MCS Headers 
 */
#include "mcs.h"
#include "err.h"
#include "log.h"


/*
 * Local Headers 
 */
#include "miscDynBuf.h"


/*
 * Local Functions 
 */
void displayCmdStatus(mcsINT8);
void displayExecStatus(mcsCOMPL_STAT);
void displayDynBuf(miscDYN_BUF*);


/* 
 * Main
 */

#define SUCCEED "SUCCEED"
#define FAILED "FAILED"

int main (int argc, char *argv[])
{
    /* Configure logging service */
    logSetStdoutLogLevel(logTEST);
    logSetPrintDate(mcsFALSE);
    logSetPrintFileLine(mcsFALSE);

    /* Give process name to mcs library */
    mcsInit(argv[0]);

    mcsCOMPL_STAT  executionStatusCode;
    mcsINT8        cmdStatusCode;

    miscDYN_BUF    dynBuf;

    char           *bytes       = NULL;
    int            bytesNumber  = 0;

    char           byte         = '\0';

    miscDynSIZE    storedBytes  = 0;
    miscDynSIZE    position     = 0;
    miscDynSIZE    from         = 0;
    miscDynSIZE    to           = 0;



    /* miscDynBufInit */
    printf("---------------------------------------------------------------\n");
    printf("&dynBuf = NULL :\n");
    printf("----------------\n");
    displayDynBuf(NULL);
    errCloseStack();
    printf("\n");

    printf("dynBuf Allocated :\n");
    printf("------------------\n");
    miscDynBufInit(&dynBuf);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");



    /* miscDynBufAppendBytes */
    printf("---------------------------------------------------------------\n");
    printf("&dynBuf = NULL :\n");
    printf("----------------\n");
    printf("miscDynBufAppendBytes(&dynBuf = NULL) : ");
    executionStatusCode = miscDynBufAppendBytes(NULL, bytes, bytesNumber);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    printf("dynBuf Allocated :\n");
    printf("------------------\n");
    printf("miscDynBufAppendBytes(NULL, 0) ");
    executionStatusCode = miscDynBufAppendBytes(&dynBuf, bytes, bytesNumber);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    bytes = "hello dynBuf" ;
    bytesNumber = strlen(bytes);
    printf("miscDynBufAppendBytes(\"%s\", %d) ", bytes, bytesNumber);
    executionStatusCode = miscDynBufAppendBytes(&dynBuf, bytes, bytesNumber);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    displayDynBuf(&dynBuf);
    printf("\n");

    bytes    = " ... :)" ;
    bytesNumber = strlen(bytes);
    printf("miscDynBufAppendBytes(\"%s\", %d) ", bytes, bytesNumber);
    executionStatusCode = miscDynBufAppendBytes(&dynBuf, bytes, bytesNumber);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    displayDynBuf(&dynBuf);
    printf("\n");

    bytes    = " !!!" ;
    bytesNumber = strlen(bytes);
    printf("miscDynBufAppendBytes(\"%s\", %d) ", bytes, bytesNumber);
    executionStatusCode = miscDynBufAppendBytes(&dynBuf, bytes, bytesNumber);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    displayDynBuf(&dynBuf);
    printf("\n");



    /* miscDynBufGetByteAt */
    printf("---------------------------------------------------------------\n");
    position = miscDYN_BUF_BEGINNING_POSITION - 1;
    printf("&dynBuf = NULL :\n");
    printf("----------------\n");
    executionStatusCode = miscDynBufGetByteAt(NULL, NULL, position);
    printf("miscDynBufGetByteAt(NULL, %ld) ", position);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    printf("dynBuf Allocated :\n");
    printf("------------------\n");
    executionStatusCode = miscDynBufGetByteAt(&dynBuf, NULL, position);
    printf("miscDynBufGetByteAt(NULL, %ld) ", position);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    executionStatusCode = miscDynBufGetByteAt(&dynBuf, &byte, position);
    printf("miscDynBufGetByteAt(%ld) ", position);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    position = miscDYN_BUF_BEGINNING_POSITION;
    executionStatusCode = miscDynBufGetByteAt(&dynBuf, &byte, position);
    printf("miscDynBufGetByteAt(%ld) = \"%c\" ", position, byte);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    position = 7;
    executionStatusCode = miscDynBufGetByteAt(&dynBuf, &byte, position);
    printf("miscDynBufGetByteAt(%ld) = \"%c\" ", position, byte);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    miscDynBufGetNbStoredBytes(&dynBuf, &position);
    executionStatusCode = miscDynBufGetByteAt(&dynBuf, &byte, position);
    printf("miscDynBufGetByteAt(%ld) = \"%c\" ", position, byte);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    miscDynBufGetNbStoredBytes(&dynBuf, &position);
    position += 1;
    executionStatusCode = miscDynBufGetByteAt(&dynBuf, &byte, position);
    printf("miscDynBufGetByteAt(%ld) ", position);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");



    /* miscDynBufGetBytesFromTo */
    printf("---------------------------------------------------------------\n");
    from = miscDYN_BUF_BEGINNING_POSITION - 1;
    to = 4;
    miscDynBufGetNbStoredBytes(&dynBuf, &storedBytes);
    bytes = calloc(sizeof(char), storedBytes + 1);
    bytes[0] = '\0';
    printf("&dynBuf = NULL :\n");
    printf("----------------\n");
    executionStatusCode = miscDynBufGetBytesFromTo(NULL, bytes, from, to);
    printf("miscDynBufGetBytesFromTo(%ld, %ld) ", from, to);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    printf("dynBuf Allocated :\n");
    printf("------------------\n");
    executionStatusCode = miscDynBufGetBytesFromTo(&dynBuf, bytes, from, to);
    printf("miscDynBufGetBytesFromTo(%ld, %ld) ", from, to);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    from = miscDYN_BUF_BEGINNING_POSITION;
    to = 12;
    executionStatusCode = miscDynBufGetBytesFromTo(&dynBuf, NULL, from, to);
    printf("miscDynBufGetBytesFromTo(NULL, %ld, %ld) ", from, to);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    executionStatusCode = miscDynBufGetBytesFromTo(&dynBuf, bytes, from, to);
    bytes[(to - from) + 1] = '\0';
    printf("miscDynBufGetBytesFromTo(%ld, %ld) = \"%s\" ", from, to, bytes);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    bytes[0] = '\0';
    printf("\n");

    from = 7;
    to = 16;
    bytes[(to - from) + 1] = '\0';
    executionStatusCode = miscDynBufGetBytesFromTo(&dynBuf, bytes, from, to);
    printf("miscDynBufGetBytesFromTo(%ld, %ld) = \"%s\" ", from, to, bytes);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    bytes[0] = '\0';
    printf("\n");

    from = 6;
    to = 6;
    bytes[(to - from) + 1] = '\0';
    executionStatusCode = miscDynBufGetBytesFromTo(&dynBuf, bytes, from, to);
    printf("miscDynBufGetBytesFromTo(%ld, %ld) = \"%s\" ", from, to, bytes);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    bytes[0] = '\0';
    printf("\n");

    from = 18;
    miscDynBufGetNbStoredBytes(&dynBuf, &to);
    executionStatusCode = miscDynBufGetBytesFromTo(&dynBuf, bytes, to, from);
    printf("miscDynBufGetBytesFromTo(%ld, %ld) ", to, from);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    bytes[0] = '\0';
    printf("\n");

    executionStatusCode = miscDynBufGetBytesFromTo(&dynBuf, bytes, from, to);
    bytes[(to - from) + 1] = '\0';
    printf("miscDynBufGetBytesFromTo(%ld, %ld) = \"%s\" ", from, to, bytes);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    bytes[0] = '\0';
    printf("\n");

    miscDynBufGetNbStoredBytes(&dynBuf, &to);
    to += 1;
    executionStatusCode = miscDynBufGetBytesFromTo(&dynBuf, bytes, from, to);
    printf("miscDynBufGetBytesFromTo(%ld, %ld) ", from, to);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    free(bytes);
    printf("\n");



    /* miscDynBufReplaceByteAt */
    printf("---------------------------------------------------------------\n");
    position = miscDYN_BUF_BEGINNING_POSITION - 1;
    byte = 'H';
    printf("&dynBuf = NULL :\n");
    printf("----------------\n");
    executionStatusCode = miscDynBufReplaceByteAt(NULL, byte, position);
    printf("miscDynBufReplaceByteAt(%ld) ", position);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    printf("dynBuf Allocated :\n");
    printf("------------------\n");
    executionStatusCode = miscDynBufReplaceByteAt(&dynBuf, byte, position);
    printf("miscDynBufReplaceByteAt(%ld) ", position);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    position = miscDYN_BUF_BEGINNING_POSITION;
    executionStatusCode = miscDynBufReplaceByteAt(&dynBuf, byte, position);
    printf("miscDynBufReplaceByteAt(%ld) = \"%c\" ", position, byte);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    position = 7;
    byte = 'B';
    executionStatusCode = miscDynBufReplaceByteAt(&dynBuf, byte, position);
    printf("miscDynBufReplaceByteAt(%ld) = \"%c\" ", position, byte);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    position = 13;
    byte = '\'';
    executionStatusCode = miscDynBufReplaceByteAt(&dynBuf, byte, position);
    printf("miscDynBufReplaceByteAt(%ld) = \"%c\" ", position, byte);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    miscDynBufGetNbStoredBytes(&dynBuf, &position);
    byte = '@';
    executionStatusCode = miscDynBufReplaceByteAt(&dynBuf, byte, position);
    printf("miscDynBufReplaceByteAt(%ld) = \"%c\" ", position, byte);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    miscDynBufGetNbStoredBytes(&dynBuf, &position);
    position += 1;
    executionStatusCode = miscDynBufReplaceByteAt(&dynBuf, byte, position);
    printf("miscDynBufReplaceByteAt(%ld) ", position);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");



    /* miscDynBufInsertBytesAt */
    printf("---------------------------------------------------------------\n");
    printf("&dynBuf = NULL :\n");
    printf("----------------\n");
    executionStatusCode = miscDynBufInsertBytesAt(NULL, NULL, 0, 0);
    printf("miscDynBufInsertBytesAt(NULL, 0, 0) ");
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    printf("dynBuf Allocated :\n");
    printf("------------------\n");
    position = miscDYN_BUF_BEGINNING_POSITION - 1;
    executionStatusCode = miscDynBufInsertBytesAt(&dynBuf, NULL, 0, position);
    printf("miscDynBufInsertBytesAt(NULL, 0, %ld) ", position);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    position = miscDYN_BUF_BEGINNING_POSITION;
    executionStatusCode = miscDynBufInsertBytesAt(&dynBuf, NULL, 0, position);
    printf("miscDynBufInsertBytesAt(NULL, 0, %ld) ", position);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    bytes = "Encore un '";
    bytesNumber = 0;
    printf("miscDynBufInsertBytesAt(\"%s\", %d, %ld) ", bytes, bytesNumber,
           position);
    executionStatusCode = miscDynBufInsertBytesAt(&dynBuf, bytes, bytesNumber,
                                                  position);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    bytesNumber = strlen(bytes);
    executionStatusCode = miscDynBufInsertBytesAt(&dynBuf, bytes, bytesNumber,
                                                  position);
    printf("miscDynBufInsertBytesAt(\"%s\", %d, %ld) ", bytes, bytesNumber,
           position);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    position = 18;
    bytes = "misc";
    bytesNumber = 0;
    executionStatusCode = miscDynBufInsertBytesAt(&dynBuf, bytes, bytesNumber,
                                                  position);
    printf("miscDynBufInsertBytesAt(\"%s\", %d, %ld) ", bytes, bytesNumber,
           position);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    bytesNumber = strlen(bytes);
    executionStatusCode = miscDynBufInsertBytesAt(&dynBuf, bytes, bytesNumber,
                                                  position);
    printf("miscDynBufInsertBytesAt(\"%s\", %d, %ld) ", bytes, bytesNumber,
           position);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    miscDynBufGetNbStoredBytes(&dynBuf, &position);
    bytes = "~~~";
    bytesNumber = 0;
    executionStatusCode = miscDynBufInsertBytesAt(&dynBuf, bytes, bytesNumber,
                                                  position);
    printf("miscDynBufInsertBytesAt(\"%s\", %d, %ld) ", bytes, 0,
           position);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    bytesNumber = strlen(bytes);
    executionStatusCode = miscDynBufInsertBytesAt(&dynBuf, bytes, bytesNumber,
                                                  position);
    printf("miscDynBufInsertBytesAt(\"%s\", %d, %ld) ", bytes, bytesNumber,
           position);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    miscDynBufGetNbStoredBytes(&dynBuf, &position);
    position += 1;
    executionStatusCode = miscDynBufInsertBytesAt(&dynBuf, bytes, bytesNumber,
                                                  position);
    printf("miscDynBufInsertBytesAt(\"%s\", %d, %ld) ", bytes, bytesNumber,
           position);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");



    /* miscDynBufReplaceBytesFromTo */
    printf("---------------------------------------------------------------\n");
    from = miscDYN_BUF_BEGINNING_POSITION - 1;
    to = 9;
    bytes = NULL;
    bytesNumber = 0;
    printf("&dynBuf = NULL :\n");
    printf("----------------\n");
    printf("miscDynBufReplaceBytesFromTo(\"%s\", %d, %ld, %ld) ", bytes,
           bytesNumber, from, to);
    executionStatusCode = miscDynBufReplaceBytesFromTo(NULL, bytes, bytesNumber, 
                                                       from, to);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    printf("dynBuf Allocated :\n");
    printf("------------------\n");
    printf("miscDynBufReplaceBytesFromTo(\"%s\", %d, %ld, %ld) ", bytes,
           bytesNumber, from, to);
    executionStatusCode = miscDynBufReplaceBytesFromTo(&dynBuf, bytes,
                                                       bytesNumber, from, to);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    from = miscDYN_BUF_BEGINNING_POSITION;
    bytes = "Toujours ce";
    bytesNumber = strlen(bytes);
    printf("miscDynBufReplaceBytesFromTo(\"%s\", %d, %ld, %ld) ", bytes,
           bytesNumber, from, to);
    executionStatusCode = miscDynBufReplaceBytesFromTo(&dynBuf, bytes,
                                                       bytesNumber, from, to);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    from = 40;
    to = 42;
    bytes = "X";
    bytesNumber = 0;
    printf("miscDynBufReplaceBytesFromTo(\"%s\", %d, %ld, %ld) ", bytes,
           bytesNumber, to, from);
    executionStatusCode = miscDynBufReplaceBytesFromTo(&dynBuf, bytes, bytesNumber, to,
                                                       from);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    printf("miscDynBufReplaceBytesFromTo(\"%s\", %d, %ld, %ld) ", bytes,
           bytesNumber, from, to);
    executionStatusCode = miscDynBufReplaceBytesFromTo(&dynBuf, bytes,
                                                       bytesNumber, from, to);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    bytesNumber = strlen(bytes);
    to = 40;
    printf("miscDynBufReplaceBytesFromTo(\"%s\", %d, %ld, %ld) ", bytes,
           bytesNumber, from, to);
    executionStatusCode = miscDynBufReplaceBytesFromTo(&dynBuf, bytes,
                                                       bytesNumber, from, to);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    from = 31;
    miscDynBufGetNbStoredBytes(&dynBuf, &to);
    bytes = " !";
    bytesNumber = strlen(bytes) + 1;
    printf("miscDynBufReplaceBytesFromTo(\"%s\", %d, %ld, %ld) ", bytes,
           bytesNumber, from, to);
    executionStatusCode = miscDynBufReplaceBytesFromTo(&dynBuf, bytes,
                                                       bytesNumber, from, to);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    from = 31;
    miscDynBufGetNbStoredBytes(&dynBuf, &to);
    to += 1;
    printf("miscDynBufReplaceBytesFromTo(\"%s\", %d, %ld, %ld) ", bytes,
           bytesNumber, from, to);
    executionStatusCode = miscDynBufReplaceBytesFromTo(&dynBuf, bytes,
                                                       bytesNumber, from, to);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");



    /* miscDynBufDeleteBytesFromTo */
    printf("---------------------------------------------------------------\n");
    from = miscDYN_BUF_BEGINNING_POSITION - 1;
    to = 13;
    printf("&dynBuf = NULL :\n");
    printf("----------------\n");
    printf("miscDynBufDeleteBytesFromTo(%ld, %ld) ", from, to);
    executionStatusCode = miscDynBufDeleteBytesFromTo(NULL, from, to);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    printf("dynBuf Allocated :\n");
    printf("------------------\n");
    printf("miscDynBufDeleteBytesFromTo(%ld, %ld) ", from, to);
    executionStatusCode = miscDynBufDeleteBytesFromTo(&dynBuf, from, to);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    from = miscDYN_BUF_BEGINNING_POSITION;
    printf("miscDynBufDeleteBytesFromTo(%ld, %ld) ", from, to);
    executionStatusCode = miscDynBufDeleteBytesFromTo(&dynBuf, from, to);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    from = 7;
    to = 10;
    printf("miscDynBufDeleteBytesFromTo(%ld, %ld) ", to, from);
    executionStatusCode = miscDynBufDeleteBytesFromTo(&dynBuf, to, from);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    printf("miscDynBufDeleteBytesFromTo(%ld, %ld) ", from, to);
    executionStatusCode = miscDynBufDeleteBytesFromTo(&dynBuf, from, to);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    from = 13;
    to = 13;
    printf("miscDynBufDeleteBytesFromTo(%ld, %ld) ", from, to);
    executionStatusCode = miscDynBufDeleteBytesFromTo(&dynBuf, from, to);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    from = 13;
    miscDynBufGetNbStoredBytes(&dynBuf, &to);
    to -= 1;
    printf("miscDynBufDeleteBytesFromTo(%ld, %ld) ", from, to);
    executionStatusCode = miscDynBufDeleteBytesFromTo(&dynBuf, from, to);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    from = 12;
    miscDynBufGetNbStoredBytes(&dynBuf, &to);
    to += 1;
    printf("miscDynBufDeleteBytesFromTo(%ld, %ld) ", from, to);
    executionStatusCode = miscDynBufDeleteBytesFromTo(&dynBuf, from, to);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");



    /* miscDynBufStrip */
    printf("---------------------------------------------------------------\n");
    printf("&dynBuf = NULL :\n");
    printf("----------------\n");
    printf("miscDynBufStrip() ");
    executionStatusCode = miscDynBufStrip(NULL);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    printf("dynBuf Allocated :\n");
    printf("------------------\n");
    printf("miscDynBufStrip() ");
    executionStatusCode = miscDynBufStrip(&dynBuf);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");



    /* miscDynBufReset */
    printf("---------------------------------------------------------------\n");
    printf("&dynBuf = NULL :\n");
    printf("----------------\n");
    printf("miscDynBufReset() ");
    executionStatusCode = miscDynBufReset(NULL);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    printf("dynBuf Allocated :\n");
    printf("------------------\n");
    printf("miscDynBufReset() ");
    executionStatusCode = miscDynBufReset(&dynBuf);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");



    /* miscDynBufAppendString */
    printf("---------------------------------------------------------------\n");
    printf("&dynBuf = NULL :\n");
    printf("----------------\n");
    bytes = NULL;
    printf("miscDynBufAppendString(&dynBuf = NULL) : ");
    executionStatusCode = miscDynBufAppendString(NULL, bytes);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    printf("dynBuf Allocated :\n");
    printf("------------------\n");
    printf("miscDynBufAppendString(NULL) ");
    executionStatusCode = miscDynBufAppendString(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    bytes = "hello dynStr" ;
    printf("miscDynBufAppendString(\"%s\") ", bytes);
    executionStatusCode = miscDynBufAppendString(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    displayDynBuf(&dynBuf);
    printf("\n");

    bytes    = " ... :)" ;
    printf("miscDynBufAppendString(\"%s\") ", bytes);
    executionStatusCode = miscDynBufAppendString(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    displayDynBuf(&dynBuf);
    printf("\n");

    bytes    = " !!!" ;
    printf("miscDynBufAppendString(\"%s\") ", bytes);
    executionStatusCode = miscDynBufAppendString(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    displayDynBuf(&dynBuf);
    printf("\n");



    /* miscDynBufInsertStringAt */
    printf("---------------------------------------------------------------\n");
    printf("&dynBuf = NULL :\n");
    printf("----------------\n");
    executionStatusCode = miscDynBufInsertStringAt(NULL, NULL, 0);
    printf("miscDynBufInsertStringAt(NULL, 0) ");
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    printf("dynBuf Allocated :\n");
    printf("------------------\n");
    position = miscDYN_BUF_BEGINNING_POSITION - 1;
    executionStatusCode = miscDynBufInsertStringAt(&dynBuf, NULL, position);
    printf("miscDynBufInsertStringAt(NULL, %ld) ", position);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    position = miscDYN_BUF_BEGINNING_POSITION;
    executionStatusCode = miscDynBufInsertStringAt(&dynBuf, NULL, position);
    printf("miscDynBufInsertStringAt(NULL, %ld) ", position);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    bytes = "Encore un '";
    executionStatusCode = miscDynBufInsertStringAt(&dynBuf, bytes, position);
    printf("miscDynBufInsertStringAt(\"%s\", %ld) ", bytes, position);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    position = 18;
    bytes = "misc";
    executionStatusCode = miscDynBufInsertStringAt(&dynBuf, bytes, position);
    printf("miscDynBufInsertStringAt(\"%s\", %ld) ", bytes, position);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    miscDynBufGetNbStoredBytes(&dynBuf, &position);
    bytes = "~~~";
    executionStatusCode = miscDynBufInsertStringAt(&dynBuf, bytes, position);
    printf("miscDynBufInsertStringAt(\"%s\", %ld) ", bytes, position);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    miscDynBufGetNbStoredBytes(&dynBuf, &position);
    position += 1;
    executionStatusCode = miscDynBufInsertStringAt(&dynBuf, bytes, position);
    printf("miscDynBufInsertStringAt(\"%s\", %ld) ", bytes, position);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");



    /* miscDynBufReplaceStringFromTo */
    printf("---------------------------------------------------------------\n");
    from = miscDYN_BUF_BEGINNING_POSITION - 1;
    to = 9;
    bytes = NULL;
    printf("&dynBuf = NULL :\n");
    printf("----------------\n");
    printf("miscDynBufReplaceStringFromTo(\"%s\", %ld, %ld) ", bytes, from, to);
    executionStatusCode = miscDynBufReplaceStringFromTo(NULL, bytes, from, to);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    printf("dynBuf Allocated :\n");
    printf("------------------\n");
    printf("miscDynBufReplaceStringFromTo(\"%s\", %ld, %ld) ", bytes, from, to);
    executionStatusCode = miscDynBufReplaceStringFromTo(&dynBuf, bytes, from,
                                                        to);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    from = miscDYN_BUF_BEGINNING_POSITION;
    bytes = "Toujours ce";
    printf("miscDynBufReplaceStringFromTo(\"%s\", %ld, %ld) ", bytes, from, to);
    executionStatusCode = miscDynBufReplaceStringFromTo(&dynBuf, bytes, from,
                                                        to);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    from = 40;
    to = 42;
    bytes = " !";
    printf("miscDynBufReplaceStringFromTo(\"%s\", %ld, %ld) ", bytes, to, from);
    executionStatusCode = miscDynBufReplaceStringFromTo(&dynBuf, bytes, to,
                                                        from);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    printf("miscDynBufReplaceStringFromTo(\"%s\", %ld, %ld) ", bytes, from, to);
    executionStatusCode = miscDynBufReplaceStringFromTo(&dynBuf, bytes, from,
                                                        to);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    from = 31;
    miscDynBufGetNbStoredBytes(&dynBuf, &to);
    printf("miscDynBufReplaceStringFromTo(\"%s\", %ld, %ld) ", bytes, from, to);
    executionStatusCode = miscDynBufReplaceStringFromTo(&dynBuf, bytes, from,
                                                        to);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");

    from = 31;
    miscDynBufGetNbStoredBytes(&dynBuf, &to);
    to += 1;
    printf("miscDynBufReplaceStringFromTo(\"%s\", %ld, %ld) ", bytes, from, to);
    executionStatusCode = miscDynBufReplaceStringFromTo(&dynBuf, bytes, from,
                                                        to);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");



    /* miscDynBufDestroy */
    printf("---------------------------------------------------------------\n");
    printf("&dynBuf = NULL :\n");
    printf("----------------\n");
    printf("miscDynBufDestroy() ");
    executionStatusCode = miscDynBufDestroy(NULL);
    displayExecStatus(executionStatusCode);
    errCloseStack();
    printf("\n");

    printf("dynBuf Allocated :\n");
    printf("------------------\n");
    printf("miscDynBufDestroy() ");
    executionStatusCode = miscDynBufDestroy(&dynBuf);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");



    /* miscDynBufSetCommentPattern */
    printf("---------------------------------------------------------------\n");
    bytes = "#";
    printf("miscDynBufSetCommentPattern(%s) ", bytes);
    executionStatusCode = miscDynBufSetCommentPattern(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    printf("------------------\n");
    bytes = "//";
    printf("miscDynBufSetCommentPattern(%s) ", bytes);
    executionStatusCode = miscDynBufSetCommentPattern(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    printf("------------------\n");
    bytes = "/**";
    printf("miscDynBufSetCommentPattern(%s) ", bytes);
    executionStatusCode = miscDynBufSetCommentPattern(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    printf("------------------\n");
    bytes = ";--;";
    printf("miscDynBufSetCommentPattern(%s) ", bytes);
    executionStatusCode = miscDynBufSetCommentPattern(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    printf("------------------\n");
    bytes = NULL;
    printf("miscDynBufSetCommentPattern(%s) ", bytes);
    executionStatusCode = miscDynBufSetCommentPattern(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    printf("\n");



    /* miscDynBufLoadFile */
    printf("---------------------------------------------------------------\n");
    bytes = "../config/";
    printf("miscDynBufLoadFile(%s) ", bytes);
    executionStatusCode = miscDynBufLoadFile(&dynBuf, bytes, NULL);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    bytes = "../config/doxyfile";
    printf("miscDynBufLoadFile(%s) ", bytes);
    executionStatusCode = miscDynBufLoadFile(&dynBuf, bytes, NULL);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    printf("\n");



    /* miscDynBufSavePartInFile */
    printf("---------------------------------------------------------------\n");
    bytes = "../tmp/0.txt";
    printf("miscDynBufSavePartInFile(%d, %s) ", 0, bytes);
    executionStatusCode = miscDynBufSavePartInFile(&dynBuf, 0, bytes);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    bytes = "../tmp/10.txt";
    printf("miscDynBufSavePartInFile(%d, %s) ", 10, bytes);
    executionStatusCode = miscDynBufSavePartInFile(&dynBuf, 10, bytes);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    printf("\n");


    /*
     * Add an '\0' at the end of the buffer in order to test
     * miscDynBufSaveInASCIIFile() against miscDynBufSaveInFile().
     */
    miscDynBufAppendString(&dynBuf, "\n");

    /* miscDynBufSaveInFile */
    printf("---------------------------------------------------------------\n");
    bytes = "../tmp/";
    printf("miscDynBufSaveInFile(%s) ", bytes);
    executionStatusCode = miscDynBufSaveInFile(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    bytes = "../tmp/test.txt";
    printf("miscDynBufSaveInFile(%s) ", bytes);
    executionStatusCode = miscDynBufSaveInFile(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    printf("\n");



    /* miscDynBufSaveInASCIIFile */
    printf("---------------------------------------------------------------\n");
    bytes = "../tmp/";
    printf("miscDynBufSaveInASCIIFile(%s) ", bytes);
    executionStatusCode = miscDynBufSaveInASCIIFile(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    bytes = "../tmp/testASCII.txt";
    printf("miscDynBufSaveInASCIIFile(%s) ", bytes);
    executionStatusCode = miscDynBufSaveInASCIIFile(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    printf("\n");



    /* miscDynBufGetNextLine */
    printf("---------------------------------------------------------------\n");
    mcsLOGICAL skipFlag;
    mcsSTRING1024 nextLine;
    mcsUINT32 maxLineLength = sizeof(nextLine);
    const char *pos = NULL;
    printf("------------------\n");
    skipFlag = mcsFALSE;
    miscDynBufSetCommentPattern(&dynBuf, "\0");
    printf("skipFlag = '%s Comment Skiping' | commentPattern = '%s'\n",
           (skipFlag == mcsFALSE?"WITHOUT":"WITH"),
           miscDynBufGetCommentPattern(&dynBuf));
    while ((pos = miscDynBufGetNextLine(&dynBuf, pos, nextLine, maxLineLength,
                                        skipFlag)) != NULL)
    {
        printf("miscDynBufGetNextLine() = '%s'\n", nextLine);
    }
    errCloseStack();
    printf("------------------\n");
    pos = NULL;
    skipFlag = mcsFALSE;
    miscDynBufSetCommentPattern(&dynBuf, "#");
    printf("skipFlag = '%s Comment Skiping' | commentPattern = '%s'\n",
           (skipFlag == mcsFALSE?"WITHOUT":"WITH"),
           miscDynBufGetCommentPattern(&dynBuf));
    while ((pos = miscDynBufGetNextLine(&dynBuf, pos, nextLine, maxLineLength,
                                        skipFlag)) != NULL)
    {
        printf("miscDynBufGetNextLine() = '%s'\n", nextLine);
    }
    errCloseStack();
    printf("------------------\n");
    pos = NULL;
    skipFlag = mcsTRUE;
    miscDynBufSetCommentPattern(&dynBuf, "\0");
    printf("skipFlag = '%s Comment Skiping' | commentPattern = '%s'\n",
           (skipFlag == mcsFALSE?"WITHOUT":"WITH"),
           miscDynBufGetCommentPattern(&dynBuf));
    while ((pos = miscDynBufGetNextLine(&dynBuf, pos, nextLine, maxLineLength,
                                        skipFlag)) != NULL)
    {
        printf("miscDynBufGetNextLine() = '%s'\n", nextLine);
    }
    errCloseStack();
    printf("------------------\n");
    pos = NULL;
    skipFlag = mcsTRUE;
    miscDynBufSetCommentPattern(&dynBuf, "#");
    printf("skipFlag = '%s Comment Skiping' | commentPattern = '%s'\n",
           (skipFlag == mcsFALSE?"WITHOUT":"WITH"),
           miscDynBufGetCommentPattern(&dynBuf));
    while ((pos = miscDynBufGetNextLine(&dynBuf, pos, nextLine, maxLineLength,
                                        skipFlag)) != NULL)
    {
        printf("miscDynBufGetNextLine() = '%s'\n", nextLine);
    }
    errCloseStack();
    printf("\n");



    /* miscDynBufGetNextCommentLine */
    printf("---------------------------------------------------------------\n");
    printf("------------------\n");
    pos = NULL;
    miscDynBufSetCommentPattern(&dynBuf, "\0");
    printf("commentPattern = '%s'\n", miscDynBufGetCommentPattern(&dynBuf));
    while ((pos = miscDynBufGetNextCommentLine(&dynBuf, pos, nextLine,
                                               maxLineLength)) != NULL)
    {
        printf("miscDynBufGetNextCommentLine() = '%s'\n", nextLine);
    }
    errCloseStack();
    printf("------------------\n");
    pos = NULL;
    miscDynBufSetCommentPattern(&dynBuf, "#");
    printf("commentPattern = '%s'\n", miscDynBufGetCommentPattern(&dynBuf));
    while ((pos = miscDynBufGetNextCommentLine(&dynBuf, pos, nextLine,
                                               maxLineLength)) != NULL)
    {
        printf("miscDynBufGetNextCommentLine() = '%s'\n", nextLine);
    }
    errCloseStack();
    printf("\n");



    /* miscDynBufAppendLine */
    printf("---------------------------------------------------------------\n");
    printf("------------------\n");
    bytes = NULL;
    printf("commentPattern = '%s'\n", miscDynBufGetCommentPattern(&dynBuf));
    printf("line           = '%s'\n", bytes);
    executionStatusCode = miscDynBufAppendLine(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");
    printf("------------------\n");
    bytes = "Test de miscAppendLine() !";
    printf("commentPattern = '%s'\n", miscDynBufGetCommentPattern(&dynBuf));
    printf("line           = '%s'\n", bytes);
    executionStatusCode = miscDynBufAppendLine(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");



    /* miscDynBufAppendCommentLine */
    printf("---------------------------------------------------------------\n");
    printf("------------------\n");
    miscDynBufSetCommentPattern(&dynBuf, NULL);
    bytes = NULL;
    printf("commentPattern = '%s'\n", miscDynBufGetCommentPattern(&dynBuf));
    printf("line           = '%s'\n", bytes);
    executionStatusCode = miscDynBufAppendCommentLine(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");
    printf("------------------\n");
    bytes = "Test de miscAppendCommentLine() !";
    printf("commentPattern = '%s'\n", miscDynBufGetCommentPattern(&dynBuf));
    printf("line           = '%s'\n", bytes);
    executionStatusCode = miscDynBufAppendCommentLine(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");
    printf("------------------\n");
    miscDynBufSetCommentPattern(&dynBuf, "#");
    printf("commentPattern = '%s'\n", miscDynBufGetCommentPattern(&dynBuf));
    printf("line           = '%s'\n", bytes);
    executionStatusCode = miscDynBufAppendCommentLine(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");
    printf("------------------\n");
    miscDynBufSetCommentPattern(&dynBuf, " /*");
    printf("commentPattern = '%s'\n", miscDynBufGetCommentPattern(&dynBuf));
    printf("line           = '%s'\n", bytes);
    executionStatusCode = miscDynBufAppendCommentLine(&dynBuf, bytes);
    displayExecStatus(executionStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");



    /* miscDynBufExecuteCommand */
    printf("---------------------------------------------------------------\n");
    printf("------------------\n");
    miscDynBufInit(&dynBuf);
    bytes = "toto";
    printf("Executing '%s':\n", bytes);
    cmdStatusCode = miscDynBufExecuteCommand(&dynBuf, bytes);
    displayCmdStatus(cmdStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");
    printf("------------------\n");
    bytes = "echo \"toto\"";
    printf("Executing '%s':\n", bytes);
    cmdStatusCode = miscDynBufExecuteCommand(&dynBuf, bytes);
    displayCmdStatus(cmdStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");
    printf("------------------\n");
    bytes = "echo $PATH";
    printf("Executing '%s':\n", bytes);
    cmdStatusCode = miscDynBufExecuteCommand(&dynBuf, bytes);
    displayCmdStatus(cmdStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");
    printf("------------------\n");
    bytes = "pwd";
    printf("Executing '%s':\n", bytes);
    cmdStatusCode = miscDynBufExecuteCommand(&dynBuf, bytes);
    displayCmdStatus(cmdStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");
    printf("------------------\n");
    bytes = "/usr/bin/curl --max-time 30 -s -L \"http://www.apple.com\"";
    printf("Executing '%s':\n", bytes);
    cmdStatusCode = miscDynBufExecuteCommand(&dynBuf, bytes);
    displayCmdStatus(cmdStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");
    printf("------------------\n");
    bytes = "/usr/bin/curl --max-time 30 -s -L \"http://vizier.u-strasbg.fr/viz-bin/asu-xml?-source=I/280&-c.ra=22:57:39.05&-c.dec=-29:37:20.1&Vmag=0.00..4.00&-c.eq=J2000&-out.max=100&-c.geom=b&-c.bm=3391/1200&-c.u=arcmin&-out.add=_RAJ2000,_DEJ2000&-oc=hms&-out=*POS_EQ_PMDEC&-out=*POS_EQ_PMRA&-out=*POS_PARLX_TRIG&-out=e_Plx&-out=*SPECT_TYPE_MK&-out=*PHOT_JHN_B&-out=*PHOT_JHN_V&-out=v1&-out=v2&-out=v3&-out=d5&-out=HIP&-out=HD&-out=DM&-out=TYC1&-sort=_r&SpType=%5bOBAFGKM%5d*\"";
    printf("Executing '%s':\n", bytes);
    cmdStatusCode = miscDynBufExecuteCommand(&dynBuf, bytes);
    displayCmdStatus(cmdStatusCode);
    displayDynBuf(&dynBuf);
    errCloseStack();
    printf("\n");



    miscDynBufDestroy(&dynBuf);
    printf("---------------------------------------------------------------\n");
    printf("                      THAT'S ALL FOLKS ;)                      \n");
    printf("---------------------------------------------------------------\n");



    exit(0);
}


void displayCmdStatus(mcsINT8 cmdStatusCode)
{
    if (cmdStatusCode == mcsSUCCESS)
    {
        printf("%s\n", SUCCEED);
    }
    else
    {
        printf("%s\n", FAILED);
        errCloseStack();
    }

    return;
}

void displayExecStatus(mcsCOMPL_STAT executionStatusCode)
{
    if (executionStatusCode == mcsFAILURE)
    {
        printf("%s\n", FAILED);
        errCloseStack();
    }
    else
    {
        printf("%s\n", SUCCEED);
    }

    return;
}

void displayDynBuf(miscDYN_BUF *dynBuf)
{
    miscDynSIZE bytesNumber = 0;
    char*       tmp         = NULL;

    printf("miscDynBufGetNbStoredBytes = ");
    if (miscDynBufGetNbStoredBytes(dynBuf, &bytesNumber) == mcsFAILURE)
    {
        printf("mcsFAILURE.\n");
    }
    else
    {
        printf("'%ld'.\n", bytesNumber);
    }

    printf("miscDynBufGetNbAllocatedBytes = ");
    if (miscDynBufGetNbAllocatedBytes(dynBuf, &bytesNumber) == mcsFAILURE)
    {
        printf("mcsFAILURE.\n");
    }
    else
    {
        printf("'%ld'.\n", bytesNumber);
    }

    printf("miscDynBufGetCommentPattern = ");
    tmp = (char*)miscDynBufGetCommentPattern(dynBuf);
    if (tmp == NULL)
    {
        printf("mcsFAILURE.\n");
    }
    else
    {
        printf("\"%s\".\n", tmp);
    }

    printf("miscDynBufGetBuffer= ");
    tmp = miscDynBufGetBuffer(dynBuf);
    if (tmp == NULL)
    {
        printf("mcsFAILURE.\n");
    }
    else
    {
        printf("\"%s\".\n", tmp);
    }

    errResetStack();
}

/*___oOo___*/
