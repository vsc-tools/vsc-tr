/**
 * TraceMemRW.h
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
#include "dmgr/IDebugMgr.h"
#include "vsc/tr/ITraceRW.h"

namespace vsc {
namespace tr {



class TraceMemRW :
    public virtual ITraceRW {
public:
    TraceMemRW(dmgr::IDebugMgr *dmgr);

    virtual ~TraceMemRW();

    virtual void close() override { }

    virtual void flush() override { }

    virtual IStreamWriter *addStream(const std::string &name) override;

    virtual const std::vector<IStreamReaderUP> &getStreams() const override {
        return m_streams;
    }

    virtual ITraceIterator *iterate(
        uint64_t                            start,
        const std::vector<IStreamReader *>  &streams) override;

protected:
    static dmgr::IDebug                     *m_dbg;
    std::vector<IStreamReaderUP>            m_streams;

};

}
}


