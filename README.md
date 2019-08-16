# Allen-Yuan-ICPC-Regionals
Allen Yuan's C++ solutions to International Collegiate Programming Competition (ICPC) Regionals questions. Contains full comments and problem statements.

Work in progress to clean up, write editorials, and write inline comments.

# How to use
Click the folder with the contest you are interested in and see my solution w/ problem statement and comments all in the corresponding cpp file.

# Sample: Count the Bits
```
/**
 *    author:  Allen Yuan
 *    created: 8/15/2019
 *
 *    Official problem statement and editorial at http://acmicpc-pacnw.org/results.htm
 *    Problem: Given ints k and b, return the number of 1-bits in multiplies of k within the range
 *    [0, 2^b-1], mod 1,000,000,009
 *    Input:  two ints k, b on a single line
 *    Output: the answer as an integer on a single line
 *
 *    Solution: Dynamic programming. The question is asking for # of 1-bits in multiples of k
 *    having bitlength b. We build the solution up from bitlength 0 by considering the effect
 *    as we prepend a 0 or a 1.
 *
 *    Define f[i][j] = number of 1-bits amongst numbers of bitlength i in the residue class j,
 *    modulo k. Define c[i][j] = count of numbers of bitlength i in the residue class j. We
 *    aim to find f[b][0].
 *
 *    Base case: f[0][j] = 0, c[0][0] = 1 and c[0][j] = 0 otherwise.
 *    Recurrence: Prepending a 0 does nothing to the number, so c[i+1][j] += c[i][j] and
 *    f[i+1][j] += f[i][j]. Prepending a 1 adds 2^i to the number so let offset = j - 2^i mod k
 *    be the inverse of j under this operation and let c[i+1][j] += c[i][offset] and
 *    f[i+1][j] += c[i][offset]. Finally consider that after prepending a 1, each
 *    number of c[i][offset] contributes a new 1 to f[i+1][j] so let f[i+1][j] += c[i][offset].
 *
 *    The below code contains this logic.
**/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll MOD = 1'000'000'009;

int main() {
  // stream in k and b
  int k;
  int b;
  cin >> k >> b;
  // init bit count and num count per residue class
  vector<int> bit_count(k);
  vector<int> num_count(k);
  // base case: our convention is that 0 is the only 0 bitlength number.
  // certainly 0 is congruent to 0 mod k.
  num_count[0] = 1;
  // the additive inverse of 2^i mod k where i is the bitlength (0 indexed)
  int inverse = k - 1;
  for (int i = 0; i < b; i++) {
    // initialize new bit count and num count
    vector<int> new_bit_count(k);
    vector<int> new_num_count(k);
    // for each remainder j mod k, consider appending bits from left.
    for (int j = 0; j < k; j++) {
      // prej = the preimage of j under prepending a 1
      // prepending a 1 is equivalent to adding 2^i so to invert this we
      // add inverse = -2^i mod k
      int prej = (j + inverse) % k;
      new_num_count[j] = (num_count[j] + num_count[prej]) % MOD;
      new_bit_count[j] = (bit_count[j] + bit_count[prej] + num_count[prej]) % MOD;
    }
    // update bitcount and numcount
    bit_count = new_bit_count;
    num_count = new_num_count;
    // update the inverse
    inverse = 2*inverse % k;
  }
  cout << bit_count[0] << endl;
  return 0;
}
```
