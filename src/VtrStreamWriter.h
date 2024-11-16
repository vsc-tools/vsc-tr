/**
 * VtrStreamWriter.h
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
#include <memory>
#include <string>
#include "vsc/tr/IStreamWriter.h"
#include "VtrMemBlockWriter.h"

namespace vsc {
namespace tr {

class VtrTraceWriter;

class VtrStreamWriter;
using VtrStreamWriterUP=std::unique_ptr<VtrStreamWriter>;
class VtrStreamWriter :
    public virtual IStreamWriter {
public:
    VtrStreamWriter(
        VtrTraceWriter      *trace,
        const std::string   &name);

    virtual ~VtrStreamWriter();

    virtual const std::string &name() const { return m_name; }

    virtual intptr_t addTransaction(
        uint64_t            tstart,
        uint64_t            tend,
        const dm::ValRef    &data) override;

    std::streampos flush();

private:
    VtrTraceWriter          *m_trace;
    std::string             m_name;
    VtrMemBlockWriter       m_writer;
    VtrMemBlockWriter       m_twriter;
    intptr_t                m_tid;
    bool                    m_block_first;
    uint64_t                m_block_first_end;
    uint64_t                m_block_first_start;

    // Pointer to the previous stream-data bloc
    std::streampos          m_prev;
};

}
}


