/**
 *    author:  Allen Yuan
 *    created: 8/16/2019
 *
 *    Official problem statement and editorial at http://acmicpc-pacnw.org/results.htm
 *
 *    Problem: Given n problems each with an integer difficulty and k problems to set on a contest,
 *    output the number of distinct valid contests, where a valid contest is a set of k problems
 *    each with a different difficulty.
 *
 *    Input:  two ints n, k on a single line, followed by n ints representing the problem difficulties.
 *    Output: the answer as an integer on a single line
 *
 *    Solution: Dynamic programming. We do recursion on the number of difficulty classes. First map
 *    each difficulty class to how many questions have this difficulty. Now define f[i][j] = # contests
 *    with first i difficulty classes and j questions.
 *
 *    We obtain f[i+1] from f[i] as follows. Note we f[i+1][j+1] += f[i][j+1]
 *
 *    The below code contains this logic.
**/

#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

int main()
{
  // stream in n (# of problems created) and k (# of problems in contest)
  int n, k;
  cin >> n >> k;

  // map difficulty to frequency of this difficulty
  map<int, int> counts;
  for (int i = 0; i < n; i++)
  {
    int difficulty;
    cin >> difficulty;
    counts[difficulty]++;
  }

  // dynamic programming: recurrence on # of difficulty classes
  // res[i] = # contests with i problems, where each iteration considers 1 additional difficulty class
  // we seek res[k].
  vector<int> res;
  // there is only 1 0-problem contest: empty set
  res.push_back(1);

  // for each (difficulty, frequency) pair in counts
  for (auto p : counts)
  {
    // let res2 be a copy of res with a 0 at the end
    vector<int> res2(res.begin(), res.end());
    res2.push_back(0);

    // recurrence: ignore new difficulty class => += res[i+1].
    // use new difficulty class to populate additional question
    // => += p.second*res[i].
    for (int i = 0; i < (int)res.size(); i++)
    {
      res2[i + 1] = (res[i + 1] + p.second * res[i]) % MOD;
    }
    res = res2;
  }

  // not enough difficulties => 0. Otherwise res[k].
  cout << (k < (int)res.size() ? res[k] : 0) << endl;
}
