Generalized Halton Number Generator
===================================

This library allows to generate quasi-random numbers according to the
generalized Halton sequence. For more information on Generalized Halton
Sequences, their properties and limits, see Braaten and Weller (1979), Faure
and Lemieux (2009), and De Rainville et al. (2012) and reference therein.


Building The Code
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

    print points[0]
    # [0.5, 0.3333, 0.2, 0.1429, 0.0909]

The halton sequence produce points in sequence, to reset it call
`sequencer.reset()`.

The generalised Halton sequence constructor takes one mendatory argument, the
dimensionality, and one optional argument, which defines either the seed of
the sequencer or the configuration.

    import ghalton
    sequencer = ghalton.GeneralizedHalton(5, 68)
    points = sequencer.get(100)
    print points[0]
    # [0.5, 0.6667, 0.2, 0.8571, 0.6364]

A configuration is a flattened series of permutations each of *n_i* numbers,
where *n_i* is the *n_i*'th prime number.

    import ghalton
    perms = (0, 1,
             0, 2, 1,
             0, 4, 2, 3, 1,
             0, 6, 5, 4, 3, 2, 1,
             0, 8, 2, 10, 4, 9, 5, 6, 1, 7, 3)
    sequencer = ghalton.GeneralizedHalton(5, perms)
    points = sequencer.get(100)
    print points[0]
    # [0.5, 0.6667, 0.8, 0.8571, 0.7273]

The configuration presented in De Rainville et al. (2012) is available in the
ghalton module. Sum the *dim* first prime numbers to know how many numbers from the permutations are required
and use them as the configuration argument. The maximum dimensionality for that sequence is 100.

    import ghalton
    dim = 5
    n = sum(ghalton.PRIMES[:dim])
    sequencer = ghalton.GeneralizedHalton(5, ghalton.EA_PERMS[:n])
    points = sequencer.get(100)
    print points[0]
    # [0.5, 0.6667, 0.8, 0.8571, 0.7273]

The complete API is presented [here](http://vision.gel.ulaval.ca/~fmdrainville/doc/python/index.html).

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
