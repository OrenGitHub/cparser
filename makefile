main.o: main.c
	gcc -g -c $< -o $@

tree-sitter-c/src/parser.o: tree-sitter-c/src/parser.c
	gcc -g -c $< -o $@

tree-sitter/libtree-sitter.a:
	cd tree-sitter && make && cd - 

parser:                    \
main.o                     \
tree-sitter-c/src/parser.o \
tree-sitter/libtree-sitter.a
	gcc $^ -o $@
