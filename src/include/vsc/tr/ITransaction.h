/**
 * ITransaction.h
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
#include "vsc/dm/impl/ValRef.h"
#include "vsc/dm/IValIterator.h"

namespace vsc {
namespace tr {

class ITransaction;
using ITransactionUP=std::unique_ptr<ITransaction>;
class ITransaction {
public:

    virtual ~ITransaction() { }

    virtual intptr_t getId() = 0;

    virtual uint64_t getTimeStart() = 0;

    virtual uint64_t getTimeEnd() = 0;

    virtual dm::IValIterator *mkValIterator() = 0;

};

} /* namespace tr */
} /* namespace vsc */


