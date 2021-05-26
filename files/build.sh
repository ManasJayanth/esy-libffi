#! /bin/sh

FLAGS=

case "$(uname -s)" in
    CYGWIN*|MINGW32*|MSYS*)
        FLAGS="$FLAGS --host x86_64-w64-mingw32"
        ;;
    DARWIN*)
        FLAGS="$FLAGS --disable-dependency-tracking"
        case "$(uname -m)" in
          arm64*)
          FLAGS="$FLAGS -build=aarch64-apple-darwin20.3.0"
          ;;
        case *)
          ;;
        esac
    *)
        ;;
esac


./configure $FLAGS
make
