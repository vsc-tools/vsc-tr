/**
 * TraceMemTransaction.h
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
#include "vsc/tr/ITransaction.h"

namespace vsc {
namespace tr {

class TraceMemTransaction;
using TraceMemTransactionUP=std::unique_ptr<TraceMemTransaction>;
class TraceMemTransaction :
    public virtual ITransaction {
public:
    TraceMemTransaction(
        uint64_t                start,
        uint64_t                end,
        const vsc::dm::ValRef   &val
    );

    virtual ~TraceMemTransaction();

    virtual intptr_t getId() override {
        return (intptr_t)this;
    }

    virtual uint64_t getTimeStart() override {
        return m_start;
    }

    virtual uint64_t getTimeEnd() override {
        return m_end;
    }

    virtual dm::IValIterator *mkValIterator() override;

private:
    uint64_t                    m_start;
    uint64_t                    m_end;
    vsc::dm::ValRef             m_val;

};

}
}


