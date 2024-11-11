
cimport debug_mgr.core as dmgr_core
cimport vsc_dm.core as dm_core
from vsc_tr cimport decl
from libc.stdint cimport intptr_t
from libc.stdint cimport uintptr_t
from libc.stdint cimport int32_t
from libc.stdint cimport uint32_t
from libc.stdint cimport uint64_t
from libc.stdint cimport int64_t
from libcpp cimport bool
from libcpp.vector cimport vector as cpp_vector
from enum import IntFlag, IntEnum
from typing import List
cimport cpython.ref as cpy_ref

cdef class Factory(object):
    cdef decl.IFactory          *_hndl

    cdef init(self, dmgr_core.Factory)
#    cpdef Context mkContext(self)
    cpdef dmgr_core.DebugMgr getDebugMgr(self)

    cpdef TraceRW mkTraceMem(self)



cdef class Stream(object):
    cdef decl.IStream           *_hndl
    cdef bool                   _owned

cdef class StreamReader(Stream):

    cdef decl.IStreamReader *asReader(self)

    cpdef TraceIterator iterator(self, uint64_t start)

    @staticmethod
    cdef StreamReader mk(decl.IStreamReader *hndl, bool owned=*)

cdef class StreamWriter(Stream):

    cdef decl.IStreamWriter *asWriter(self)

    cpdef intptr_t addTransaction(
        self,
        uint64_t                tstart,
        uint64_t                tend,
        dm_core.ValRef          val)

    @staticmethod
    cdef StreamWriter mk(decl.IStreamWriter *hndl, bool owned=*)

cdef class Trace(object):
    cdef decl.ITrace            *_hndl
    cdef bool                   _owned

cdef class TraceIterator(object):
    cdef decl.ITraceIterator    *_hndl
    cdef bool                   _owned

    cpdef bool valid(self)
    cpdef Transaction next(self)

    @staticmethod
    cdef TraceIterator mk(decl.ITraceIterator *hndl, bool owned=*)

cdef class TraceReader(Trace):

    cdef decl.ITraceReader *asReader(self)

    cpdef List[StreamReader] getStreams(self)

    @staticmethod
    cdef TraceReader mk(decl.ITraceReader *hndl, bool owned=*)

cdef class TraceWriter(Trace):

    cdef decl.ITraceWriter *asWriter(self)

    cpdef StreamWriter addStream(self, str name)

    @staticmethod
    cdef TraceWriter mk(decl.ITraceWriter *hndl, bool owned=*)

cdef class TraceRW(object):
    cdef decl.ITraceRW          *_hndl
    cdef bool                   _owned

    cpdef StreamWriter addStream(self, str name)

    cpdef List[StreamReader] getStreams(self)

    cpdef int numStreams(self)

    cpdef StreamReader getStream(self, int idx)

    cpdef TraceIterator iterate(self, uint64_t start, streams)

    @staticmethod
    cdef TraceRW mk(decl.ITraceRW *hndl, bool owned=*)

cdef class Transaction(object):
    cdef decl.ITransaction      *_hndl
    cdef bool                   _owned

    cpdef intptr_t getId(self)
    cpdef uint64_t getTimeStart(self)
    cpdef uint64_t getTimeEnd(self)
    cpdef dm_core.ValIterator mkValIterator(self)

    @staticmethod
    cdef Transaction mk(decl.ITransaction *hndl, bool owned=*)
