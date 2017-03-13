#ifndef _CMD_FUN_H_
#define _CMD_FUN_H_

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"
/* Public Function */
extern void CMD_Init(void);

/* Static CMD functions */
static BaseType_t CLI_HelloWorld(char* pt, size_t size, const char *cmd);
static BaseType_t CLI_Clear(char *pt, size_t size, const char *cmd);
static BaseType_t CLI_CPU(char *pt, size_t size, const char *cmd);
static BaseType_t CLI_Heap(char *pt, size_t size, const char *cmd);
static BaseType_t CLI_ThreadList(char *pt, size_t size, const char *cmd);

/* Extern CMD function */

#endif

