/*
 * VtrMemBlockWriter.cpp
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
#include <string.h>
#include "VtrMemBlockWriter.h"


namespace vsc {
namespace tr {


VtrMemBlockWriter::VtrMemBlockWriter() : m_mem(0), m_mem_sz(0), m_idx(0) {
    int32_t init_sz = 64;
    m_mem = new uint8_t[init_sz];
    m_mem_sz = init_sz;
}

VtrMemBlockWriter::~VtrMemBlockWriter() {
    if (m_mem) {
        delete [] m_mem;
    }
}

void VtrMemBlockWriter::reset() {

}

int32_t VtrMemBlockWriter::write_ui(uint64_t val) {
    int32_t nbytes = 0;
    uint64_t tval = val;
    do {
        nbytes++;
        tval >>= 7;
    } while (tval);

    // Ensure sufficient space
    ensure_space(nbytes);

    // Pack in big-endian order to simplify unpacking
    for (int32_t i=nbytes-1; i>=0; i--) {
        uint8_t t = (val >> 8*i);
        m_mem[m_idx++] = i?t:(t|0x80);
    }

    return nbytes;
}

int32_t VtrMemBlockWriter::write_si(int64_t val) {
    // Use zig-zag encoding
    bool sgn = (val < 0);
    uint64_t uv = (val < 0)?-val:val;
    uint64_t tuv;
    int32_t nbytes = 0;

    uv <<= 1; // Make space for the sign bit
    uv |= sgn;

    tuv = uv;
    do {
        nbytes++;
        tuv >>= 7;
    } while (tuv);

    ensure_space(nbytes);

    for (int32_t i=nbytes-1; i>=0; i--) {
        uint8_t t = (val >> 8*i);
        m_mem[m_idx++] = i?t:(t|0x80);
    }
    
    return nbytes;
}

int32_t VtrMemBlockWriter::pack_ui(uint64_t val, uint8_t *buf) {
    int32_t nbytes = 0;
    uint64_t tval = val;
    do {
        nbytes++;
        tval >>= 7;
    } while (tval);

    if (buf) {
        // Pack in big-endian order to simplify unpacking
        for (int32_t i=nbytes-1; i>=0; i--) {
            uint8_t t = (val >> 8*i);
            buf[nbytes-1-i] = i?t:(t|0x80);
        }
    }

    return nbytes;
}

void VtrMemBlockWriter::write_bytes(const void *data, int32_t sz) {
    ensure_space(sz);
    memcpy(&m_mem[m_idx], data, sz);
    m_idx += sz;
}

int32_t VtrMemBlockWriter::pack_si(int64_t val, uint8_t *buf) {
    // Use zig-zag encoding
    bool sgn = (val < 0);
    uint64_t uv = (val < 0)?-val:val;
    uint64_t tuv;
    int32_t nbytes = 0;

    uv <<= 1; // Make space for the sign bit
    uv |= sgn;

    tuv = uv;
    do {
        nbytes++;
        tuv >>= 7;
    } while (tuv);

    if (buf) {
        for (int32_t i=nbytes-1; i>=0; i--) {
            uint8_t t = (val >> 8*i);
            buf[nbytes-1-i] = i?t:(t|0x80);
        }
    }
    
    return nbytes;
}

void VtrMemBlockWriter::ensure_space(uint32_t sz) {
    if (m_idx+sz >= m_mem_sz) {
        uint8_t *tmp = m_mem;
        int32_t new_sz = m_mem_sz?(2*m_mem_sz):64;
        m_mem = new uint8_t[new_sz];
        if (tmp) {
            memcpy(m_mem, tmp, m_mem_sz);
            delete [] tmp;
        }
        m_mem_sz = new_sz;
    }
}

}
}
