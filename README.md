*University project for Quantum Cryptography class.*

# Background
Random number generators are defined by algorithms thus are actually *pseudo-random* number generators. That means that sequences generated by them might include patterns.

This behavior is undesirable in many of the applications of RNGs, including crucial ones as cryptography or communication protocols. 

There are three types of RNGs: Pseudo-random number generators (PRNGs), True random number generators (TRNGs) and Quantum random number generators (QRNGs).

###### PRNGs
PRNGs are based on deterministic algorithms which usually must first be provided a random seed. It is important that the seed is generated by the *real* randomness since the same seed will generate the same sequence for every run. 

###### TRNGs
These random number generators relay on classical physical processes to create random numbers. The randomness is provided by the existence of many uncontrollable degrees of freedom or systems with chaotic behavior. However, it is hard to establish the quality of generated random numbers.

###### QRNGs
QRNGs are based on the quantum property of indeterminacy. It is impossible to predict random numbers produced by these generators.


# Randomness tests
Randomness tests are used to determine whether there is a recognizable pattern in a data set. It is crucial to assure the randomness of an algorithm before it will be used for purposes where security is concerned. These test should also confirm whether the generation process was a quantum one. 

Some standards are insufficient and one can find a PRNG that would pass the test, while some QRNGs would not.

# Project outline
 1. Choose a library to carry out tests
    - [TestU01](http://simul.iro.umontreal.ca/testu01/) library which provides tools for empirical randomness testing of RNGs in C language. **not good parametrization** ([How to Test with TestU01](https://www.pcg-random.org/posts/how-to-test-with-testu01.html))
    - [NIST Test Suite ](https://randomness-tests.fi.muni.cz/)
    - [Diehard Statistical Test Suite](https://github.com/GINARTeam/Diehard-statistical-test)
    - implement a new test described in a recent article
    - implement a brute force test
 2. Analyze influence of testing parameters (enhance the complexity of performed tests, search for more complex, long range patterns in provided data). E.g. find parameters that will detect determinism of a following sequence (one third of the sequence can be predicted based on two previous parts): 
```
s_1 = 100mb from QRNG
s_2 = 100mb from QRNG
s_3 = s_1 XOR s_2 

sequence = s_1.s_2.s_3
```

# Bibliography 
[Wikipedia, *Randomness test*](https://en.wikipedia.org/wiki/Randomness_test)

[Quantum Flagship, *Quantum Random Numbers Generator*](https://qt.eu/discover-quantum/underlying-principles/qrng/)

*missing reference*

[Andrei Khrennikov, *Randomness: quantum versus classical*](https://arxiv.org/abs/1512.08852)

