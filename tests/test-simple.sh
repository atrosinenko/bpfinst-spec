#!/bin/sh -e

bindir="$(dirname $0)/../../bpfinst-bin/"
bindir="$(realpath $bindir)"

run_test() {
	oldcwd=$(pwd)
	cd $1

    # Remove old artifacts
	rm -f *.o *.bc *.so test-program

	# Compile instrumenter
	clang -O3 -ggdb3 -Wall -Werror -funroll-loops -emit-llvm -c inst-bpf.c -I../../include
	llc -march=bpf -filetype=obj -o inst-bpf.o inst-bpf.bc
	clang -O3 -ggdb3 -Wall -Werror inst-native.c -o inst-native.so -fPIC --shared -I../../include
	export BPF_INST=$(pwd)/inst-bpf.o
	export NATIVE_INST=$(pwd)/inst-native.so

	$bindir/prepare-for-test
	$bindir/compile-sources make test-program
	for input in *.in
	do
	    echo "---> Validating $input"
	    $bindir/run-binary ./test-program < $input 2> real.err || echo "Run failed"
	    diff $(basename $input .in).err real.err
	done
	cd "$oldcwd"
}

for x in $*
do
    echo "==== Testing $x... ===="
    run_test $x
	echo "==== Done: $x ===="
done

echo "OK"
