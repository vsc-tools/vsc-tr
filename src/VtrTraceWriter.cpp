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
    int32_t             timeunit) : m_out(out), 
    m_streams_last_sz(0), m_streams_last(0),
    m_type_desc_last_sz(0), m_type_desc_last(0),
    m_strtab_last_sz(0), m_strtab_last(0),
    m_last_term(0) {
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
    std::streampos next = 0;

    std::streampos type_def_p = writeTypeDef();
    if (type_def_p > next) {
        next = type_def_p;
    }

    // Flush any new string entries
    std::streampos strtab_p = writeStrTab();
    if (strtab_p > next) {
        next = strtab_p;
    }

    // TODO: flushStreamDesc
    std::streampos stream_desc_p = writeStreamDescriptors();
    if (stream_desc_p > next) {
        next = stream_desc_p;
    }

    // Need to write the stream-data pointer record first.
    // But, first, we need to ensure that the streams
    // have written their pending data blocks
    std::vector<std::streampos> stream_data_p;
    for (std::vector<VtrStreamWriterUP>::const_iterator
        it=m_streams.begin();
        it!=m_streams.end(); it++) {
        std::streampos stream_last = (*it)->flush();
        if (stream_last > next) {
            next = stream_last;
        }
        stream_data_p.push_back(stream_last);
    }

    if (next > m_last_term) {
        // Data has been written since the last terminator
        // was output

        // Write the actual stream-data pointer record
        std::streampos stream_data_p_ptr = m_out->tellp();
        char tmp[64];
        uint32_t nbytes;

        // Write the number of elements
        nbytes = VtrMemBlockWriter::pack_ui(m_streams.size(), (uint8_t *)tmp);
        m_out->write(tmp, nbytes);
        for (std::vector<std::streampos>::const_iterator
            it=stream_data_p.begin();
            it!=stream_data_p.end(); it++) {
            // Write out the last stream-data pointers
            nbytes = VtrMemBlockWriter::pack_ui(*it, (uint8_t *)tmp);
            m_out->write(tmp, nbytes);
        }

        // Now, write the Terminator record
        VtrTraceTerminator term;
        term.type = VtrBlockType::Terminator;
        term.type_def_p = 0;
        term.stream_desc_p = stream_desc_p;
        term.stream_data_p = stream_data_p_ptr;
        term.strtab_p = strtab_p;

        term.write(m_out);

        // Record the position *after* writing the
        // terminator, since that's what we have 
        // available when flush() is called next
        m_last_term = m_out->tellp();
    }




}

void VtrTraceWriter::close() {
    flush();
}

int32_t VtrTraceWriter::mapStr(const std::string &str, bool add) {
    int32_t ret = -1;
    std::unordered_map<std::string,int32_t>::const_iterator it;

    if ((it=m_strtab.find(str)) != m_strtab.end()) {
        ret = it->second;
    } else if (add) {
        ret = m_strtab_l.size();
        m_strtab.insert({str, ret});
        m_strtab_l.push_back(str);
    }
    return ret;
}

int32_t VtrTraceWriter::getTypeId(dm::IDataType *t, bool add) {
    int32_t ret = -1;
    std::unordered_map<dm::IDataType *,int32_t>::const_iterator it;
    if ((it=m_type_m.find(t)) != m_type_m.end()) {
        ret = it->second;
    } else if (add) {
        ret = m_type_l.size();
        m_type_m.insert({t, ret});
        m_type_l.push_back(t);
    }
    return ret;
}

std::streampos VtrTraceWriter::writeTypeDef() {

}


std::streampos VtrTraceWriter::writeStreamDescriptors() {
    std::streampos ret = m_type_desc_last;

    if (m_streams.size() > m_streams_last_sz) {
        VtrMemBlockWriter writer;
        ret = m_out->tellp();
        for (uint32_t i=m_streams_last_sz; i<m_streams.size(); i++) {
            if (writer.size() > 16384) {
                // Flush
                writer.reset();
            }
        }

        if (writer.size()) {
            // Flush
        }

        m_streams_last_sz = m_streams.size();
    }

    // Pack the descriptors into

    return ret;
};

std::streampos VtrTraceWriter::writeStrTab() {
    VtrMemBlockWriter writer;
    std::streampos ret = m_out->tellp();
    std::streampos last = m_strtab_last;

    // First 

    if (m_strtab_last_sz < m_strtab_l.size()) {
        for (uint32_t i=m_strtab_last_sz; i<m_strtab_l.size(); i++) {
            writer.write_bytes(m_strtab_l.at(i).c_str(), m_strtab_l.at(i).size());

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
        m_strtab_last_sz = m_strtab_l.size();

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
    }
    m_strtab_last = last;

    return last;
}

}
}
