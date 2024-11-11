/**
 * IStreamReader.h
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
#include <stdint.h>
#include "vsc/tr/IStream.h"
#include "vsc/tr/ITraceIterator.h"

namespace vsc {
namespace tr {

class IStreamReader;
using IStreamReaderUP=std::unique_ptr<IStreamReader>;
class IStreamReader :
    public virtual IStream {
public:

    virtual ~IStreamReader() { }

    enum class ItKind {
        /**
        * Returns an iterator that returns all transactions that were 
        * active within the specified window.
        * as those that continue up to end time
        */
        Active,
        /**
        * Returns an iterator that returns all transactions that have
        * a start time >=start. 
        */
        Start,
        /**
        * Returns an iterator that returns all transactions that have
        * a start and end times inside the specified range
        */
        Inside
    };

    virtual ITraceIterator *iterator(uint64_t start) = 0;

};

} /* namespace tr */
} /* namespace vsc */


