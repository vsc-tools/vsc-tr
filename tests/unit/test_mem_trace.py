
import vsc_dm.core as vsc_dm
import vsc_dataclasses as vdc
from .test_base import TestBase

class TestMemTrace(TestBase):
    
    def test_smoke(self):

        @vdc.randclass
        class transaction(object):
            a : vdc.uint32_t
            b : vdc.uint32_t
        

        trace = self.tr_f.mkTraceMem()
        s1 = trace.addStream("s1")
        streams = trace.getStreams()
        self.assertEqual(len(streams), 1)

        vsc_dm_f = vsc_dm.Factory.inst()
        ctx = vsc_dm_f.mkContext()

        s_t = ctx.mkDataTypeStruct("S")
        i_t = ctx.findDataTypeInt(False, 32)
        s_t.addField(ctx.mkTypeFieldPhy("a", i_t, False, 0, None))
        s_t.addField(ctx.mkTypeFieldPhy("b", i_t, False, 0, None))


#        val_it = val.iterator()
#        print("numFields: %d" % val_it.numFields())
#        print("Field[0]: %s" % val_it.getFieldName(0))
#        print("Field[1]: %s" % val_it.getFieldName(1))

        for i in range(16):
            print("i: %d" % i)
            val = ctx.mkValRefStruct(s_t)
            s1.addTransaction(i, i+10, val)

        s1_r = trace.getStream(0)
        t_it = s1_r.iterator(4)

        while t_it.valid():
            t = t_it.next()
            print("%d..%d" % (t.getTimeStart(), t.getTimeEnd()))

        # filter expected to yield bool
        # map expected to yield a value or a transaction
        # 

        pass