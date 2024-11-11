
cimport debug_mgr.decl as dmgr_decl
cimport vsc_dm.decl as dm_decl
from libcpp.pair cimport pair as cpp_pair
from libcpp.set cimport set as cpp_set
from libcpp.string cimport string as cpp_string
from libcpp.vector cimport vector as cpp_vector
from libcpp.memory cimport unique_ptr
from libc.stdint cimport intptr_t
from libc.stdint cimport uintptr_t
from libc.stdint cimport int32_t
from libc.stdint cimport uint32_t
from libc.stdint cimport uint64_t
from libc.stdint cimport int64_t
from libcpp cimport bool
cimport cpython.ref as cpy_ref

ctypedef IFactory *IFactoryP
ctypedef IStreamWriter *IStreamWriterP
ctypedef IStreamReader *IStreamReaderP
ctypedef ITrace *ITraceP
ctypedef ITraceReader *ITraceReaderP
ctypedef ITraceWriter *ITraceWriterP
ctypedef ITraceRW *ITraceRWP
ctypedef unique_ptr[IStreamReader] IStreamReaderUP

#********************************************************************
#* IFactory
#********************************************************************
cdef extern from "vsc/tr/IFactory.h" namespace "vsc::tr":
    cdef cppclass IFactory:
        void init(dmgr_decl.IDebugMgr *)
#        IContext *mkContext()
        ITraceRW *mkTraceMem()
        dmgr_decl.IDebugMgr *getDebugMgr()

cdef extern from "vsc/tr/IStream.h" namespace "vsc::tr":
    cdef cppclass IStream:
        const cpp_string &name() const

cdef extern from "vsc/tr/IStreamReader.h" namespace "vsc::tr":
    cdef cppclass IStreamReader(IStream):
        ITraceIterator *iterator(uint64_t start)
        pass

cdef extern from "vsc/tr/IStreamWriter.h" namespace "vsc::tr":
    cdef cppclass IStreamWriter(IStream):
        intptr_t addTransaction(
            uint64_t                tstart,
            uint64_t                tend,
            const dm_decl.ValRef    &data)

cdef extern from "vsc/tr/ITrace.h" namespace "vsc::tr":
    cdef cppclass ITrace:
        pass

cdef extern from "vsc/tr/ITraceReader.h" namespace "vsc::tr":
    cdef cppclass ITraceReader(ITrace):
        const cpp_vector[IStreamReaderUP] &getStreams() const
        ITraceIterator *iterator(uint64_t start, const cpp_vector[IStreamReaderP] &)

cdef extern from "vsc/tr/ITraceWriter.h" namespace "vsc::tr":
    cdef cppclass ITraceWriter(ITrace):
        IStreamWriter *addStream(const cpp_string &name)

cdef extern from "vsc/tr/ITraceRW.h" namespace "vsc::tr":
    cdef cppclass ITraceRW(ITrace):
        IStreamWriter *addStream(const cpp_string &name)
        const cpp_vector[IStreamReaderUP] &getStreams() const
        ITraceIterator *iterate(uint64_t start, const cpp_vector[IStreamReaderP] &)

cdef extern from "vsc/tr/ITransaction.h" namespace "vsc::tr":
    cdef cppclass ITransaction:
        intptr_t getId()
        uint64_t getTimeStart()
        uint64_t getTimeEnd()
        dm_decl.IValIterator *mkValIterator()

cdef extern from "vsc/tr/ITraceIterator.h" namespace "vsc::tr":
    cdef cppclass ITraceIterator:
        bool valid()
        ITransaction *next()


