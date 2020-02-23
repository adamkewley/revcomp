revcomp: revcomp.cpp
	$(CXX) -g -DSIMD -std=c++11 -O3 -march=native -o $@ $^

googletest/googletest/build:
	./configure

googletest/googletest/build/lib/libgtest.a: |  googletest/googletest/build
	make -C "$(@D)/.."

test-runner: revcomp.cpp tests.cpp googletest/googletest/build/lib/libgtest.a
	$(CXX) -g -DSIMD -std=c++11 -O3 -march=native -I googletest/googletest/include/ -o $@ tests.cpp googletest/googletest/build/lib/libgtest.a -lpthread

.PHONY: compile test
DEFAULT_TARGET := compile

compile: revcomp
test:  test-runner
	./test-runner
