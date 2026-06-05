# TI-99 PPM Converter

`ppm-converter` reads a black/white PPM image and emits TI VDP tile bytes as xas99-compatible `BYTE` lines.

The generated text can be copied directly into assembly source for xga99/xas99 workflows.

## What It Does

- Reads a binary RGB PPM file (`P6` style data)
- Converts each 8x8 tile into 8 bytes (1 bit per pixel, MSB = left-most pixel)
- Prints one `BYTE` line per tile, for example:

```asm
BYTE >ff,>81,>81,>81,>81,>81,>81,>ff
```

A pixel is treated as set (`1`) when its red byte is `0` (black). Any non-zero red byte is treated as clear (`0`) (white).

## Supported Input Sizes

This project is intended for black/white images that are:

- 8x8 (1 tile)
- 16x16 (4 tiles)

Internally, width and height must both be divisible by 8.

## Build

From the project root:

```sh
make
```

This creates:

- `bin/ppm-converter`

## Usage

```sh
bin/ppm-converter [-d|--debug] <image.ppm>
```

Options:

- `-d`, `--debug`: prints parsed header values (`P6`, width/height, max value) before tile output.

Example:

```sh
bin/ppm-converter sprite16.ppm > sprite_tiles.inc
```

Then in xas99 source:

```asm
* Include generated tile bytes
       COPY "sprite_tiles.inc"
```

## Tile Output Order

Tiles are emitted in 8x8 blocks, left-to-right by tile column, then top-to-bottom within each column.

For a 16x16 image, order is:

1. top-left
2. bottom-left
3. top-right
4. bottom-right

## Input Notes

- Use binary PPM pixel data (`P6`-style RGB bytes).
- The converter currently assumes plain header fields and does not handle PPM comment lines.
- Use strictly black (`0,0,0`) and white (`255,255,255`) pixels.
