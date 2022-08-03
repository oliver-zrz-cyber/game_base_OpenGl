#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/zrz-oliver/CLionProjects/Opengl/cmake-build-debug
  make -f /Users/zrz-oliver/CLionProjects/Opengl/cmake-build-debug/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/zrz-oliver/CLionProjects/Opengl/cmake-build-debug
  make -f /Users/zrz-oliver/CLionProjects/Opengl/cmake-build-debug/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/zrz-oliver/CLionProjects/Opengl/cmake-build-debug
  make -f /Users/zrz-oliver/CLionProjects/Opengl/cmake-build-debug/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/zrz-oliver/CLionProjects/Opengl/cmake-build-debug
  make -f /Users/zrz-oliver/CLionProjects/Opengl/cmake-build-debug/CMakeScripts/ReRunCMake.make
fi

