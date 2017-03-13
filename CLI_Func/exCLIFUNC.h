/*
 * Created on Mon Mar 13 2017
 *
 * The MIT License (MIT)
 * Copyright (c) 2017 savent gate
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _FUNCDEF_H_
#define _FUNCDEF_H_

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"
#include "cJSON.h"
#include <string.h>

/**
 * @Brief: Call All the Harddriver to gain purpuse.
 * @Output: pt
 */
extern BaseType_t CLI_JSON(char *pt, size_t size, const char *cmd);


/**
 * Module extern define
 */
/* Finger-Print ************************************/
extern void CLI_FingerPrint(cJSON* root, char *pcOutput);
extern void CLI_ChargePal(cJSON* root, char *pcOutput);
extern void CLI_TempControl(cJSON* root, char *pcOutput);
extern void CLI_MotorControl(cJSON* root, char *pcOutput);
extern void CLI_BodyCheck(cJSON* root, char *pcOutput);
extern void CLI_PalCheck(cJSON* root, char *pcOutput);
extern void CLI_StandBy(cJSON* root, char *pcOutput);

/**
 * Call back handle
 */

 /**
  * @Note: Need datalenth*1/3 more, cause need to convert 2 Base64
  */
 extern uint8_t FingerPrint_DataCallBack(uint8_t *src);
#endif
