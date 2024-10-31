from .test_base import TestBase

class TestMemTrace(TestBase):
    
    def test_smoke(self):
        trace = self.tr_f.mkTraceMem()
        s1 = trace.addStream("s1")
        streams = trace.getStreams()
        self.assertEqual(len(streams), 1)
        pass