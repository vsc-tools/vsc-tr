/*
 * VtrBlockHeader.cpp
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
#include "VtrBlockHeader.h"
#include "VtrMemBlockWriter.h"


namespace vsc {
namespace tr {


VtrBlockHeader::VtrBlockHeader() {

}

VtrBlockHeader::~VtrBlockHeader() {

}

void VtrBlockHeader::write(
        std::ostream            *out,
        VtrBlockType            type,
        uint32_t                flags,
        std::streampos          prev,
        int32_t                 body_sz) {
    uint8_t sz_tmp[16];

    // First, calculate the size of the header
    int32_t hdr_sz = 1; // type
    hdr_sz += 1; // flags
    hdr_sz += (prev)?VtrMemBlockWriter::pack_ui(prev, 0):1;
    int32_t nbytes = VtrMemBlockWriter::pack_ui(body_sz+hdr_sz, sz_tmp);

    // Write the block size
    out->write((char *)sz_tmp, nbytes);

    // Write the type
    nbytes = VtrMemBlockWriter::pack_ui((int)VtrBlockType::StrTab, sz_tmp);
    out->write((char *)sz_tmp, nbytes);

    // Write the flags
    nbytes = VtrMemBlockWriter::pack_ui(0, sz_tmp);
    out->write((char *)sz_tmp, nbytes);

    // Write the prev-block pointer
    nbytes = VtrMemBlockWriter::pack_ui(prev, sz_tmp);
    out->write((char *)sz_tmp, nbytes);
}

void VtrBlockHeader::write(
        std::ostream            *out,
        VtrBlockType            type,
        uint32_t                flags,
        std::streampos          prev,
        VtrMemBlockWriter       *writer) {
    write(out, type, flags, prev, writer->size());
    out->write(writer->mem(), writer->size());
}

}
}
