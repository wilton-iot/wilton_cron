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

