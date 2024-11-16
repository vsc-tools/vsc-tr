/*
 * VtrMemBlockReader.cpp
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
#include "VtrMemBlockReader.h"


namespace vsc {
namespace tr {


VtrMemBlockReader::VtrMemBlockReader(
    uint8_t         *mem,
    int32_t         mem_sz,
    bool            owned) : m_mem(mem), m_mem_sz(mem_sz), m_owned(owned) {

}

VtrMemBlockReader::~VtrMemBlockReader() {
    if (m_mem && m_owned) {
        delete [] m_mem;
        m_mem = 0;
    }
}

uint64_t VtrMemBlockReader::read_ui() {
    uint64_t val = 0;

    while (m_idx < m_mem_sz) {
        val <<= 7;
        val |= (m_mem[m_idx] & 0x7F);

        if (m_mem[m_idx++]&0x80) {
            break;
        }
    }

    return val;
}

int64_t VtrMemBlockReader::read_si() {
    uint64_t val = read_ui();
    int64_t ret = (val >> 1);

    if (val & 1) {
        ret = -ret;
    }

    return ret;
}

void VtrMemBlockReader::reset() {
    m_idx = 0;
}

}
}
