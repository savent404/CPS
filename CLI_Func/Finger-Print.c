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

#include "exCLIFUNC.h"
static const char base64_index[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
/**
 * @Brief: Base64 convert
 */
static void Base64_Encode(char* des, uint8_t *src, size_t size); 
/**
 * @Note:If pdata == NULL, Print a "ACK" message
         If pdata != NULL, no needs pt, will send a const string
 */
static void json_print(char*pt, uint8_t *pdata);
/**
 * @Brief: Enable module
 */
static uint8_t FingerPrint_Enable(void);
/**
 * @Brief: Disable module
 */
static uint8_t FingerPrint_Disable(void);

void CLI_FingerPrint(cJSON* root, char *pcOutput) {
    cJSON *arg = cJSON_GetObjectItem(root, "arg");

    if (!strcmp(arg->valuestring, "Enable")) {
        if (FingerPrint_Enable()) {
            goto FAIL;
        }
    } else if (!strcmp(arg->valuestring, "Disable")) {
        if (FingerPrint_Disable()) {
            goto FAIL;
        }
    }
    // Enable/Disable will do this both
    json_print(pcOutput, NULL);
    return;
FAIL: *pcOutput = 0;
}

 /**
  * @Note: Need datalenth*1/3 more, cause need to convert 2 Base64
  */
uint8_t FingerPrint_DataCallBack(uint8_t *src) {
    char *des = (char*)pvPortMalloc(512*4/3 + 1);
    Base64_Encode(des, src, 512);
    json_print(NULL, des);
    vPortFree(des);
}

__inline Bit8toBit6(char *des, uint8_t *src) {
    __IO uint8_t buf[4];
    buf[0] = src[0] >> 2;
    buf[1] = ((src[0] & 0x03) << 4) | (src[1] >> 4);
    buf[2] = ((src[0] & 0x0F) << 2) | (src[2] >> 6);
    buf[3] = src[3] & 0x3F;
    *des++ = Base64_Table[buf[0]];
    *des++ = Base64_Table[buf[1]];
    *des++ = Base64_Table[buf[2]];
    *des++ = Base64_Table[buf[3]];
}
/**
 * @Brief: Base64 convert
 */
static void Base64_Encode(char *output, const size_t length, const char *input)
{
    *output = '\0';
    if (input == NULL || length < 1) return;

    char *p = (char*)input;
    char *p_dst = (char*)output;;
    char *p_end = (char*)input + length;
    int  loop_count = 0;

    // 0x30 -> 00110000
    // 0x3C -> 00111100
    // 0x3F -> 00111111
    while (p_end - p >= 3) {
        *p_dst++ = base64_index[( p[0] >> 2 )];
        *p_dst++ = base64_index[( (p[0] << 4) & 0x30 ) | ( p[1] >> 4 )];
        *p_dst++ = base64_index[( (p[1] << 2) & 0x3C ) | ( p[2] >> 6 )];
        *p_dst++ = base64_index[p[2] & 0x3F];
        p += 3;
    }
    if (p_end - p > 0) {
        *p_dst++ = base64_index[(p[0] >> 2)];
        if (p_end - p == 2) {
            *p_dst++ = base64_index[( (p[0] << 4) & 0x30 ) | ( p[1] >> 4 )];
            *p_dst++ = base64_index[(p[1] << 2) & 0x3C]; 
            *p_dst++ = '=';
        } else if (p_end - p == 1) {
            *p_dst++ = base64_index[(p[1] << 4) & 0x30];
            *p_dst++ = '=';
            *p_dst++ = '=';
        }
    }
    *p_dst = '\0';
    return;
}
/**
 * @Note:If pdata == NULL, Print a "ACK" message
         If pdata != NULL, no needs pt, will send a const string
 */
static void json_print(char*pt, uint8_t *pdata) {
    const char const_buffer1[] = "{\"cmd\":\"Finger-Print\",\"arg\":\"data\",\"data\":\"";
    const char cnost_buffer2[] = "\"}"
    if (pdata == 0) {
        sprintf(pt, "%s%s%s\n",const_buffer1, pdata, const_buffer2);
    } else {
        cJSON *root = cJSON_CreateObject();
        cJSON_AddStringToObject(root, "cmd", "Finger-Print");
        cJSON_AddStringToObject(root, "arg", "Ack");
        puts(cJSON_Print(root));
        cJSON_Delete(root);
    }
}
/**
 * @Brief: Enable module
 */
static uint8_t FingerPrint_Enable(void);
/**
 * @Brief: Disable module
 */
static uint8_t FingerPrint_Disable(void);

