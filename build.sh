#!/usr/bin/env bash

set -e

BUILD_DIR="build"

case "${1:-build}" in
build)
	echo "Configuring..."
	cmake -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Debug

	echo "Building..."
	cmake --build "$BUILD_DIR" --parallel
	;;

release)
	echo "Configuring Release..."
	cmake -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release

	echo "Building..."
	cmake --build "$BUILD_DIR" --parallel
	;;

run)
	cmake -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Debug
	cmake --build "$BUILD_DIR" --parallel
	cmake --build "$BUILD_DIR" --target run
	;;

clean)
	echo "Cleaning..."
	rm -rf "$BUILD_DIR"
	;;

*)
	echo "Usage:"
	echo "  ./build.sh build    # Debug build"
	echo "  ./build.sh release  # Release build"
	echo "  ./build.sh run      # Build and run SDL version"
	echo "  ./build.sh clean    # Remove build directory"
	exit 1
	;;
esac
