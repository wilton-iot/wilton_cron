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
 * File:   cron_task.hpp
 * Author: alex
 *
 * Created on September 7, 2016, 12:51 PM
 */

#ifndef WILTON_CRON_CRON_TASK_HPP
#define WILTON_CRON_CRON_TASK_HPP

#include <functional>
#include <string>

#include "staticlib/pimpl.hpp"

#include "wilton/support/exception.hpp"

namespace wilton {
namespace cron {

class cron_task : public sl::pimpl::object {
protected:
    /**
     * implementation class
     */
    class impl;
    
public:
    /**
     * PIMPL-specific constructor
     * 
     * @param pimpl impl object
     */
    PIMPL_CONSTRUCTOR(cron_task)

    cron_task(const std::string& cronexpr, std::function<void()> task);

    void stop();

};

} // namespace
}
#endif /* WILTON_CRON_CRON_TASK_HPP */

