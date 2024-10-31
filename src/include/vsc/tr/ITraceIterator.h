/**
 * ITraceIterator.h
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

enum class IterEv {
    Enter,
    Leave
};

class ITraceIterator;
using ITraceIteratorUP=std::unique_ptr<ITraceIterator>;
class ITraceIterator {
public:

    virtual ~ITraceIterator() { }

    virtual bool valid() const = 0;

    virtual IterEv kind() const = 0;

    virtual ITransaction *transaction() const = 0;

    virtual bool next() = 0;

};

} /* namespace tr */
} /* namespace vsc */


