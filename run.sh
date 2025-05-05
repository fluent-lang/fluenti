# Make sure the executable exists, if not build it
if [ ! -f "./cmake-build-debug/fluenti" ]; then
    echo "Executable not found, building..."
    ./build.sh
fi

./cmake-build-debug/fluenti "$@"
