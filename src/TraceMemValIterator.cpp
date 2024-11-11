/*
 * TraceMemValIterator.cpp
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
#include "TraceMemValIterator.h"


namespace vsc {
namespace tr {


TraceMemValIterator::TraceMemValIterator(const vsc::dm::ValRef &val) :
    m_val(val), m_it(m_val.type()->mkValIterator(m_val)) {
    

}

TraceMemValIterator::~TraceMemValIterator() {

}

// Resets the iterator to its initial point
void TraceMemValIterator::reset() {
    m_it->reset();
}

    // Gets the data type of the current value
dm::IDataType *TraceMemValIterator::getDataType() {
    return m_it->getDataType();
}

    // Returns the number of fields in the current scope
int32_t TraceMemValIterator::numFields() {
    return m_it->numFields();
}

dm::IDataType *TraceMemValIterator::getFieldType(int32_t idx) {
    return m_it->getFieldType(idx);
}

std::string TraceMemValIterator::getFieldName(int32_t idx) {
    return m_it->getFieldName(idx);
}

dm::ValRef TraceMemValIterator::getFieldVal(int32_t idx) {
    return m_it->getFieldVal(idx);
}

    // Pushes into a specific field scope
bool TraceMemValIterator::push(int32_t idx) {
    return m_it->push(idx);
}

    // Pops out of the current scope
bool TraceMemValIterator::pop() {
    return m_it->pop();
}

    // Gets the value of the current field
dm::ValRef TraceMemValIterator::getVal() {
    return m_it->getVal();
}

}
}
