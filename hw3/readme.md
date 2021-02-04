* Similar question to q1: [Maximum Subarray - LeetCode](https://leetcode.com/problems/maximum-subarray/)
* For q2, we make use of the data structure of [Trie](https://medium.com/basecs/trying-to-understand-tries-3ec6bede0014)  
  * q2-1: First construct the dictionary Trie and be sure to mark the end of the words. And then to search the Trie by the requests.
  * q2-2: Transform the word into morse code, and search the Trie by the requests. Check whether the request code exists in the trie and whether the request code equals to the trie.
  * q2-3: Construct the trie using the dictionary words, and recursively check the sum of words of the child of the query.(bottom up)
