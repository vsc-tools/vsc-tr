/**
 * VtrTraceTerminator.h
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
#include <istream>
#include <ostream>
#include "VtrBlockType.h"

namespace vsc {
namespace tr {

struct VtrTraceTerminator {
    uint8_t         sz; // sz and type ensure this is a valid block
    VtrBlockType    type;
    uint64_t        type_def_p;
    uint64_t        stream_desc_p; // points to the tail of the stream-
    uint64_t        stream_data_p; // points back to a variable-size block
    uint64_t        strtab_p; // points to the tail of the strtab chain

    std::streampos write(std::ostream *out);

    static VtrTraceTerminator read(std::istream *in, bool seek=true);
};

} /* namespace tr */
} /* namespace vsc */


