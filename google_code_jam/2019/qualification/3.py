#Problem
#On the Code Jam team, we enjoy sending each other pangrams, which are phrases that use each letter of the English alphabet at least once. One common example of a pangram is "the quick brown fox jumps over the lazy dog". Sometimes our pangrams contain confidential information — for example, CJ QUIZ: KNOW BEVY OF DP FLUX ALGORITHMS — so we need to keep them secure.

#We looked through a cryptography textbook for a few minutes, and we learned that it is very hard to factor products of two large prime numbers, so we devised an encryption scheme based on that fact. First, we made some preparations:

#We chose 26 different prime numbers, none of which is larger than some integer N.
#We sorted those primes in increasing order. Then, we assigned the smallest prime to the letter A, the second smallest prime to the letter B, and so on.
#Everyone on the team memorized this list.
#Now, whenever we want to send a pangram as a message, we first remove all spacing to form a plaintext message. Then we write down the product of the prime for the first letter of the plaintext and the prime for the second letter of the plaintext. Then we write down the product of the primes for the second and third plaintext letters, and so on, ending with the product of the primes for the next-to-last and last plaintext letters. This new list of values is our ciphertext. The number of values is one smaller than the number of characters in the plaintext message.

#For example, suppose that N = 103 and we chose to use the first 26 odd prime numbers, because we worry that it is too easy to factor even numbers. Then A = 3, B = 5, C = 7, D = 11, and so on, up to Z = 103. Also suppose that we want to encrypt the CJ QUIZ... pangram above, so our plaintext is CJQUIZKNOWBEVYOFDPFLUXALGORITHMS. Then the first value in our ciphertext is 7 (the prime for C) times 31 (the prime for J) = 217; the next value is 1891, and so on, ending with 3053.

#We will give you a ciphertext message and the value of N that we used. We will not tell you which primes we used, or how to decrypt the ciphertext. Do you think you can recover the plaintext anyway?

#Input
#The first line of the input gives the number of test cases, T. T test cases follow; each test case consists of two lines. The first line contains two integers: N, as described above, and L, the length of the list of values in the ciphertext. The second line contains L integers: the list of values in the ciphertext.

#Output
#For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is a string of L + 1 uppercase English alphabet letters: the plaintext.

#Limits
#1 ≤ T ≤ 100.
#Time limit: 20 seconds per test set.
#Memory limit: 1 GB.
#25 ≤ L ≤ 100.
#The plaintext contains each English alphabet letter at least once.

#Test set 1 (Visible)
#101 ≤ N ≤ 10000.

#Test set 2 (Hidden)
#101 ≤ N ≤ 10100.

#Sample

#Input

#2
#103 31
#217 1891 4819 2291 2987 3811 1739 2491 4717 445 65 1079 8383 5353 901 187 649 1003 697 3239 7663 291 123 779 1007 3551 1943 2117 1679 989 3053
#10000 25
#3292937 175597 18779 50429 375469 1651121 2102 3722 2376497 611683 489059 2328901 3150061 829981 421301 76409 38477 291931 730241 959821 1664197 3057407 4267589 4729181 5335543




#Output

#Case #1: CJQUIZKNOWBEVYOFDPFLUXALGORITHMS
#Case #2: SUBDERMATOGLYPHICFJKNQVWXZ

#Analysis
#Yeah, but what about decrypting?
#The statement tells us how the plaintext is encrypted, but it says nothing about the decryption mechanism! Figuring that out is part of the problem. Since this is a Qualification Round problem, there is slightly less time pressure and competitive urgency, and you have some extra time to think about how this cryptosystem is supposed to be used.

#Suppose that Cameron and Jamie are members of the Code Jam team who know the secret list of 26 primes, and suppose that Cameron has just sent the ciphertext to Jamie. Each value in the ciphertext is the product of two of those primes, so Jamie can try dividing each value by each known prime to find the value's factors. (Notice that a value in the ciphertext might be the square of a prime, if the plaintext has the same letter twice in a row.)

#After getting the list of factored ciphertext values, how should Jamie recover the plaintext? We might be tempted to say that the second letter of the plaintext is the one whose prime appears as factors of both the first and second ciphertext values, the third letter is the one whose prime appears as factors of both the second and third ciphertext values, and so on. Then the remaining factors in the first and last ciphertext values give us the first and last letters of the plaintext.

#This is almost correct, but we (and Jamie) would have to deal with one significant annoyance. If the plaintext starts with something like ABABA..., for example, then the first, second, third, and fourth ciphertext values will all be the same, being the product of the same two factors (the primes corresponding to A and B). In particular, the start of BABAB... looks just the same as the start of ABABA...! The good news is that we know that this kind of pattern must terminate somewhere in the message; eventually, either we will get the same letter twice in a row, or (since the plaintext uses more than two different letters) three consecutive different letters. As soon as either of these things happens, we have a "break-in point", and we know which factors of a particular ciphertext value go with which of the two letters of the plaintext that it encodes. Then, we can "unzip" the rest of the plaintext from there, working backwards and forwards.

