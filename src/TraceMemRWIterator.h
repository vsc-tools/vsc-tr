/**
 * TraceMemRWIterator.h
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
#include <vector>
#include "vsc/tr/ITraceIterator.h"
#include "vsc/tr/IStreamReader.h"

namespace vsc {
namespace tr {

class TraceMemRWStream;

class TraceMemRWIterator :
    public virtual ITraceIterator {
public:
    TraceMemRWIterator(
        uint64_t                            start,
        const std::vector<IStreamReader *>  &streams);

    virtual ~TraceMemRWIterator();

    virtual bool valid() override;

    virtual ITransaction *next() override;

private:
    uint64_t                                m_start;
    uint64_t                                m_time;
    int32_t                                 m_valid;
    std::vector<ITraceIteratorUP>           m_streams;
    std::vector<ITransaction *>             m_transactions;
    int32_t                                 m_stream_idx;
    ITransaction                            *m_transaction;

};

}
}


