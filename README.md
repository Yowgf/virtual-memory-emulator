# Virtual memory emulator

Emulation of operating system virtual memory algorithms.

## Build and execute

To build the program, simply run `make`. The executable can be found at
`build/main.out`. To execute it, follow the format:

```shell
./build/main.out <emulator> <input-file> <page-size> <memory-size>
```

`<emulator>` is one of `lru`, `fifo`, `newalg`. LRU implements the Least
Recently Used strategy. `fifo` implements a first-in-first-out page replacement
strategy. `newalg` replaces the page that has been used the least considering
all past uses in history.

For example, to run the `lru` emulator on file `test/fixtures/compressor.log`,
with page size of 2, and memory size of 1024 (512 pages of size 2 each), run:

```shell
./build/main.out lru test/fixtures/compressor.log 2 1024
```
