#!/usr/bin/env python
from setuptools import setup, find_packages, Extension

ghalton_module = Extension("ghalton._ghalton_wrapper",
                           sources=["src/Halton_wrap.cxx", "src/Halton.cpp"],
                           extra_compile_args=["-stdlib=libc++"],
                           extra_link_args=['-stdlib=libc++'])

version = "0.6.2"

# read the contents of README file
from os import path
import codecs
this_directory = path.abspath(path.dirname(__file__))
long_description = codecs.open(path.join(this_directory, 'README.md'), 'r', 'utf-8').read()

setup (name = "ghalton",
       version = version,
       packages=find_packages(),
       author = "Francois-Michel De Rainville",
       author_email = "f.derainville@gmail.com",
       license = "LICENSE.txt",
       description = "Generalized Halton number generator",
       long_description = long_description,
       long_description_content_type="text/markdown",
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
