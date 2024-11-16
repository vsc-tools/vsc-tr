/**
 * VtrMemBlockReader.h
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

namespace vsc {
namespace tr {



class VtrMemBlockReader {
public:
    VtrMemBlockReader(uint8_t *mem, int32_t mem_sz, bool owned);

    virtual ~VtrMemBlockReader();

    uint64_t read_ui();

    int64_t read_si();

    void reset();

    bool valid() const { return m_idx < m_mem_sz; }

private:
    uint8_t                 *m_mem;
    int32_t                 m_mem_sz;
    bool                    m_owned;
    int32_t                 m_idx;


};

}
}


