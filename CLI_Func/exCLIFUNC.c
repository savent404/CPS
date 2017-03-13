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

BaseType_t CLI_JSON(char* pt, size_t size, const char *cmd) {

    const cJSON_Hooks hook = {
        pvPortMalloc,
        vPortFree
    };
    cJSON_InitHooks((cJSON_Hooks*)&hook);
    cJSON *input = cJSON_Parse(cmd);
    if (input == NULL) {
        sprintf(pt, "Error input:%s\n", cmd);
        return 0;
    }
    cJSON *cj_cmd = cJSON_GetObjectItem(input, "cmd");
    if (cj_cmd == NULL || cj_arg == NULL) {
        sprintf(pt, "No id:cmd or arg\n");
        return 0;
    }
    
    // Found module
    if (!strcmp(cj_cmd->valuestring, "Finger-Print")) {
        CLI_FingerPrint(input, pt);
    } else if (!strcmp(cj_cmd->valuestring, "Charge-Pal")) {

    } else if (!strcmp(cj_cmd->valuestring, "Temp-Control")) {

    } else if (!strcmp(cj_cmd->valuestring, "Motor-Control")) {

    } else if (!strcmp(cj_cmd->valuestring, "Body-Check")) {

    } else if (!strcmp(cj_cmd->valuestring, "Pal-Check")) {

    } else if (!strcmp(cj_cmd->valuestring, "Stand-By")) {

    } else {
        srpintf(pt, "No such a cmd id: %s\n", cj_cmd->valuestring);
        return 0;
    }

    cJSON_Delete(input);

	return 0;
}