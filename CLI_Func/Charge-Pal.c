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

enum Channel
{
    Channel_1 = 1,Channel_2,Channel_3,Channel_4,Channel_5,Channel_6
};

static float getV(enum Channel ch);
static float getI(enum Channel ch);
static uint32_t getID(enum Channel ch);
static void  ChargeEnable(enum Channel ch);
static void  ChargeDisable(enum Channel ch);
static uint8_t isThere(enum Channel ch);
static uint8_t isCharge(enum Channel ch);
static void returnAck(char *pt);
static void returnData(char *pt, enum Channel ch);

void CLI_ChargePal(cJSON* root, char *pcOutput) {
    cJSON *arg = cJSON_GetObjectItem(root, "arg");
    cJSON *ch  = cJSON_GetObjectItem(root, "channel");
    if (arg == NULL || ch == NULL) {
        sprintf(pcOutput, "No ID:channel");
        return;
    } else if ((uint8_t)(ch->valueint) > 6) {
        sprintf(pcOutput, "NO channel:%d", ch->valueint);
        return;
    }

    if (!strcmp(arg->valuestring, "Enable")) {
        ChargeEnable(ch->valueint);
        returnAck(pcOutput);
        return;
    } else if (!strcmp(arg->valuestring, "Disable")) {
        ChargeDisable(ch->valueint);
        returnAck(pcOutput);
        return;
    } else if (!strcmp(arg->valuestring, "Get-Status")) {
        returnData(pcOutput, ch->valueint);
        return;
    } else {
        sprintf(pcOutput, "No such a arg:%s\n", arg->valuestring);
        return;
    }
}

static float getV(enum Channel ch) {
    return -99;
}
static float getI(enum Channel ch) {
    return -99;
}
static uint32_t getID(enum Channel ch) {
    return 0xFFFFFF;
}
static void  ChargeEnable(enum Channel ch) {

}
static void  ChargeDisable(enum Channel ch) {

}
static uint8_t isThere(enum Channel ch) {
    return 0;
}
static uint8_t isCharge(enum Channel ch) {
    return 0;
}
static void returnAck(char *pt, enum Channel ch) {
    cJSON *t = cJSON_CreateObject();
    cJSON_AddStringToObject(t, "cmd", "Charge-Pal");
    cJSON_AddStringToObject(t, "arg", "Ack");
    cJSON_AddNumberToObject(t, "channel", ch);
    sprintf(pt, "%s", cJSON_Print(t));
    cJSON_Delete(t);
}
static void returnData(char *pt, enum Channel ch) {
    cJSON *t = cJSON_CreateObject();
    cJSON_AddStringToObject(t, "cmd", "Charge-Pal");
    cJSON_AddStringToObject(t, "arg", "data");
    cJSON *data = cJSON_CreateObject();
    cJSON_AddItemReferenceToObject(t, "data", data);
    cJSON_AddNumberToObject(data, "channel", ch);
    cJSON_AddBoolToObject(data, "IsThere", isThere(ch));
    cJSON_AddNumberToObject(data, "ID", getID(ch));
    cJSON_AddNumberToObject(data, "Vol", getV(ch));
    cJSON_AddNumberToObject(data, "I", getI(ch));
    cJSON_AddBoolToObject(data, "IsCharge", isCharge(ch));

    sprintf(pt, "%s", cJSON_Print(t));
    cJSON_Delete(t);
}