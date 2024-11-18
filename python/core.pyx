
import os
import sys
import ctypes
from enum import IntFlag, IntEnum
from ctypes import CDLL
cimport vsc_tr.decl as decl
cimport vsc_dm.core as dm_core
cimport vsc_dm.decl as dm_decl
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
            func = so.vsc_tr_getFactory
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

    cpdef TraceWriter mkTraceVtrWriter(self,
        costream        out,
        int32_t         timescale,
        int32_t         timeunit):
        cdef decl.ITraceWriter *writer = self._hndl.mkTraceVtrWriter(
            out._hndl,
            timescale,
            timeunit)

        return TraceWriter.mk(writer, True)


cdef class Stream(object):
    pass

cdef class StreamReader(Stream):

    cdef decl.IStreamReader *asReader(self):
        return dynamic_cast[decl.IStreamReaderP](self._hndl)

    cpdef TraceIterator iterator(self, uint64_t start):
        cdef decl.ITraceIterator *it = self.asReader().iterator(start)
        if it == NULL:
            return None
        else:
            return TraceIterator.mk(it, True)

    @staticmethod
    cdef StreamReader mk(decl.IStreamReader *hndl, bool owned=True):
        ret = StreamReader()
        ret._hndl = hndl
        ret._owned = owned
        return ret

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

    @staticmethod
    cdef StreamWriter mk(decl.IStreamWriter *hndl, bool owned=True):
        ret = StreamWriter()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class Trace(object):
    pass

class TraceIteratorProxy(object):
    def __init__(self, it):
        self._it = it
        
    def __next__(self):
        if (self._it.valid()):
            return self._it.next()
        else:
            raise StopIteration()

cdef class TraceIterator(object):

    def __dealloc__(self):
        if self._owned and self._hndl != NULL:
            del self._hndl
            self._hndl = NULL

    def __iter__(self):
        return TraceIteratorProxy(self)

    cpdef bool valid(self):
        return self._hndl.valid()

    cpdef Transaction next(self):
        cdef decl.ITransaction *t = self._hndl.next()
        if t == NULL:
            return None
        else:
            return Transaction.mk(t, False)

    @staticmethod
    cdef TraceIterator mk(decl.ITraceIterator *hndl, bool owned=True):
        ret = TraceIterator()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TraceReader(Trace):

    cdef decl.ITraceReader *asReader(self):
        return dynamic_cast[decl.ITraceReaderP](self._hndl)

    cpdef List[StreamReader] getStreams(self):
        cdef const cpp_vector[decl.IStreamReaderUP] *stream_l
        ret = []
        stream_l = &self.asReader().getStreams()

        for i in range(stream_l.size()):
            ret.append(StreamReader.mk(stream_l.at(i).get(), False))

        return ret

    @staticmethod
    cdef TraceReader mk(decl.ITraceReader *hndl, bool owned=True):
        ret = TraceReader()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TraceWriter(Trace):

    cdef decl.ITraceWriter *asWriter(self):
        return dynamic_cast[decl.ITraceWriterP](self._hndl)

    cpdef StreamWriter addStream(self, str name):
        cdef decl.IStreamWriter *stream = self.asWriter().addStream(name.encode())
        return StreamWriter.mk(stream, False)

    @staticmethod
    cdef TraceWriter mk(decl.ITraceWriter *hndl, bool owned=True):
        ret = TraceWriter()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TraceRW(object):

    cpdef StreamWriter addStream(self, str name):
        cdef decl.IStreamWriter *stream = self._hndl.addStream(name.encode())
        return StreamWriter.mk(stream, False)

    cpdef List[StreamReader] getStreams(self):
        cdef const cpp_vector[decl.IStreamReaderUP] *stream_l
        ret = []
        stream_l = &self._hndl.getStreams()

        for i in range(stream_l.size()):
            ret.append(StreamReader.mk(stream_l.at(i).get(), False))

        return ret

    cpdef int numStreams(self):
        return self._hndl.getStreams().size()

    cpdef StreamReader getStream(self, int idx):
        cdef decl.IStreamReader *stream = self._hndl.getStreams().at(idx).get()
        return StreamReader.mk(stream, False)

    cpdef TraceIterator iterate(self, uint64_t start, streams):
        cdef cpp_vector[decl.IStreamReaderP] streams_v
        cdef StreamReader stream_r
        cdef decl.ITraceIterator *it

        for stream in streams:
            stream_r = <StreamReader>stream
            streams_v.push_back(stream_r.asReader())

        it = self._hndl.iterate(start, streams_v)

        if it == NULL:
            return None
        else: 
            return TraceIterator.mk(it, True)

    @staticmethod
    cdef TraceRW mk(decl.ITraceRW *hndl, bool owned=True):
        ret = TraceRW()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class Transaction(object):

    cpdef intptr_t getId(self):
        return self._hndl.getId()

    cpdef uint64_t getTimeStart(self):
        return self._hndl.getTimeStart()

    cpdef uint64_t getTimeEnd(self):
        return self._hndl.getTimeEnd()

    cpdef dm_core.ValIterator mkValIterator(self):
        cdef dm_decl.IValIterator *it = self._hndl.mkValIterator()
        if it == NULL:
            return None
        else:
            return dm_core.ValIterator.mk(it, True)

    @staticmethod
    cdef Transaction mk(decl.ITransaction *hndl, bool owned=True):
        ret = Transaction()
        ret._hndl = hndl
        ret._owned = owned
        return ret
