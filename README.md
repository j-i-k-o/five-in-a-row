# Five in a row (written in pure C tested by googletest)

## Build

```sh
cmake -S . -B build
cmake --build build
```

## Run app

```sh
❯ build/app
set board size: 6
⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜

Player 1 turn [format: r c]: 2 3
⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜
⬜⬜⬜１⬜⬜
⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜

Player 2 turn [format: r c]: 1 2
⬜⬜⬜⬜⬜⬜
⬜⬜２⬜⬜⬜
⬜⬜⬜１⬜⬜
⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜

Player 1 turn [format: r c]: ^C

```

## Run test

```sh
build/mytest
```
