/**
 * ITraceReader.h
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
#include "vsc/tr/IStreamReader.h"
#include "vsc/tr/ITrace.h"
#include "vsc/tr/ITraceIterator.h"

namespace vsc {
namespace tr {



class ITraceReader :
    public virtual ITrace {
public:

    virtual ~ITraceReader() { }

    // TODO: Need some facility for getting system meta-data

    virtual const std::vector<IStreamReaderUP> &getStreams() const = 0;

    virtual ITraceIterator *iterate(
        uint64_t                            start,
        const std::vector<IStreamReader *>  &streams) = 0;

};

} /* namespace tr */
} /* namespace vsc */


