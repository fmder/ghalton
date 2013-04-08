
Python Generalized Halton module's documentation
================================================

.. class:: ghalton.GeneralizedHalton(dim[, seed] | config)
	
	Creates a generalized Halton generator. It takes at least one argument,
	either the dimensionality, or a configuration. When the dimensionality is
	given, an optional argument can be used to seed for the random permutations
	created. The configuration is a series of permutations each of *n_i* numbers,
	where *n_i* is the *n_i*'th prime number. In that last case, the
	dimensionality is infered from the number of sublists given.

	:param dim: Dimensionality of the points to create
	:type dim: integer
	:param seed: Seed to create the permutations
	:type seed: integer
	:param config: List of permutations to scramble the halton digits
	:type config: list of lists of integers
	
	.. method:: ghalton.GeneralizedHalton.get(n)
	
	Retreive the *n* next points from this sequence. Each point is a :class:`list` 
	containing each value for each coordinates and the points are returned
	in a :class:`list` of *n* elements even if *n* is 1.
	
	.. method:: ghalton.GeneralizedHalton.reset()
	
	Reset the generator to its initial state, i.e. before it generated the
	first point.
	
	.. method:: ghalton.GeneralizedHalton.seed([config])
	
	Seed the generator with a new seed or configuration. Seeding a generator
	automatically call :meth:`~ghalton.GeneralizedHalton.reset`.
	
	:param config: The config to seed the sequencer
	:type config: :data:`None`, integer, or list of lists of integers

.. class:: ghalton.Halton(dim)

	Creates a Halton generator of dimensionality *dim*. This is similar to
	creating a :class:`~ghalton.GeneralizedHalton` sequence with the identity
	permutations.
	
	.. method:: ghalton.Halton.get(n)
	
	Retreive the *n* next points from this sequence. Each point is a
	:class:`list` containing each value for each coordinates and the points are
	returned in a :class:`list` of *n* elements even if *n* is 1.
	
	.. method:: ghalton.Halton.reset()
	
	Reset the generator to its initial state, i.e. before it generated the
	first point.
	
.. data:: ghalton.EA_PERMS
   
   Permutations described in [DeRainville2012]_ for the 100 first
   dimensions of the Generalized Halton sequence.

.. data:: ghalton.PRIMES
   
   Prime numbers lower than 10000.

.. [DeRainville2012] F.-M. De Rainville, C. Gagné, O. Teytaud, D. Laurendeau. *Evolutionary optimization of low-discrepancy sequences.* ACM Trans. Model. Comput. Simul., 22(2):1-25, 2012.
