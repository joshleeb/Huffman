# Huffman

Huffman encoder.

Please note that this is not for actual use, unless you want to play around with the Huffman algorithm. Not only is this code not optimized, it also encodes the input into bytes of 0 and 1 instead of bits. Similarly, the input for decoding is expected to be in bytes rather than bits.

## Motivation

Wanted to work on a small side project to get better at programming in C++.

## Usage

```bash
huffman [OPTIONS...]
Huffman encoder concept project.

OPTIONS:
  -h [ --help ]         Show this help
  -s [ --stats ]        Show hypothetical statistics
  -v [ --verbose ]      Turn on verbose output
```

Input is read from `stdin` and outputted to a specified file or `stdout`.

### Options

#### Help

`-h --help`

Show help message and usage information.

#### Statistics

`-s --stats`

Display theoretical statistics, specifically how much space was compressed/expanded. As mentioned above, the data is in bytes rather than bits. The calculations for these statistics assume that this is a proper Huffman encoder that works in bits.

#### Verbose

`-v --verbose`

Display the encoding mapping that will be used.
