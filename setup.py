#!/usr/bin/env python
from setuptools import setup, find_packages, Extension

ghalton_module = Extension("ghalton._ghalton_wrapper", sources=["src/Halton_wrap.cxx", "src/Halton.cpp"])

version = "0.6.1"

setup (name = "ghalton",
       version = version,
       packages=find_packages(),
       author = "Francois-Michel De Rainville",
       author_email = "f.derainville@gmail.com",
       license = "LICENSE.txt",
       description = "Generalized Halton number generator",
       long_description = open("README.md").read(),
       url='https://github.com/fmder/ghalton',
       download_url = "https://github.com/fmder/ghalton/tarball/master#egg=ghalton-%s" % version,
       classifiers=[
        'Development Status :: 4 - Beta',
        'Intended Audience :: Developers',
        'Intended Audience :: Education',
        'Intended Audience :: Science/Research',
        'License :: OSI Approved :: GNU Library or Lesser General Public License (LGPL)',
        'Topic :: Scientific/Engineering',
        ],
       ext_modules = [ghalton_module],
       )
