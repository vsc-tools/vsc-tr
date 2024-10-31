import os
import sys
import unittest

tests_unit_dir = os.path.dirname(os.path.abspath(__file__))
vsc_tr_dir = os.path.abspath(os.path.join(tests_unit_dir, "../.."))
sys.path.insert(0, os.path.join(vsc_tr_dir, "python"))

class TestBase(unittest.TestCase):

    def setUp(self):
        import vsc_tr.core as vsc_tr
        self.tr_f = vsc_tr.Factory.inst()
        return super().setUp()
    pass
