/*
 * TraceMemRW.cpp
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
#include "dmgr/impl/DebugMacros.h"
#include "TraceMemRW.h"


namespace vsc {
namespace tr {


TraceMemRW::TraceMemRW(dmgr::IDebugMgr *dmgr) {
    DEBUG_INIT("vsc::tr:TraceMemRW", dmgr);
}

TraceMemRW::~TraceMemRW() {

}

IStreamWriter *TraceMemRW::addStream(const std::string &name) {
    DEBUG_ENTER("addStream");

    DEBUG_LEAVE("addStream");
}

ITraceIterator *TraceMemRW::iterate(
        uint64_t                            start,
        const std::vector<IStreamReader *>  &streams) {
    DEBUG_ENTER("iterate");

    DEBUG_LEAVE("iterate");
}

dmgr::IDebug *TraceMemRW::m_dbg = 0;

}
}
