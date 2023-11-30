# cparser
stand-alone c parser skeleton based on tree-sitter and tree-sitter-c

## Build
```
git clone --recurse-submodules https://github.com/OrenGitHub/cparser.git
cd cparser
make parser
```

## Test it
```
# print called functions in example.c
./parser example.c
call [row:  6 (col: 16, end: 20)]
call [row: 10 (col:  5, end: 10)]
call [row: 12 (col: 15, end: 20)]
call [row: 15 (col:  5, end: 10)]
```
