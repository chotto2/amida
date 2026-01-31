# Amida - Divisor Algorithm Based on 45-Degree Mirror Conjecture

[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://codespaces.new/chotto2/amida)

## Overview

This program finds divisors of integers from 0 to 128 using a novel algorithm based on the "45-degree Mirror Conjecture for Divisors" and displays them with asterisks (*).  
This is a derivative program originating from the previously published [dstar-dev](https://github.com/chotto2/dstar-dev).  
The asterisk pattern plotted by this program (hereafter referred to as "amida") matches the pattern generated using the Sieve of Eratosthenes.  
However, it does not use the Sieve of Eratosthenes but instead employs the 45-degree Mirror Conjecture for Divisors described in the dstar-dev README.  
In this sense, it can be considered an alternative algorithm to the Sieve of Eratosthenes.  
The algorithm itself is simple: once a divisor is determined, it tilts 45 degrees like falling dominoes, determining the next domino, and the chain reaction continues.  
Through this repetition, divisors of all integers are determined without any arithmetic operations.  
The dominoes can also travel backward, and divisors are determined in that case as well.  
While attractive as an algorithm, it has the drawback of large memory consumption.  
The resulting list is placed in results/resultam.txt, so please take a look.  
However, the appearance is the same as dstar-dev.

## Features

- 🐳 **Docker Support** - Reproducible build environment
- 📊 **Divisors up to 128** - Suitable size for educational and research purposes

## Requirements

- Docker Desktop
- Git

## Build and Run

```bash
# Clone the repository
git clone https://github.com/chotto2/amida.git
cd amida

# Build Docker image
docker build -t amida .

# Run (list output)
docker run -it amida /app/build/amida
```

## Performance

```text
real    0m0.283s
user    0m0.010s
sys     0m0.015s
```

※Codespace: 2-Core  
※Without output redirection

## Output Example

The output result of `amida` is shown below.

```text
      n:   d(n):divisor2(n, 128)
      0:    128:******************************** ...
      1:      1:*
      2:      2:**
      3:      2:* *
      4:      3:** *
      5:      2:*   *
      6:      4:***  *
      7:      2:*     *
      8:      4:** *   *
      9:      3:* *     *
     10:      4:**  *    *
     11:      2:*         *
     12:      6:**** *     *
     13:      2:*           *
     14:      4:**    *      *
     15:      4:* * *         *
...
```

The first line indicates that each line of the list consists of three fields separated by ':'.  
The first field, n, indicates the target integer value.  
The second field, d(n), indicates the number of divisors of integer n.  
The third field, divisor2(n, 128), indicates plotting asterisks (*) at divisor positions.  
The positions of divisors (asterisks) are in ascending order 1, 2, 3... from the side closer to the second field.  
divisor2(n, 128) limits the upper bound of divisors to 128 and displays the results with asterisks.

For example, looking at the output for integer 6:

```text
      6:      4:***  * 
```

This indicates that integer 6 has 4 divisors, which are {1, 2, 3, 6}. (Positions 4 and 5 are blank)

※Integer 0 is a special case where all non-zero integers are divisors (n × 0 = 0)

## Main Processing Sequence

Step 1) Plot divisors of n=0

```text
      n:   d(n):divisor2(n, 128)
      0:    128:********************************...
      1:      0:
      2:      0:
      3:      0:
      4:      0:
      5:      0:
      6:      0:
...
```

Step 2) Expand divisor pattern of n=0 from n=1 at 45-degree angle

```text
      n:   d(n):divisor2(n, 128)
      0:    128:********************************...
      1:      1:*
      2:      1: *
      3:      1:  *
      4:      1:   *
      5:      1:    *
      6:      1:     *
...
```

Step 3) Expand divisor pattern of n=1 from n=2 at 45-degree angle

```text
      n:   d(n):divisor2(n, 128)
      0:    128:********************************...
      1:      1:*
      2:      2:**
      3:      1:  *
      4:      1:   *
      5:      1:    *
      6:      1:     *
...
```

Step 4) Expand divisor pattern of n=2 from n=3 at 45-degree angle

```text
      n:   d(n):divisor2(n, 128)
      0:    128:********************************...
      1:      1:*
      2:      2:**
      3:      2:* *
      4:      2: * *
      5:      1:    *
      6:      1:     *
...
```

Step 5) Expand divisor pattern of n=3 from n=4 at 45-degree angle

```text
      n:   d(n):divisor2(n, 128)
      0:    128:********************************...
      1:      1:*
      2:      2:**
      3:      2:* *
      4:      3:** *
      5:      1:    *
      6:      2:  *  *
...
```

Step 6) Expand divisor pattern of n=4 from n=5 at 45-degree angle

```text
      n:   d(n):divisor2(n, 128)
      0:    128:********************************...
      1:      1:*
      2:      2:**
      3:      2:* *
      4:      3:** *
      5:      2:*   *
      6:      3: **  *
...
```

Step 7) Expand divisor pattern of n=5 from n=6 at 45-degree angle

```text
      n:   d(n):divisor2(n, 128)
      0:    128:********************************...
      1:      1:*
      2:      2:**
      3:      2:* *
      4:      3:** *
      5:      2:*   *
      6:      4:***  *
...
```

Step 8) By repeating the above process, divisors of all integers can be found.

> **Note:** Since this is an algorithm based on the 45-degree Mirror Conjecture for Divisors, results are not guaranteed.
> Use at your own risk.

## Technical Details

- **Language**: C
- **Library**: GMP (GNU Multiple Precision Arithmetic Library)
- **Build System**: CMake
- **Divisor Range**: 0..128

## Important Notes

⚠️ **Important**: This version is an implementation for educational and research purposes. It handles divisors up to integer 128, so it does not affect modern cryptographic systems (such as RSA-4096).

## Future Plans

- 📝 Plan to submit paper to arXiv
- 📚 Detailed theoretical background of the algorithm

## License

MIT License

## Author

N.Arai

## Citation

Paper in preparation. Proper citation method will be provided after publication.

## Related Links

- Paper: arXiv (in preparation)
- Repository: <https://github.com/chotto2/amida>
