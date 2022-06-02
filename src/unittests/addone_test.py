import sys
import os

# Append main directory
sys.path.insert(1, os.path.join(sys.path[0], ".."))

from scripts.test_functions import add_one, subtract_one, divide_one, multiply_one

import unittest


class MathTests(unittest.TestCase):
    def test_add_one(self):
        self.assertEqual(add_one(1), 2)

    def test_subtract_one(self):
        self.assertEqual(subtract_one(155), 154)

    def test_multiply_one(self):
        self.assertEqual(multiply_one(1337), 1337)

    def test_divide_one(self):
        self.assertEqual(divide_one(31), 31)


"""
This file contains various toy test cases for testing out dagger.io
"""
if __name__ == "__main__":
    unittest.main()  # pragma: no cover
