# Browser-History-Management-System

## Overview  
A C++ file-based program that simulates browser navigation history using a stack-based approach. The system manages forward and backward navigation through visited URLs, reading input from a file and processing navigation commands.

## Features  

- **Dual-Stack Navigation:** Uses previous/next stacks to manage navigation history  
- **Command Processing:** Handles sequential "Forward" and "Backward" commands  
- **State Tracking:** Maintains current, next, and previous URL references  
- **File-Based Input:** Reads URLs and commands from "URLs.txt"  

## Program Input/Output Examples  

### Input Format  
The program reads from `URLs.txt` with:  
1. First line: Number of URLs  
2. Subsequent lines: URLs (one per line)  
3. Last line: Navigation commands ("Forward"/"Backward" separated by spaces)  

**Example Input File (`URLs.txt`):**  
```
5
https://www.google.com
https://www.github.com
https://www.stackoverflow.com
https://www.reddit.com
https://www.wikipedia.org
Backward Forward Backward Backward Forward
```

### Output Format  
**Output:**  
```
The current page at initial state is:
https://www.wikipedia.org

1:After choosing Backward: The current page is:
https://www.reddit.com
The Next one is:
https://www.wikipedia.org
The Previous one is:
https://www.stackoverflow.com

2:After choosing Forward: The current page is:
https://www.wikipedia.org
The Next one is:
The Previous one is:
https://www.reddit.com

3:After choosing Backward: The current page is:
https://www.reddit.com
The Next one is:
https://www.wikipedia.org
The Previous one is:
https://www.stackoverflow.com

4:After choosing Backward: The current page is:
https://www.stackoverflow.com
The Next one is:
https://www.reddit.com
The Previous one is:
https://www.github.com

5:After choosing Forward: The current page is:
https://www.reddit.com
The Next one is:
https://www.stackoverflow.com
The Previous one is:
https://www.wikipedia.org
```
