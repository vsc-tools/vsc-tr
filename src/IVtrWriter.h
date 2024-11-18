/**
 * IVtrWriter.h
 *
 * Copyright 2023 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * Created on:
 *     Author: 
 */
#pragma once
#include <stdint.h>

namespace vsc {
namespace tr {



class IVtrWriter {
public:

    virtual ~IVtrWriter() { }

    virtual int32_t write_ui(uint64_t val) = 0;

    virtual int32_t write_si(int64_t val) = 0;

    virtual void write_bytes(const void *data, int32_t sz) = 0;

};

} /* namespace tr */
} /* namespace vsc */


