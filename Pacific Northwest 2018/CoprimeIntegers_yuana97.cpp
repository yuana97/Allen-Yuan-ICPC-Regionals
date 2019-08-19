/**
 *    author:  Allen Yuan
 *    created: 8/19/2019
 *
 *    Official problem statement and editorial at http://acmicpc-pacnw.org/results.htm
 *
 *    Problem: Given [a, b] and [c, d] return the number of (x, y) with x in [a, b] and y in [c, d] such that x, y are coprime.
 *
 *    Input:  a b c d (a, b, c, d <= 10^7)
 *    Output: the answer as an integer on a single line
 *
 *    Solution: Inclusion exclusion: For each prime p, remove all pairs divisible by p, add back all pairs divisible by the product of
 *    2 primes pq, subtract out all pairs divisible by the product of 3 primes, etc. Number of pairs divisible
 *    by k in given constraints is (floor(b/k) - floor((a-1)/k))(floor(d/k) - floor((c-1)/k)).
 *
 *    To program this, use recursion on including another prime to the product. Generate the
 *    all primes <= min(b, d) with a sieve.
 *
 *    The below code contains this logic.
**/

#include <iostream>
#include <vector>

using namespace std;

// incex(at, prod, par) returns the contribution from appending the (at-1)th prime to
// the product.
// at is current index + 1. prod is current product of distinct primes, par is 1 if
// we are adding, -1 if we are subtracting, p is the list of primes, a, b, c, d are
// the givens.
int incex(int at, int prod, int par, const vector<int> &p, int a, int b, int c, int d)
{
  // number of pairs divisible by prod
  int r = par * (b / prod - a / prod) * (d / prod - c / prod);

  // lim = max size prime we need to look at (multiplying by > lim will go over
  // an upper bound so we don't need to look over lim)
  int lim = min(b, d) / prod;

  // for each prime bigger than current, try including it.
  for (int i = at; i < p.size() && p[i] <= lim; i++)
    r += incex(i + 1, prod * p[i], -par, p, a, b, c, d);

  return r;
}

int main()
{
  // stream in a, b, c, d. set hi = min(b,d) as we don't need to look at
  // any primes > hi.
  int A, B, C, D;
  cin >> A >> B >> C >> D;
  int HI{min(B, D)};

  // init primes and sieve sf. sf[i] = 0 => not sieved, sf[i] = 1 => sieved out
  vector<int> primes;
  vector<char> sf(HI + 1);
  primes.push_back(2);

  // sieve of eratosthenes
  // for each number in [3, HI]
  for (int i = 3; i <= HI; i += 2)
    // not sieved => prime
    if (sf[i] == 0)
    {
      // push to primes and mark sf[i].
      primes.push_back(i);
      sf[i] = 1;
      // it suffices to mark numbers starting from i^2 as all previous composite numbers
      // have been sieved by a smaller prime.
      if (HI / i >= i)
        // go in increments of 2i because odd increments are even therefore redundant.
        for (int j = i * i; j <= HI; j += 2 * i)
          sf[j] = 1;
    }

  // print incex on p[0,...,end] starting with product 1, adding.
  cout << incex(0, 1, 1, primes, A - 1, B, C - 1, D) << endl;
}
