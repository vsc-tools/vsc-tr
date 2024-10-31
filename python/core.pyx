
import os
import sys
import ctypes
from enum import IntFlag, IntEnum
from ctypes import CDLL
cimport vsc_tr.decl as decl
cimport vsc_dm.core as dm_core
cimport cpython.ref as cpy_ref
cimport debug_mgr.core as dmgr_core
from libc.stdint cimport intptr_t
from libc.stdint cimport int32_t
from libc.stdint cimport uint32_t
from libc.stdint cimport uint64_t
from libc.stdint cimport int64_t
from libcpp cimport bool
from libcpp.cast cimport dynamic_cast
from libcpp.cast cimport static_cast
from libcpp.cast cimport const_cast
from libcpp.utility cimport move as std_move
from libcpp.vector cimport vector as cpp_vector
from libcpp.memory cimport unique_ptr

#********************************************************************
#* Factory
#********************************************************************
cdef Factory _inst = None
cdef class Factory(object):
    
    def __init__(self):
        pass

    cdef init(self, dmgr_core.Factory f):
        self._hndl.init(f._hndl.getDebugMgr())

    @staticmethod
    def inst():
        cdef decl.IFactory *hndl = NULL
        cdef Factory factory
        global _inst
        if _inst is None:
            ext_dir = os.path.dirname(os.path.abspath(__file__))

            build_dir = os.path.abspath(os.path.join(ext_dir, "../../build"))

            core_lib = None
            libname = "libvsc-tr.so"
            for libdir in ("lib", "lib64"):
                if os.path.isfile(os.path.join(build_dir, libdir, libname)):
                    core_lib = os.path.join(build_dir, libdir, libname)
                    break

            if core_lib is None:
                core_lib = os.path.join(ext_dir, libname)

            if not os.path.isfile(core_lib):
                raise Exception("Extension library core \"%s\" doesn't exist" % core_lib)
            
            so = ctypes.cdll.LoadLibrary(core_lib)
            func = so.vsc_dm_getFactory
            func.restype = ctypes.c_void_p

            hndl = <decl.IFactoryP>(<intptr_t>(func()))
            factory = Factory()
            factory._hndl = hndl
            factory.init(dmgr_core.Factory.inst())
            _inst = factory

        return _inst

    cpdef dmgr_core.DebugMgr getDebugMgr(self):
        return dmgr_core.DebugMgr.mk(self._hndl.getDebugMgr(), False)

    cpdef TraceRW mkTraceMem(self):
        cdef decl.ITraceRW *trace = self._hndl.mkTraceMem()
        return TraceRW.mk(trace, False)

cdef class Stream(object):
    pass

cdef class StreamWriter(Stream):

    cdef decl.IStreamWriter *asWriter(self):
        return dynamic_cast[decl.IStreamWriterP](self._hndl)

    cpdef intptr_t addTransaction(
        self,
        uint64_t            tstart,
        uint64_t            tend,
        dm_core.ValRef      val):
        self.asWriter().addTransaction(
            tstart,
            tend,
            val.val)

cdef class TraceRW(object):

    @staticmethod
    cdef TraceRW mk(decl.ITraceRW *hndl, bool owned=True):
        ret = TraceRW()
        ret._hndl = hndl
        ret._owned = owned