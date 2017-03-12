#include "cmd-fun.h"

/* Usr Include */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu_utils.h"
#include "cmsis_os.h"
#include "cjson.h"
/* CLI Command Structure define */
static const CLI_Command_Definition_t CLI_Definition_All[] = {
  {
    "hello",
    "\r\nhello:\r\n Hello World\r\n\r\n",
    CLI_HelloWorld,
    0
  },
	{
		"clear",
		"\r\nclear:\r\n clean the console\r\n\r\n",
		CLI_Clear,
		0
	},
  {
    "cpu",
    "\r\ncpu:\r\n show CPU usage\r\n\r\n",
    CLI_CPU,
    0
  },
  {
    "heap",
    "\r\nheap:\r\n show system OS heap size\r\n\r\n",
    CLI_Heap,
    0,
  },
  {
    "thread",
    "\r\nthread:\r\n list thread in system\r\n\r\n",
    CLI_ThreadList,
    0,
  },
	{
		"json",
		"\r\njson:\r\n json testNUM\r\n\r\n",
		CLI_JSON,
		1
	}
};
/* Public Function */
void CMD_Init(void) {
  size_t cnt = sizeof(CLI_Definition_All) / sizeof(CLI_Command_Definition_t);
  size_t i;
  for (i = 0; i < cnt; i++) {
    FreeRTOS_CLIRegisterCommand(&CLI_Definition_All[i]);
  }
}

/* Usr Command Function define */
static BaseType_t CLI_HelloWorld(char* pt, size_t size, const char *cmd) {
	sprintf(pt, "Hello World\r\n");
	return 0;
}

static BaseType_t CLI_Clear(char *pt, size_t size, const char *cmd) {
	sprintf(pt, "\f");
	return 0;
}

static BaseType_t CLI_CPU(char *pt, size_t size, const char *cmd) {
  sprintf(pt, "CPU usage:%d%%\r\n", osGetCPUUsage());
  return 0;
}

static BaseType_t CLI_Heap(char *pt, size_t size, const char *cmd) {
  size_t ever_free = xPortGetMinimumEverFreeHeapSize();
  size_t free = xPortGetFreeHeapSize();
  sprintf(pt, "System Never used heap::%dByte(%.2fKb)\tfree for now::%dByte(%.2fKb)\r\n",
          ever_free, (float)ever_free/1024, free, (float)free/1024);
  return 0;
}

static BaseType_t CLI_ThreadList(char *pt, size_t size, const char *cmd) {
	osThreadList((uint8_t*)pt);
  if (!*pt) {
    sprintf(pt, "Function is disabled"
    "\r\ntry set [configUSE_TRACE_FACILITY]&[configUSE_STATS_FORMATTING_FUNCTIONS] to 1\n");
  }
  return 0;
}
static BaseType_t CLI_JSON(char* pt, size_t size, const char *cmd) {
	cJSON_Hooks hook = {
		pvPortMalloc,
		vPortFree
	};
	const char input[] = "{\"name\":\"Jack\",""\"age\":\"20\"}";
	cJSON_InitHooks(&hook);
	cJSON *root = cJSON_CreateObject();
	cJSON *fmt = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "name", "Jack(\"Bee\")Nimble");
	cJSON_AddItemToObject(root, "format", fmt);
	cJSON_AddStringToObject(fmt, "type", "rect");
	cJSON_AddStringToObject(fmt, "age", "20");
	cJSON_AddNumberToObject(fmt, "width", 102);
	cJSON_AddNumberToObject(fmt, "year", 1999);
	
	char *out = cJSON_Print(root);
	printf("%s\n", out);
	vPortFree(out);
	cJSON_Delete(root);
	return 0;
}
