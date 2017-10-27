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

#include "wilton/support/alloc_copy.hpp"
#include "wilton/support/handle_registry.hpp"
#include "wilton/support/logging.hpp"

#include "cron_task.hpp"

namespace { // anonymous

const std::string LOGGER = std::string("wilton.CronTask");

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
        wilton::support::log_debug(LOGGER, "Creating Cron task, expression: [" + cronexpr_str + "] ...");
        auto cron = wilton::cron::cron_task(cronexpr_str, [task_ctx, task_cb]{
            task_cb(task_ctx);
        });
        wilton_CronTask* cron_ptr = new wilton_CronTask(std::move(cron));
        wilton::support::log_debug(LOGGER, "Cron task created successfully, handle: [" + wilton::support::strhandle(cron_ptr) + "]");
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
        wilton::support::log_debug(LOGGER, "Stopping Cron task, handle: [" + wilton::support::strhandle(cron) + "] ...");
        cron->impl().stop();
        delete cron;
        wilton::support::log_debug(LOGGER, "Cron task stopped successfully.");
        return nullptr;
    } catch (const std::exception& e) {
        return wilton::support::alloc_copy(TRACEMSG(e.what() + "\nException raised"));
    }
}
