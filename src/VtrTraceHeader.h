/**
 * VtrTraceHeader.h
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

static const uint32_t VTR_MAGIC = 0x00525456; // Assume little-endian

struct VtrTraceHeader {
    uint32_t            magic;
    uint32_t            version;
    int32_t             timecale;
    int32_t             timeunit;
};

} /* namespace tr */
} /* namespace vsc */


