/*
 * C++ transliteration of Ronald Rivest's Python implementation of the Nash
 * Cryptosystem, proposed by John Nash in the 1950s.
 *
 * Rivest's Python version can be found at
 * http://courses.csail.mit.edu/6.857/2012/files/nash.py
 *
 * Rivest's version contains some important notes.  This is just a quick
 * translation to UNOPTIMIZED C++, made for the fun of it.
 *
 * Written by Christian Stigen Larsen
 * http://csl.sublevel3.org
 *
 * Placed in the public domain by the author
 * 2012-02-20
 */

#include <cassert>
#include <vector>
#include <iostream>
#include <algorithm>

template<typename word = int>
class bitstring_t : public std::vector<word>
{
public:
  bitstring_t()
  {
  }

  bitstring_t(const word* v, const size_t len)
    : std::vector<word>(&v[0], &v[len])
  {
  }
};

typedef bitstring_t<int> bitstring;

std::ostream& operator<<(std::ostream& s, const bitstring& bs)
{
  s << "[";

  for ( bitstring::const_iterator i = bs.begin();
        i != bs.end(); ++i )
  {
    s << *i << (i+1 != bs.end()? ", " : "");
  }

  return s << "]";
}

class nash_method
{
  size_t n;
  bitstring redp, redbits, bluep, bluebits, P;

public:
  nash_method(size_t _n,
    bitstring redP,
    bitstring redBits,
    bitstring blueP,
    bitstring blueBits,
    bitstring initialP)
  : n(_n),
    redp(redP),
    redbits(redBits),
    bluep(blueP),
    bluebits(blueBits),
    P(initialP)
  {
    assert(n+2 == redp.size());
    assert(n+2 == redbits.size());
    assert(n+2 == bluep.size());
    assert(n+2 == bluebits.size());
    assert(n+2 == P.size());
  }

  /*
   * Advance s for one tick, with input ciphertext bit c.
   */
  void tick(const bool c)
  {
    bitstring& perm = c? redp : bluep,
               bits = c? redbits : bluebits;

    for ( size_t i=0; i<n+2; ++i )
      P[i] = P[perm[i]] ^ bits[i];

    P[0] = c;
    std::cout << "state:  " << c << " " << P << std::endl;
  }

  /*
   * Encrypt bitstring bs, return ciphertext string
   */
  bitstring enc(const bitstring& bs)
  {
    std::cout << "Enc: encrypting string bs = " << bs << std::endl;
    bitstring cs;

    for ( bitstring::const_iterator b = bs.begin();
          b != bs.end();
          ++b )
    {
      bool c = *b ^ P[P.size()-1];
      cs.push_back(c);
      tick(c);
    }

    std::cout << "Enc: ciphertext string cs = " << cs << std::endl;
    return cs;
  }

  /*
   * Decrypt bitstring cs, return ciphertext string
   */
  bitstring dec(const bitstring& cs)
  {
    std::cout << "Dec: decrypting string cs = " << cs << std::endl;
    bitstring bs;

    for ( bitstring::const_iterator c = cs.begin();
          c != cs.end();
          ++c )
    {
      bool b = P[P.size()-1] ^ *c;
      tick(*c);
      bs.push_back(b);
    }

    std::cout << "Dec: plaintext string bs =  " << bs << std::endl;
    return bs;
  }
};

int main()
{
  /*
   * Test example from John Nash's paper
   */

  static int redp[]     = {0, 5, 0, 4, 1, 6, 2, 3};
  static int redbits[]  = {0, 0, 0, 1, 0, 0, 1, 1};
  static int bluep[]    = {0, 6, 4, 2, 0, 1, 3, 5};
  static int bluebits[] = {0, 1, 0, 1, 1, 1, 0, 0};
  static int initialP[] = {0, 1, 1, 0, 1, 1, 0, 1};
  size_t n = sizeof(redp)/sizeof(int) - 2;

  nash_method N1 = nash_method(n,
    bitstring(redp, n+2),
    bitstring(redbits, n+2),
    bitstring(bluep, n+2),
    bitstring(bluebits, n+2),
    bitstring(initialP, n+2));

  // test string to encrypt
  static int test_bs[] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1};
  bitstring bs = bitstring(test_bs, sizeof(test_bs)/sizeof(int));

  // do the encryption, save in cs
  bitstring cs = N1.enc(bs);

  // set up (same) key for decryption
  nash_method N2 = nash_method(n,
    bitstring(redp, n+2),
    bitstring(redbits, n+2),
    bitstring(bluep, n+2),
    bitstring(bluebits, n+2),
    bitstring(initialP, n+2));

  bitstring bs2 = N2.dec(cs);

  // test: results ok?
  if ( bs == bs2 )
    std::cout << "Encryption/decryption successful!" << std::endl;
  else
    std::cout << "Encryption/decryption failed." << std::endl;

  return 0;
}
