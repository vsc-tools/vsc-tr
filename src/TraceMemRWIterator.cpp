/*
 * TraceMemRWIterator.cpp
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
#include "TraceMemRWIterator.h"
#include "TraceMemRWStream.h"


namespace vsc {
namespace tr {


TraceMemRWIterator::TraceMemRWIterator(
    uint64_t                                start,
    const std::vector<IStreamReader *>      &streams) : 
        m_start(start), m_time(0), m_valid(0), 
        m_stream_idx(-1), m_transaction(0) {
    for (std::vector<IStreamReader *>::const_iterator
        it=streams.begin();
        it!=streams.end(); it++) {
        m_streams.push_back(ITraceIteratorUP((*it)->iterator(start)));
    }
}

TraceMemRWIterator::~TraceMemRWIterator() {

}

bool TraceMemRWIterator::valid() {
    if (!m_valid) {
        // This only happens on the first valid() call, and the
        // valid call that confirms that all transactions have
        // been exhausted.
        for (std::vector<ITraceIteratorUP>::const_iterator
            it=m_streams.begin();
            it!=m_streams.end(); it++) {
            if ((*it)->valid()) {
                (*it)->next();
                m_valid++;
            }
        }
    }

    // Need at least one transaction ready to go
    return (m_valid != 0);
}

ITransaction *TraceMemRWIterator::next() {
    // Pick the next transaction
    int32_t start_idx;
    int32_t select_idx = -1;

    if (m_stream_idx != -1) {
        m_streams.at(m_stream_idx)->next();
        if (!m_streams.at(m_stream_idx)->valid()) {
            m_valid--;
        }
    } else {
        m_stream_idx = 0;
    }
    m_transaction = 0;
    start_idx = m_stream_idx;

    do {
        if (m_streams.at(m_stream_idx)->valid()) {
            /*
            if (!m_transaction) {
                m_transaction = m_streams.at(m_stream_idx)->transaction();
                select_idx = m_stream_idx;
            } else if (m_streams.at(m_stream_idx)->transaction()->getTimeStart() < m_transaction->getTimeStart()) {
                m_transaction = m_streams.at(m_stream_idx)->transaction();
                select_idx = m_stream_idx;
            }
             */
        }
        m_stream_idx = ((m_stream_idx+1) % m_streams.size());
    } while (start_idx != m_stream_idx);

    m_stream_idx = select_idx;

    return m_transaction;
}

}
}
