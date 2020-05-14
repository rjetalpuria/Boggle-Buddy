# Boggle-Buddy
Much like Scrabble Buddy, but for Boggle. It will help you by generating the longest and most awarding words. ENJOY!

To test it out yourself download the zip file.

INPUT: The user enters thier letters row-by-row

OUTPUT: A list of valid Boggle words sorted longest first

HOW IT WORKS?

-> When the user inputs the letters, they are validated and converted to lower cases.

-> Then the program runs the fetches all the valid words starting from that letter (via the .txt files) and pushes them on a vector

-> Then each word of that vector is checked. If the required letters for the word are present in the indexes next to them, then that word is pushed to the final output vector.

-> Once all the words are processed, they are sorted longest first using mergesort.

-> Finally, all possible valid words are printed out.