#For instance, if the plaintext starts with ABABAABAB, the first four ciphertext values will all be the same: the product of the prime corresponding to A and the prime corresponding to B. The fifth ciphertext value will represent the square of A, so we will know that the fifth and sixth plaintext letters are both A. We can then reason that the fourth plaintext letter must be the fourth ciphertext value divided by the prime corresponding to A, the third plaintext letter must be the third ciphertext value divided by the prime corresponding to B, and so on going backwards. We can also determine that the seventh plaintext letter is the sixth ciphertext value divided by the prime corresponding to A, and so on going forwards.

#Similarly, if the plaintext starts with ABABCBABA, when we inspect the third and fourth ciphertext values, we will see that they are different, but both have the prime corresponding to B as a factor. Then we can unzip from there, as above.

#However, we must remember that Jamie has an advantage that we do not have: we do not know the 26 secret primes! We need to find a way to get them.

#Test set 1
#In test set 1, the ciphertext values are products of small primes. Each prime is less than 104, so each ciphertext value is no larger than 108. It is straightforward to factor these values by testing every possible (prime) factor between 2 and 104. Once we have all of the factors, we will have our set of 26 primes, since each prime will be represented in at least one factor of one ciphertext value. We can assign them in increasing order to the letters A through Z.

#Then, to recover the plaintext, we can use a bit of brute force to sidestep the need to unzip as described before. Consider the two factors that contribute to the first ciphertext value; arbitrarily choose one of them. Let us first assume that that factor corresponds to the first letter of the plaintext, and the other corresponds to the second. Then we can take the remaining factor and try to divide the second ciphertext value by that factor. If we cannot, we have a contradiction, and we should go back and make the other factor correspond to the first letter of the plaintext. Otherwise, the quotient is the factor corresponding to the third letter of the plaintext, and so on. For one of our choices, this method will work and will give us the correct plaintext; for the other choice, we will reach a contradiction, since (as described above) it is guaranteed that there is only one possible decryption.

#Test set 2
#In test set 2, the primes can be enormous (as large as a googol), and the product of two such primes can be even more enormous. We should realize that it is hopeless to try to factor such a product. If we could do that, we could also break modern cryptosystems that depend on the assumption that factoring large numbers is intractable! The Code Jam servers do not run on quantum computers (yet...), so there is no way for us to try to use a quantum algorithm, either.

#To solve this seemingly impossible test set, we need to find a different vulnerability of this cryptosystem. The key insight is that any two consecutive values in the ciphertext have at least one factor in common. Factoring very large numbers may be intractable, but we do know how to efficiently find the greatest common divisor of two very large numbers! A method like Euclid's algorithm will be fast enough.

#Notice that if we have a plaintext like ABABC..., it is possible that the prime corresponding to A will not appear in any of the pairwise GCD values. So, we should compute GCDs of consecutive ciphertext values until we get a value that is not 1; at least one such value must exist, as described in the introduction to the problem. At that point, we can unzip the rest of the ciphertext, as described previously, finding all of the primes as we go. Then we can proceed as above. And we do not even have to know a bevy of DP flux algorithms, whatever those are!

#A note on language choice
#An essential skill in Code Jam is picking the right tool (language) for the right job. For some problems, a fast language such as C++ may be needed to obtain a solution within the time limits. For this problem, it is probably better to choose a language like Python that can handle very large numbers without any extra hassle, even at the cost of some speed, or a language like Java that has a built-in "big integer" implementation.

import itertools
import fileinput
import string
import math
import logging
import os

logging.basicConfig(
    level=os.environ.get("LOGLEVEL", "INFO"),
    format=('[%(filename)s:%(lineno)d] %(message)s'),
    datefmt='%Y-%m-%d:%H:%M:%S',
)

logger = logging.getLogger(__name__)

def solve2(mult_list):
    for first_found_pair, (a, b) in enumerate(zip(mult_list, mult_list[1:])):
        gcd = math.gcd(a, b)
        if gcd != a:  # looks like analysis is wrong about this bit
            break
    cipher = ['x'] * (len(mult_list) + 1)
    first_found_index = first_found_pair + 1
    cipher[first_found_index] = gcd
    logger.debug(cipher)
    for i in range(first_found_index + 1, len(cipher)):
        cipher[i] = mult_list[i-1] // cipher[i-1]
    logger.debug(mult_list)

    for i in range(first_found_index - 1, -1, -1):
        logger.debug((i, mult_list[i+1], cipher[i+1]))
        cipher[i] = mult_list[i] // cipher[i+1]

    assert len(set(cipher)) == len(string.ascii_uppercase), len(set(cipher))
    demap = dict(zip(sorted(set(cipher)), string.ascii_uppercase))
    return ''.join(demap[i] for i in cipher)


def getinputs():
    lines = fileinput.input()
    total_casenum = int(next(lines))
    for casenum in range(1, total_casenum + 1):
        unused_cap_len = next(lines)
        yield casenum, [int(e) for e in next(lines).split(' ')]


if __name__ == '__main__':
    for casenum, mult_list in getinputs():
        print('Case #{}: {}'.format(casenum, solve2(mult_list)))

