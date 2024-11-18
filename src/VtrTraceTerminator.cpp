/**
 * VtrTraceTerminator.cpp
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
#include <string.h>
#include "VtrTraceTerminator.h"

namespace vsc {
namespace tr {

std::streampos VtrTraceTerminator::write(std::ostream *out) {
    std::streampos ret = out->tellp();

    // Hand-coded packed size
    uint8_t sz = 1+8+8+8+8;
    out->put((0x80|sz));

    out->put((0x80|(int)VtrBlockType::Terminator));

    out->write((char *)&type_def_p, 8);
    out->write((char *)&stream_desc_p, 8);
    out->write((char *)&stream_data_p, 8);
    out->write((char *)&strtab_p, 8);

    return ret;
}

VtrTraceTerminator VtrTraceTerminator::read(std::istream *in, bool seek) {
    VtrTraceTerminator ret;
    // Most-common usage is for the stream to be positioned at the end of the file
    int8_t packed_sz = 1+8+8+8+8;
    if (seek) {
        in->seekg(-packed_sz, std::ios_base::seekdir::_S_cur);
    }

    memset(&ret, 0, sizeof(ret));

    uint8_t sz = (in->get() & 0x7F);

    if (sz == packed_sz) {
        ret.sz = sz;
        ret.type = (VtrBlockType)(in->get() & 0x7F);
        in->read((char *)&ret.type_def_p, 8);
        in->read((char *)&ret.stream_desc_p, 8);
        in->read((char *)&ret.stream_data_p, 8);
        in->read((char *)&ret.strtab_p, 8);
    }

    return ret;
}


} /* namespace tr */
} /* namespace vsc */


