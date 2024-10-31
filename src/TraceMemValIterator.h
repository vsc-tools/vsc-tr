/**
 * TraceMemValIterator.h
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
#include "vsc/dm/IValIterator.h"

namespace vsc {
namespace tr {



class TraceMemValIterator :
    public virtual dm::IValIterator {
public:
    TraceMemValIterator(const vsc::dm::ValRef &val);

    virtual ~TraceMemValIterator();

    // Resets the iterator to its initial point
    virtual void reset() override;

    // Gets the data type of the current value
    virtual dm::IDataType *getDataType() override;

    // Returns the number of fields in the current scope
    virtual int32_t numFields() override;

    // Pushes into a specific field scope
    virtual bool push(int32_t idx) override;

    // Pops out of the current scope
    virtual bool pop() override;

    // Gets the value of the current field
    virtual dm::ValRef getVal() override;

private:
    vsc::dm::ValRef             m_val;

};

}
}


