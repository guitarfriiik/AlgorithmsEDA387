1. Digital Clock Synchronization (Unbounded)
	upon a pulse 
	     for all Pj <- N(i) do send (j, clock_i)
	     max := clock_i
	     forall Pj <- N(i) do
	     	    recieve(clock_j)
		    if clockj > max then max := clock_j
	     od
	     clock_i := max + 1

        Proof of correctness: The correctness of the algorithm is proved by an induction of
	       the distance from Pm, where Pm is the processor with the maximum
	       clock value.

2. Digital Clock Synchronization (Bounded I)
	upon a pulse 
	     for all Pj <- N(i) do send (j, clock_i)
	     max := clock_i
	     forall Pj <- N(i) do
	     	    recieve(clock_j)
		    if clockj > max then max := clock_j
	     od
	     clock_i := (max +1) mod ((n+1)d + 1)

        Proof of correctness (convergence?!): First, M > (n+1)d where n is the number of processors and d 
	      	 	      the diameter of the network. If the system is initialized in
			      a configuration in which all values are less than M -d, the clocks
			      are synchronized before the modulo is applied. Once they are
			      zero is assigned to the clocks simultaneously after the C in which
			      all values = M -1. According to the pigeon hole principle there
			      are always two clock values x and y such that y-x >= d + 1 and there
			      is no clock value between. Since each processor choses an existing value
			      and increase it by one, there are no values greater than x+1 and smaller
			      than y+1. Thus, after M-y+1 pulses the system reaces a C in which there
			      is no clock pulse which is greater than M-d. In the next d rounds the 
			      maximum clock value propagates and the system reaches a state in
			      which all the clocks are synchronized. 

2. Digital Clock Synchronization (Bounded II)
	upon a pulse 
	     for all Pj <- N(i) do send (j, clock_i)
	     max := clock_i
	     forall Pj <- N(i) do
	     	    recieve(clock_j)
		    if clockj > max then max := clock_j
	     od
	     clock_i := (min+1) mod (2d + 1)

        Proof of correctness(convergence?): Two cases are considered. First if no processor assigns zero to its clock the
	      	 	      first d rounds. An induction on the distance proves that all processors has the
			      minimum value after the following i <= d pulses. In the other case, one processor
			      assigns 0 during the first d pulses, all processors will have no value greater than
			      d in the first d pulses. In the following d pulses no processor assigns zero to 
			      its clock and the first case is applies. 

********************************************************************************************************************


3. Self Stabilizing Maximal Matching
   The maximal matching algorithm should reach a c in which Pi points to Pj and there are no
   neighboring processors which both have null pointers.

   do forever
      if pointer_i = null and (there exists Pj in N(i) pointer_j = i) then
      	 pointer_i = j
      if pointer_I = null and (all Pj in N(i) pointer_j != i) and (there exists Pj in N(i) which pointer = NULL)
      	 pointer_i = j
      if pointer_j = j and pointer_j = k and j != i then
         pointer_j := null
   od

    The proof uses the variant function. Controlled by a central daemon so first Pi then Pj etc..
    A processor in configuration Cl has the following states:
      *matched(m) - if processor Pi points to Pj and processor Pj points to Pi.
      *single(s) - if processor Pi's pointer is null and all neighbors of Pi is matched
      *waiting(w) - if Pi has a neighbor which pointer is null and Pi points to Pj
      *free(f) - if Pi has a null pointer and there exist a Pj which is not matched
      *chaining(c) - if there exists a neighbor Pj for which pointer_i = j and pointer_j = k!=j.
    The variant function returns a vector of (m+s,w,f,c). The values of the vector are compared lexiographically.
    A safe configuration is a configuration in which (n,0,0,0) which is the largest vector. A safe configuration is
    reached within O(n^3) rounds. Once the system reaches a safe configuration no processor changes its pointer. 
    It must be prooved that all pointer changes increments the value of the variant function. 
    
    Line 3 increments the number of matched processors by 2 and decreases the number of free and 
    waiting processors by one respectively.
    
    An assignment in line 6 increases the number of waiting processors by one and reduces the number of free processors by one.
    
    Two cases needs to be considered for the assignment of line 8. First no neighboring processors points to Pi. Then
    processor Pi changes status to free if there exist an unmatched neigbor otherwise single. Therefor the number of chained
    processors is reduced by one and the number of free or single processors increased by one. 
    In the other case, a neighboring processor points to Pi and therefor the status of that processor is changed from chaining
    to waiting and the status of Pi is changed to free which results in a decrease of two in for the chained processors. Thus,
    each of the above assignments increases the variant function.


**********************************************************************************************************************