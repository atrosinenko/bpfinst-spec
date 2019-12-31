#!/bin/sh -e

bindir="$(dirname $0)/../../bpfinst-bin/"
bindir="$(realpath $bindir)"

if [ ! -d $bindir ]
then
	echo
	echo "WARNING: $bindir not found, assuming spec self-check"
	echo
	notest=1
fi

run_test() {
	# Remove old artifacts
	rm -f *.o *.bc *.so test-program

	# Test for compatibility with toolchain, etc.
	if [ -x ./skip_if ] && ./skip_if
	then
		echo "======================"
		echo "WARNING: SKIPPING TEST"
		echo "======================"
		return
	fi

	# Compile instrumenter
	clang -O3 -ggdb3 -Wall -Werror -funroll-loops -emit-llvm -c inst-bpf.c -I../../include
	llc -march=bpf -filetype=obj -o inst-bpf.o inst-bpf.bc
	clang -O3 -ggdb3 -Wall -Werror inst-native.c -o inst-native.so -fPIC --shared -I../../include
	export BPF_INST=$(pwd)/inst-bpf.o
	export NATIVE_INST=$(pwd)/inst-native.so

	if [ "x$notest" = "x1" ]
	then
		return
	fi
	$bindir/prepare-for-test
	$bindir/compile-sources make test-program
	for input in *.in
	do
	    echo "---> Validating $input"
	    $bindir/run-binary ./test-program < $input 2> real.err || echo "Run failed"
	    diff $(basename $input .in).err real.err
	done
}

for x in $*
do
	echo "==== Testing $x... ===="
	oldcwd=$(pwd)
	cd $x
	run_test
	cd "$oldcwd"
	echo "==== Done: $x ===="
done

echo "OK"
