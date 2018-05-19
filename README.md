Anagram Finder
An anagram is a word formed by rearranging the letters of a different word in a different order,
using all the original letters exactly once.
[Here is a dictionary text file](https://github.com/dwyl/english-words/blob/master/words.txt) containing over
400,000 English words, one word per line. Write a program, in a language of your choice, that will
retrieve the file, read its contents, and identify any sets of three or more anagrams in the dictionary.
Your program should print a count of the number of qualifying anagram sets, and optionally write the
anagram sets to an output file as comma-separated lists. Capitalization should be ignored for the purpose
of identifying anagrams.

Solution:
The key idea behind it is to identify an Anagram using the frequency table of 26 letters(Capitalization ignored).
The time complexity of generate such a frequency table for a word is O(M) where M is the maximal length of a word.

Another key issue for this problem is to group the anagram sets efficiently so that we could quickly find an
anagram set for a new word to fit in. Initially I implemented an ordered_map in cpp where its key is sorted with
the frequency table. So the total time complexity is O(N(MlogN+M)). Since the maximal word length of M is bounded,
we could simply write it as O(NlogN).

Then I realized that I could use hash table to further reduce the time spent on fitting a new word into anagram sets.
What I did is to convert the frequency table into a string so that unorderd_map could build a hash table with it. And
the total time complexity is O(N) on average cases. In this case I assume the number of occurencies of any letter in
any word does not surpass 255, which is reasonable.

Then I run:

	source compile.sh
	./anagram_finder words.txt

The result(in seconds) given by my 2016 mackbook pro is:

ordered_map method: 

	time elapsed for anagram sets generation: 1.98391, with 466545 lines processed
	time elapsed for anagram sets output: 0.151343, with 13850 total number of anagram sets

unordered_map method:

	time elapsed for anagram sets generation: 1.29335, with 466545 lines processed
	time elapsed for anagram sets output: 0.144183, with 13850 total number of anagram sets
