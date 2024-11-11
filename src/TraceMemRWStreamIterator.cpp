/*
 * TraceMemRWStreamIterator.cpp
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
#include "TraceMemRWStream.h"
#include "TraceMemRWStreamIterator.h"


namespace vsc {
namespace tr {


TraceMemRWStreamIterator::TraceMemRWStreamIterator(
    uint64_t            start,
    TraceMemRWStream    *stream) : m_start(start), m_stream_idx(-1), m_stream(stream) {

}

TraceMemRWStreamIterator::~TraceMemRWStreamIterator() {

}

bool TraceMemRWStreamIterator::valid() {
    if (m_stream_idx == -1) {
        // Find the first transaction that starts >= m_start
        for (uint32_t i=0; i<m_stream->numTransactions(); i++) {
            if (m_stream->getTransaction(i)->getTimeStart() >= m_start) {
                m_stream_idx = i;
                break;
            }
        }
    }

    return (m_stream_idx >= 0 && m_stream_idx < m_stream->numTransactions());
}

ITransaction *TraceMemRWStreamIterator::next() {
    if (m_stream_idx == -1) {
        // Find the first transaction that starts >= m_start
        for (uint32_t i=0; i<m_stream->numTransactions(); i++) {
            if (m_stream->getTransaction(i)->getTimeStart() >= m_start) {
                m_stream_idx = i;
                break;
            }
        }
    }

    if (m_stream_idx >= 0 && m_stream_idx < m_stream->numTransactions()) {
        m_transaction = m_stream->getTransaction(m_stream_idx);
        m_stream_idx++;
    } else {
        m_transaction = 0;
    }
    
    return m_transaction;
}

}
}
