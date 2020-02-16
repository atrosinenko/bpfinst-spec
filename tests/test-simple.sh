#!/bin/sh -e

bindir="$(dirname $0)/../../bpfinst-bin/"
bindir="$(realpath $bindir)"

passed=""
failed=""

if [ ! -d $bindir ]
then
	echo
	echo "WARNING: $bindir not found, assuming spec self-check"
	echo
	notest=1
fi

run_test() {
	local_fails=""
	test_name=$1

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
	    diff $(basename $input .in).err real.err || local_fails="$local_fails $input"
	done
	if [ -n "$local_fails" ]
	then
		failed="$failed\n$test_name: $local_fails"
	else
		passed="$passed $test_name"
	fi
}

for x in $*
do
	echo "==== Testing $x... ===="
	oldcwd=$(pwd)
	cd $x
	run_test $x
	cd "$oldcwd"
	echo "==== Done: $x ===="
done

if [ -n "$passed" ]
then
	echo "\nPassed tests:$passed"
fi

if [ -n "$failed" ]
then
	echo
	echo " ==> FAILED <==\n$failed"
	exit 1
else
	echo "OK"
fi

