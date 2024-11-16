/*
 * VtrTraceWriter.cpp
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
#include "VtrTraceWriter.h"
#include "VtrTraceHeader.h"
#include "VtrStreamWriter.h"
#include "VtrMemBlockWriter.h"
#include "VtrBlockHeader.h"
#include "VtrBlockType.h"
#include "VtrTraceTerminator.h"

namespace vsc {
namespace tr {

static const int32_t TARGET_BLOCK_SZ = 8192;

VtrTraceWriter::VtrTraceWriter(
    std::ostream        *out,
    int32_t             timescale,
    int32_t             timeunit) : m_out(out), m_last_term(0) {
    memset(&m_hdr, 0, sizeof(m_hdr));
    m_hdr.magic = VTR_MAGIC;
    m_hdr.version = 0x00000100; // 0.0.1
    m_hdr.timecale = timescale;
    m_hdr.timeunit = timeunit;

    // Reserve space for the header block by writing a 
    // placeholder now
    m_out->write(reinterpret_cast<char *>(&m_hdr), sizeof(m_hdr));
}

VtrTraceWriter::~VtrTraceWriter() {

}

#ifdef UNDEFINED
void VtrTraceWriter::close() {
    // Write out the type descriptors
    /*
    m_hdr.type_desc_p = 0;
    // Write out the stream descriptors
    m_hdr.stream_desc_p = 0;
    // Write out the string table
    m_hdr.strtab_p = 0;
     */

    // Go back and update the file header
    m_out->seekp(0);
    m_out->write(reinterpret_cast<char *>(&m_hdr), sizeof(m_hdr));
}
#endif

IStreamWriter *VtrTraceWriter::addStream(const std::string &name) {
    VtrStreamWriter *stream = new VtrStreamWriter(this, name);
    m_streams.push_back(VtrStreamWriterUP(stream));
    return stream;
}

void VtrTraceWriter::flush() {
    // Collect enough data 
    std::streampos next = m_out->tellp();

    if (m_last_term == next) {
        return;
    }

    // TODO: flushStrTab
    // TODO: flushStreamDesc

    // Need to write the stream-data pointer record first.
    // But, first, we need to ensure that the streams
    // have written their pending data blocks
    std::vector<std::streampos> stream_data_p;
    for (std::vector<VtrStreamWriterUP>::const_iterator
        it=m_streams.begin();
        it!=m_streams.end(); it++) {
        stream_data_p.push_back((*it)->flush());
    }

    // Write the actual stream-data pointer record
    std::streampos stream_data_p_ptr = m_out->tellp();

    VtrTraceTerminator term;

    m_last_term = next;
}

void VtrTraceWriter::close() {
    flush();
}

int32_t VtrTraceWriter::mapStr(const std::string &str) {
    int32_t ret = -1;
    std::unordered_map<std::string,int32_t>::const_iterator it;

    if ((it=m_strtab.find(str)) != m_strtab.end()) {
        ret = it->second;
    } else {
        ret = m_strtab.size();
        m_strtab.insert({str, ret});
    }
    return ret;
}


std::streampos VtrTraceWriter::writeStreamDescriptors() {
    std::streampos ret = m_out->tellp();

    // Pack the descriptors into

    return ret;
};

std::streampos VtrTraceWriter::writeStrTab() {
    VtrMemBlockWriter writer;
    std::streampos ret = m_out->tellp();
    std::streampos last = 0;

    // First 

    if (m_strtab.size()) {
        for (std::unordered_map<std::string,int32_t>::const_iterator
            it=m_strtab.begin();
            it!=m_strtab.end(); it++) {
                writer.write_ui(it->second);
                writer.write_ui(it->first.size());
                writer.write_bytes(it->first.c_str(), it->first.size());

            if (writer.size() >= TARGET_BLOCK_SZ) {
                // Flush block 
                std::streampos block = m_out->tellp();
                VtrBlockHeader::write(
                    m_out,
                    VtrBlockType::StrTab,
                    0,
                    last,
                    &writer);

                writer.reset();
                last = block;
            }
        }

        if (writer.size()) {
            std::streampos block = m_out->tellp();
            VtrBlockHeader::write(
                m_out,
                VtrBlockType::StrTab,
                0,
                last,
                &writer);

            writer.reset();
            last = block;
        }
    } else {
        last = m_out->tellp();
        VtrBlockHeader::write(
            m_out,
            VtrBlockType::StrTab,
            0,
            0,
            0);
    }

    return last;
}

}
}
