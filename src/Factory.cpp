/*
 * Factory.cpp
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
#include "vsc/tr/FactoryExt.h"
#include "Factory.h"
#include "TraceMemRW.h"


namespace vsc {
namespace tr {


Factory::Factory() : m_dmgr(0) {

}

Factory::~Factory() {

}

ITraceRW *Factory::mkTraceMem() {
    return new TraceMemRW(m_dmgr);
}

IFactory *Factory::inst() {
    if (!m_inst) {
        m_inst = std::unique_ptr<Factory>(new Factory());
    }
    return m_inst.get();
}

std::unique_ptr<Factory> Factory::m_inst;

}
}

vsc::tr::IFactory *vsc_tr_getFactory() {
    return vsc::tr::Factory::inst();
}