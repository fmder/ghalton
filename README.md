Generalized Halton Number Generator
===================================

This library allows to generate quasi-random numbers according to the
generalized Halton sequence. For more information on Generalized Halton
Sequences, their properties, and limits see Braaten and Weller (1979), Faure
and Lemieux (2009), and De Rainville et al. (2012) and reference therein.

The library is compatible Python 2 and Python 3.

Install with `pip`
------------------
Simply type in

    $ pip install ghalton


Building the Code
-----------------
To build the code you'll need a working C++ compiler. 

    $ python setup.py install

Using the Library
-----------------
The library contains two generators one producing the standard Halton sequence
and the other a generalized version of it. The former constructor takes a
single argument, which is the dimensionalty of the sequence.

    import ghalton
    sequencer = ghalton.Halton(5)

The last code will produce a sequence in five dimension. To get the points use

    points = sequencer.get(100)

A list of 100 lists will be produced, each sub list will containt 5 points

    print(points[0])
    # [0.5, 0.3333, 0.2, 0.1429, 0.0909]

The halton sequence produce points in sequence, to reset it call
`sequencer.reset()`.

The generalised Halton sequence constructor takes at least one argument,
either the dimensionality, or a configuration. When the dimensionality is
given, an optional argument can be used to seed for the random permutations
created.

    import ghalton
    sequencer = ghalton.GeneralizedHalton(5, 68)
    points = sequencer.get(100)
    print(points[0])
    # [0.5, 0.6667, 0.4, 0.8571, 0.7273]

A configuration is a series of permutations each of *n_i* numbers,
where *n_i* is the *n_i*'th prime number. The dimensionality is infered from
the number of sublists given.

    import ghalton
    perms = ((0, 1),
             (0, 2, 1),
             (0, 4, 2, 3, 1),
             (0, 6, 5, 4, 3, 2, 1),
             (0, 8, 2, 10, 4, 9, 5, 6, 1, 7, 3))
    sequencer = ghalton.GeneralizedHalton(perms)
    points = sequencer.get(100)
    print(points[0])
    # [0.5, 0.6667, 0.8, 0.8571, 0.7273]

The configuration presented in De Rainville et al. (2012) is available in the
ghalton module. Use the first *dim* dimensions of the `EA_PERMS` constant.
The maximum dimensionality provided is 100.

    import ghalton
    dim = 5
    sequencer = ghalton.GeneralizedHalton(ghalton.EA_PERMS[:dim])
    points = sequencer.get(100)
    print(points[0])
    # [0.5, 0.6667, 0.8, 0.8571, 0.7273]

The complete API is presented [here](http://vision.gel.ulaval.ca/~fmdrainville/doc/python/index.html).

Configuration Repository
------------------------
See the [Quasi Random Sequences Repository](http://qrand.gel.ulaval.ca) for more configurations. 

References
----------
E. Braaten and G. Weller. An improved low-discrepancy sequence for multidi-
mensional quasi-Monte Carlo integration. *J. of Comput. Phys.*,
33(2):249-258, 1979.

F.-M. De Rainville, C. Gagné, O. Teytaud, D. Laurendeau. Evolutionary
optimization of low-discrepancy sequences. *ACM Trans. Model. Comput. Simul.*,
22(2):1-25, 2012.

H. Faure and C. Lemieux. Generalized Halton sequences in 2008: A comparative
study. *ACM Trans. Model. Comput. Simul.*, 19(4):1-43, 2009.
