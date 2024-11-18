/*
 * VtrStreamWriter.cpp
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
#include "VtrStreamWriter.h"
#include "VtrMemBlockWriter.h"
#include "VtrTraceWriter.h"
#include "VtrBlockHeader.h"


namespace vsc {
namespace tr {


VtrStreamWriter::VtrStreamWriter(
    VtrTraceWriter      *trace,
    const std::string   &name) : m_trace(trace), m_name(name), m_tid(0),
        m_block_first(true), m_block_first_end(~0), m_block_first_start(~0),
        m_prev(0) {

}

VtrStreamWriter::~VtrStreamWriter() {

}

intptr_t VtrStreamWriter::addTransaction(
        uint64_t            tstart,
        uint64_t            tend,
        const dm::ValRef    &data) {
    intptr_t tid = m_tid;
    m_tid++;

    if (m_block_first) {
        m_block_first_end = tend;
        m_block_first_start = ~0;
        m_block_first = false;
    }
    if (tstart < m_block_first_start) {
        m_block_first_start = tstart;
    }

    // The times we record are offsets of the first 
    // transaction end in the block
    int64_t tstart_delta = (tstart - m_block_first_end);
    int64_t tend_delta = (tend - m_block_first_end);

    // First, write the payload to the temp writer
    m_twriter.write_si(tstart_delta);
    m_twriter.write_si(tend_delta);

    int32_t type_id = m_trace->getTypeId(data.type());
    m_twriter.write_ui(type_id);

    // TODO: pack data

    // Now, write to the primary writer
    m_writer.write_ui(m_twriter.size()); // transaction size
    m_writer.write_bytes(m_twriter.mem(), m_twriter.size());

    if (m_writer.size() > 16384) { // Target block size
        flush();
    }

    m_twriter.reset();

    return tid;
}

std::streampos VtrStreamWriter::flush() {
    if (!m_block_first) {
        // Write whatever data has accumulated
        std::streampos next = m_trace->out()->tellp();

        VtrBlockHeader::write(
            m_trace->out(),
            VtrBlockType::StreamData,
            0,
            m_prev,
            &m_writer);

        m_prev = next;
        m_block_first = true;
        m_writer.reset();
    }
    return m_prev;
}

}
}
