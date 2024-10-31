
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

    @staticmethod
    cdef TraceRW mk(decl.ITraceRW *hndl, bool owned=*)

