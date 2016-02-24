
                          POS-Tagging by Hidden Markov Model

  # Synopsis

  This is a Penn-Tree Bank tagger for any given sentence. It uses the learning concepts like Hidden Markov Model for the given Penn Tree Bank data-set. But to counter-effect the probability zero case due to some unknown values in the model. We assumed Laplacian Smoothing, which considers an initial 1 count for every instance of data to begin with.

  # Working

STEP-1:   //Coded in "HMM" folder
  Input : PennTreeBank Training Data SET.
  Output: Dictionary.txt

  This part mainly consists of a parser for the tree-bank.
  If we already have a big set of training data it can classify the training-format into "dictionary-count" format of dictionary.txt with contains

  TAGSET   -> List of all tags
  WORDSET  -> List of all words and its various Tag fruencies given aginst it.
  TAGFREQ1 -> Frequncy of list of all tags
  TAGFREQ2 -> Frequency of list of two tags in order.
  TAGFREQ3 -> Frequency of list of three tags in order.

STEP-2:   //Coded in "HMM2" folder
  Input : Dictionary.txt,
          input.txt : input sentence to POS tag.

  Output : POS-Tag prediction for the sentence provided as input.

  This part we encoded HMM with Laplacian-Smoothing.


  # How to run

  First make Parse.cpp in /HMM folder.
  Next run it with a tree bank dataset.

    $ g++ Parse.cpp -o parser
    $ ./parser
  This generates dictionary.txt file alogn with other few.

  Copy dictionary.txt to /HMM2 and make and run /MM2/HMM.cpp

    $ g++ HMM.cpp -o HMM
    $ ./HMM


  # Licence

  Copyright (C) 2014  V.Bhargav

  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
