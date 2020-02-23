# revcomp

C++ implementation of [language benchmark games'](https://benchmarksgame-team.pages.debian.net/benchmarksgame/) [reverse-complement](https://benchmarksgame-team.pages.debian.net/benchmarksgame/description/revcomp.html#revcomp)

- Single-threaded SIMD implementation, SSSE3
- C++11 with standard library


# Building

```bash
make
```

# Testing

Test suite is basic. It's just something I threw together to speed up
developent.

```bash
git submodule update --init --recursive
./configure && make test
```
