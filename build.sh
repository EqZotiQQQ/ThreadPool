rm -rf build
cmake . -B build
cmake --build build -- -j1
echo "Build Done!"
