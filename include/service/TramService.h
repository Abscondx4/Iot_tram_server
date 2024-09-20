#ifndef _TRAMSERVICE_H_
#define _TRAMSERVICE_H_

#include "stdio.h"
#include "signal.h"

#if defined(WIN32) || defined(WIN64)
#include "windows.h"
#endif

#include "pthread.h"

#include <math.h>
#include "hw_type.h"
#include "iota_init.h"
#include "iota_cfg.h"

#include "LogUtil.h"
#include "JsonUtil.h"
#include "StringUtil.h"
#include "iota_login.h"
#include "iota_datatrans.h"
#include "string.h"
#include "cJSON.h"
#include "sys/types.h"
#include "unistd.h"
#include "iota_error_type.h"
#include <malloc.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

extern int aqi;
extern int temperature;
extern int humidity;
extern int CommandNum;
extern int testnum;
extern int retTest;
extern pid_t pidUTR;
void UdpTramSent(char *result);
void *UdpTramRecv();

#endif