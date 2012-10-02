#!/usr/bin/env python

from distutils.core import setup, Extension

ghalton_module = Extension("_ghalton", sources=["src/Halton_wrap.cxx", "src/Halton.cpp"])

setup (name = "ghalton",
       version = "0.2",
       author      = "Francois-Michel De Rainville",
       description = "",
       ext_modules = [ghalton_module],
       py_modules = ["ghalton", "primes"],
       )
