# Solving challenges on https://cryptopals.com/
  - [ ] Set 1: Basics
    - [x] Challenge 1: Convert hex to base64
      - [Source](./src/set-1/ch-1/index.md)
      - [Test](./test/ch_1_test.cpp)
    - [x] Challenge 2: Fixed XOR
      - [Source](./src/set-1/ch-2/index.md)
      - [Test](./test/ch_2_test.cpp)
  - [ ] Set 2: Block crypto
  - [ ] Set 3: Block & stream crypto
  - [ ] Set 4: Stream crypto and randomness
  - [ ] Set 5: Diffie-Hellman and friends
  - [ ] Set 6: RSA and DSA
  - [ ] Set 7: Hashes
  - [ ] Set 8: Abstract Algebra


# Build
```sh
cmake -S. -B.
make -C build
```

# Test
```
ctest --test-dir build
```
