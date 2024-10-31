/**
 * TraceMemRWStream.h
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
#include <string>
#include <vector>
#include "vsc/tr/IStreamReader.h"
#include "vsc/tr/IStreamWriter.h"
#include "TraceMemTransaction.h"

namespace vsc {
namespace tr {



class TraceMemRWStream :
    public virtual IStreamReader,
    public virtual IStreamWriter {
public:
    TraceMemRWStream(const std::string &name);

    virtual ~TraceMemRWStream();

    virtual const std::string &name() const override {
        return m_name;
    }

    virtual ITraceIterator *iterator(
        ItKind          kind,
        int64_t         start=0,
        int64_t         end=-1) override;

    virtual intptr_t addTransaction(
        uint64_t            tstart,
        uint64_t            tend,
        const dm::ValRef    &data) override;

private:
    std::string                         m_name;
    std::vector<TraceMemTransactionUP>  m_transactions;

};

}
}


