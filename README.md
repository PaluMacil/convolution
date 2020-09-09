# Convolution

The purpose of this **convolution** command is to measure complexity of a document, referred to here as "total 
convolution". The command furthermore lists a few other statistics and outputs a CSV of the sliding complexity. 

## Approach

This naive tool produces a score by iterating over every window of words (default is 16 words) in the sample to 
measure local complexity. The score is a ratio of the size of the unique set of words to the count of words in the
sample:

```
// for every window being examined
for (int win = 0; win < maxWindow; win++) {
    // for every word in window, go from start index of window to end of window
    for (int i = win; i < win + windowSize; i++) {
        uniqueWords.insert(words[i]);
    }
    // calculate and save score
    scores.push_back(float(uniqueWords.size())/float(windowSize));
    // reset the word set for the next window
    uniqueWords.clear();
}
``` 

There are no dependencies outside the C++11 standard library.

Objects like the `uniqueWords` set per window above or the `std::ostringstream` accumulating each current word 
(in the parse method) are reset and reused to reduce allocation overhead in tight loops.

Due to the simplicity of this tool, I threw cstring literals instead of inheriting from exceptions, and I did 
not unit test. A more complex calculation would have led to more structure in these two areas. The CSVWriter 
class is simple approach to outputting csv but was quite sufficient for producing graphs in LibreOffice Calc.

## Run

Run the command with a filename and an optional window size. If no window size is specified, 16 will be used.

```
./bin/convolution [filename] [windowSize]
```

## Output

The output of the convolution command reports the number of words in the sample, the total, average, min, and max 
complexity, and it notifies the user of where the local scores are stored in csv format.

```
parsed 271 words from /home/dan/CLionProjects/convolution/GettysburgAddress.txt
complexity summary:
	total: 0.5203	average: 0.9219	min: 0.6875	max: 1.0000
wrote 256 records to /home/dan/CLionProjects/convolution/GettysburgAddress.txt.csv
```

```
parsed 27340 words from /home/dan/CLionProjects/convolution/Alice_in_Wonderland.txt
complexity summary:
	total: 0.0941	average: 0.9234	min: 0.3750	max: 1.0000
wrote 27325 records to /home/dan/CLionProjects/convolution/Alice_in_Wonderland.txt.csv
```

## Analysis

Graphed local complexity of the Gettysburg Address resulted in a fairly readable graph. 
You can easily see that many windows of high complexity are brief except for one in the 
middle.

![gburg](gburg-1.png)

The graph for Alice in Wonderland was much harder to read. You can't really see how many windows are 
more or less complex without making an unreasonably wide graph or by dropping data
points.

![alice1](alice-1.png)

I ran Alice in Wonderland again, this time with a huge window of 160. This allows one 
to see areas that are more or less complex, but it is no longer comparable to works of 
different window sizes. Also of note, the extremes are muted since no 160 word window 
will have only unique words.

```
parsed 27340 words from /home/dan/CLionProjects/convolution/Alice_in_Wonderland.txt
complexity summary:
	total: 0.0941	average: 0.6161	min: 0.3812	max: 0.7375
wrote 27181 records to /home/dan/CLionProjects/convolution/Alice_in_Wonderland.txt.csv
```

![alice2](alice-2.png)

### Alternative Approaches

Convolution's min, max, and average seemed to be unhelpful for measuring anything meaningful. 
The total score, however, matches the trends you see in other textual complexity measures 
such as the ones compared to this in the table below. These alternative methods are from 
[PaluMacil/flesch-index](github.com/PaluMacil/flesch-index).

|                      | Gettysburg Address | Alice in Wonderland |
|----------------------|--------------------|---------------------|
| Convolution Total    | 0.5203             | 0.0941              |
| Convolution Average  | 0.9219             | 0.9234              |
| Flesch Reading Ease  | 61.82              | 84.71               |
| Readability          | 8th and 9th grade  | 6th grade           |
| Flesch–Kincaid Grade | 11.22              | 5.05                |

The magnitude of the difference between total and average scores suggests that there might
be an unreasonable bias against shorter texts which have less opportunity to repeat words. 
While the convolution total might be helpful for comparing some texts of equal length, the 
other scoring systems are much less sensitive to this type of variance in sample length.