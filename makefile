app:
	rm -rf main && clang++ main.cpp -std=c++20 -O2 -o main && ./main
debug:
	rm -rf main && clang++ main.cpp -std=c++20 -o main &&./main
clean:
	rm -rf main
