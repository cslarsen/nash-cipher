Background
----------

In 1955, John Nash sent a letter to the NSA, detailing an encryption scheme.
In the letter, he anticipated compelxity theory by a decade, and mentioned
one-way functions (whose existence is still an open problem in mathematics).

Declassification
----------------

The NSA recently declassified the letter, which can be found at:
http://www.nsa.gov/public_info/_files/nash_letters/nash_letters1.pdf

Ronald Rivest (yes, _that_ Rivest), quickly prototyped a version in Python,
and put it up at his course site at MIT:

* Python Code: http://courses.csail.mit.edu/6.857/2012/files/nash.py
* Course site: http://courses.csail.mit.edu/6.857/2012/

Transliteration
---------------

This version is just a transliteration of Rivest's Python code into C++.
And it's not even optimized, either.  But it's should be a nice starting
point for people who want to play with it in C++.

Compiling and running the test
------------------------------

Just type

    $ make clean check

and you should see some output:

    $ make clean check
    rm -f nash
    c++ -W -Wall -g    nash.cpp   -o nash
    ./nash
    Enc: encrypting string bs = [0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1]
    state:  1 [1, 1, 0, 0, 1, 0, 1, 1]
    state:  1 [1, 0, 1, 0, 0, 1, 0, 1]
    state:  1 [1, 1, 1, 1, 1, 0, 0, 0]
    state:  0 [0, 1, 1, 0, 0, 0, 0, 0]
    state:  0 [0, 1, 0, 1, 1, 0, 1, 0]
    state:  1 [1, 0, 0, 0, 0, 1, 1, 1]
    state:  0 [0, 0, 0, 1, 0, 1, 1, 1]
    state:  0 [0, 0, 0, 1, 1, 1, 1, 1]
    state:  0 [0, 0, 1, 0, 1, 1, 0, 1]
    state:  0 [0, 1, 1, 0, 1, 0, 0, 0]
    state:  0 [0, 1, 1, 0, 1, 0, 0, 0]
    state:  1 [1, 0, 0, 0, 0, 0, 1, 1]
    state:  1 [1, 0, 1, 1, 0, 1, 0, 0]
    state:  1 [1, 1, 1, 1, 1, 0, 0, 0]
    Enc: ciphertext string cs = [1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1]
    Dec: decrypting string cs = [1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1]
    state:  1 [1, 1, 0, 0, 1, 0, 1, 1]
    state:  1 [1, 0, 1, 0, 0, 1, 0, 1]
    state:  1 [1, 1, 1, 1, 1, 0, 0, 0]
    state:  0 [0, 1, 1, 0, 0, 0, 0, 0]
    state:  0 [0, 1, 0, 1, 1, 0, 1, 0]
    state:  1 [1, 0, 0, 0, 0, 1, 1, 1]
    state:  0 [0, 0, 0, 1, 0, 1, 1, 1]
    state:  0 [0, 0, 0, 1, 1, 1, 1, 1]
    state:  0 [0, 0, 1, 0, 1, 1, 0, 1]
    state:  0 [0, 1, 1, 0, 1, 0, 0, 0]
    state:  0 [0, 1, 1, 0, 1, 0, 0, 0]
    state:  1 [1, 0, 0, 0, 0, 0, 1, 1]
    state:  1 [1, 0, 1, 1, 0, 1, 0, 0]
    state:  1 [1, 1, 1, 1, 1, 0, 0, 0]
    Dec: plaintext string bs =  [0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1]
    Encryption/decryption successful!

Author and license
------------------

Original Python version by Ronald Rivest

Translated to C++ by Christian Stigen Larsen
http://csl.sublevel3.org

The C++ version is placed in the public domain by the author
2012-02-20
