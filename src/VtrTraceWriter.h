/**
 * VtrTraceWriter.h
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
#include <ostream>
#include <unordered_map>
#include <vector>
#include "vsc/dm/IDataType.h"
#include "vsc/tr/ITraceWriter.h"
#include "VtrTraceHeader.h"
#include "VtrStreamWriter.h"

namespace vsc {
namespace tr {



class VtrTraceWriter :
    public virtual ITraceWriter {
public:
    VtrTraceWriter(
        std::ostream        *out,
        int32_t             timescale,
        int32_t             timeunit
    );

    virtual ~VtrTraceWriter();

    virtual IStreamWriter *addStream(const std::string &name) override;

    virtual void flush() override;

    virtual void close() override;

    int32_t mapStr(const std::string &str, bool add=true);

    std::ostream *out() const { return m_out; }

    int32_t getTypeId(dm::IDataType *t, bool add=true);

protected:

    std::streampos writeTypeDef();

    std::streampos writeStreamDescriptors();

    std::streampos writeStrTab();

private:
    std::ostream                                    *m_out;
    VtrTraceHeader                                  m_hdr;

    // Stream descriptor
    std::vector<VtrStreamWriterUP>                  m_streams;
    int32_t                                         m_streams_last_sz;
    std::streampos                                  m_streams_last;

    // Type Desc
    std::unordered_map<dm::IDataType *,int32_t>     m_type_m;
    std::vector<dm::IDataType *>                    m_type_l;
    int32_t                                         m_type_desc_last_sz;
    std::streampos                                  m_type_desc_last;

    // String Tab
    std::unordered_map<std::string,int32_t>         m_strtab;
    std::vector<std::string>                        m_strtab_l;
    int32_t                                         m_strtab_last_sz;
    std::streampos                                  m_strtab_last;

    std::streampos                                  m_last_term;

};

}
}


