/*
 * VtrTypeDescReader.cpp
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
#include "VtrTypeDescReader.h"
#include "VtrDataType.h"


namespace vsc {
namespace tr {


VtrTypeDescReader::VtrTypeDescReader(dm::IContext *ctxt) : m_ctxt(ctxt) {

}

VtrTypeDescReader::~VtrTypeDescReader() {

}

dm::IDataType *VtrTypeDescReader::read(IVtrReader *reader) {
    dm::IDataType *ret = 0;
    uint32_t sz = reader->read_ui();
    VtrDataType type = (VtrDataType)reader->read_ui();

    switch (type) {
        case VtrDataType::Integer: {
            bool is_signed = (bool)reader->read_ui();
            uint32_t width = reader->read_ui();
            ret = m_ctxt->findDataTypeInt(is_signed, width);
        } break;
    }

}

}
}
