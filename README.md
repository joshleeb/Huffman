# Huffman

Huffman encoder/decoder.

Please note that this is not for actual use, unless you want to play around with the Huffman algorithm. Not only is this code not optimized, it also encodes the input into bytes of 0 and 1 instead of bits. Similarly, the input for decoding is expected to be in bytes rather than bits.

## Motivation

Wanted to work on a small side project to get better at programming in C++.

## Usage

```bash
huffman [options]
```

Input is read from `stdin` and outputted to `stdout`.

### Options

#### Encoding

+ TODO: Implement.

`-e --encode`

Encode the input.

#### Decoding

+ TODO: Implement.

`-d --decode`

Decode the input.

#### Verbose

+ TODO: Implement.
+ TODO: Make sure escape characters are correctly displayed.

`-v --verbose`

Display the encoding mapping that will be used.

#### Statistics

+ TODO: Implement.

`-s --stats`

Display theoretical statistics, specifically how much space was compressed/expanded. As mentioned above, the data is in bytes rather than bits. The calculations for these statistics assume that this is a proper Huffman encoder/decoder that works in bits.
