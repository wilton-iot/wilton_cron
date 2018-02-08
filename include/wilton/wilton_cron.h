/*
 * Copyright 2017, alex at staticlibs.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   wilton_cron.h
 * Author: alex
 *
 * Created on September 22, 2017, 6:47 PM
 */

#ifndef WILTON_CRON_H
#define WILTON_CRON_H

#include "wilton/wilton.h"

#ifdef __cplusplus
extern "C" {
#endif

// Cron

struct wilton_CronTask;
typedef struct wilton_CronTask wilton_CronTask;

char* wilton_CronTask_start(
        wilton_CronTask** cron_out,
        const char* cronexpr,
        int cronexpr_len,
        void* task_ctx,
        void (*task_cb)(
                void* task_ctx));


char* wilton_CronTask_stop(
        wilton_CronTask* cron);

#ifdef __cplusplus
}
#endif

#endif /* WILTON_CRON_H */

