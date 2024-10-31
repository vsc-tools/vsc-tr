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


TraceMemValIterator::TraceMemValIterator(const vsc::dm::ValRef &val) {

}

TraceMemValIterator::~TraceMemValIterator() {

}

// Resets the iterator to its initial point
void TraceMemValIterator::reset() {

}

    // Gets the data type of the current value
dm::IDataType *TraceMemValIterator::getDataType() {

}

    // Returns the number of fields in the current scope
int32_t TraceMemValIterator::numFields() {

}

    // Pushes into a specific field scope
bool TraceMemValIterator::push(int32_t idx) {

}

    // Pops out of the current scope
bool TraceMemValIterator::pop() {

}

    // Gets the value of the current field
dm::ValRef TraceMemValIterator::getVal() {

}

}
}
