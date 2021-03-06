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
 * File:   wilton_cron.cpp
 * Author: alex
 * 
 * Created on September 7, 2016, 8:22 PM
 */

#include "wilton/wilton_cron.h"

#include <string>

#include "staticlib/config.hpp"
#include "staticlib/utils.hpp"

#include "wilton/support/alloc.hpp"
#include "wilton/support/logging.hpp"
#include "wilton/support/misc.hpp"

#include "cron_task.hpp"

namespace { // anonymous

const std::string logger = std::string("wilton.CronTask");

} // namespace

struct wilton_CronTask {
private:
    wilton::cron::cron_task cron;

public:
    wilton_CronTask(wilton::cron::cron_task&& cron) :
    cron(std::move(cron)) { }

    wilton::cron::cron_task& impl() {
        return cron;
    }
};


char* wilton_CronTask_start(
        wilton_CronTask** cron_out,
        const char* cronexpr,
        int cronexpr_len,
        void* task_ctx,
        void (*task_cb)(
                void* task_ctx)) /* noexcept */ {
    if (nullptr == cron_out) return wilton::support::alloc_copy(TRACEMSG("Null 'cron_out' parameter specified"));
    if (nullptr == cronexpr) return wilton::support::alloc_copy(TRACEMSG("Null 'cronexpr' parameter specified"));
    if (!sl::support::is_uint16_positive(cronexpr_len)) return wilton::support::alloc_copy(TRACEMSG(
            "Invalid 'cronexpr_len' parameter specified: [" + sl::support::to_string(cronexpr_len) + "]"));
    if (nullptr == task_cb) return wilton::support::alloc_copy(TRACEMSG("Null 'task_cb' parameter specified"));
    try {
        auto cronexpr_str = std::string(cronexpr, static_cast<uint16_t> (cronexpr_len));
        wilton::support::log_debug(logger, "Creating Cron task, expression: [" + cronexpr_str + "] ...");
        auto cron = wilton::cron::cron_task(cronexpr_str, [task_ctx, task_cb]{
            task_cb(task_ctx);
        });
        wilton_CronTask* cron_ptr = new wilton_CronTask(std::move(cron));
        wilton::support::log_debug(logger, "Cron task created successfully, handle: [" + wilton::support::strhandle(cron_ptr) + "]");
        *cron_out = cron_ptr;
        return nullptr;
    } catch (const std::exception& e) {
        return wilton::support::alloc_copy(TRACEMSG(e.what() + "\nException raised"));
    }
}

char* wilton_CronTask_stop(
        wilton_CronTask* cron) {
    if (nullptr == cron) return wilton::support::alloc_copy(TRACEMSG("Null 'cron' parameter specified"));
    try {
        wilton::support::log_debug(logger, "Stopping Cron task, handle: [" + wilton::support::strhandle(cron) + "] ...");
        cron->impl().stop();
        delete cron;
        wilton::support::log_debug(logger, "Cron task stopped successfully.");
        return nullptr;
    } catch (const std::exception& e) {
        return wilton::support::alloc_copy(TRACEMSG(e.what() + "\nException raised"));
    }
}
