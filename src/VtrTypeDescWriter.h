/**
 * VtrTypeDescWriter.h
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
#include "vsc/dm/impl/VisitorBase.h"
#include "IVtrWriter.h"

namespace vsc {
namespace tr {

class VtrTraceWriter;

class VtrTypeDescWriter :
    public virtual dm::VisitorBase {
public:
    VtrTypeDescWriter(
        VtrTraceWriter      *trace,
        IVtrWriter          *writer);

    virtual ~VtrTypeDescWriter();

    void write(dm::IDataType *t);

    virtual void visitDataTypeBool(dm::IDataTypeBool *t) override;

    virtual void visitDataTypeInt(dm::IDataTypeInt *t) override;

    virtual void visitDataTypeString(dm::IDataTypeString *t) override;

    virtual void visitDataTypeStruct(dm::IDataTypeStruct *t) override;


protected:
    VtrTraceWriter      *m_trace;
    IVtrWriter          *m_writer;

};

}
}


