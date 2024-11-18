/**
 * VtrMemBlockWriter.h
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
#include "IVtrWriter.h"

namespace vsc {
namespace tr {



class VtrMemBlockWriter :
    public virtual IVtrWriter {
public:
    VtrMemBlockWriter();

    virtual ~VtrMemBlockWriter();

    void reset();

    uint32_t size() { return m_idx; }

    char *mem() { return (char *)m_mem; }

    virtual int32_t write_ui(uint64_t val) override;

    virtual int32_t write_si(int64_t val) override;

    virtual void write_bytes(const void *data, int32_t sz) override;

    static int32_t pack_ui(uint64_t val, uint8_t *buf);

    static int32_t pack_si(int64_t val, uint8_t *buf);

private:
    void ensure_space(uint32_t sz);

private:
    uint8_t             *m_mem;
    uint32_t            m_mem_sz;
    uint32_t            m_idx;

};

}
}


