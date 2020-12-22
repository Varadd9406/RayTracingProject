app:
	rm -rf main && clang++ main.cpp -std=c++20 -pthread -O2 -o main && ./main
debug:
	rm -rf main && clang++ main.cpp -std=c++20 -pthread -o main &&./main
clean:
	rm -rf main
