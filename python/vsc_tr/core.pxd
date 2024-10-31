
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
cimport cpython.ref as cpy_ref

cdef class Factory(object):
    cdef decl.IFactory          *_hndl

    cdef init(self, dmgr_core.Factory)
#    cpdef Context mkContext(self)
    cpdef dmgr_core.DebugMgr getDebugMgr(self)

    cpdef TraceRW mkTraceMem(self)

cdef class TraceRW(object):
    cdef decl.ITraceRW          *_hndl
    cdef bool                   _owned

    @staticmethod
    cdef TraceRW mk(decl.ITraceRW *hndl, bool owned=*)

cdef class Trace(object):
    cdef decl.ITrace            *_hndl

cdef class Stream(object):
    cdef decl.IStream           *_hndl

cdef class StreamWriter(Stream):

    cdef decl.IStreamWriter *asWriter(self)

    cpdef intptr_t addTransaction(
        self,
        uint64_t                tstart,
        uint64_t                tend,
        dm_core.ValRef          val)
