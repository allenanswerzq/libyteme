
byte_cc_library(
  NAME
    bit
  SRCS
    "bit.h"
  COPTS
    ${BYTE_DEFAULT_COPTS}
  PUBLIC
)

byte_cc_test(NAME
    bit_test
  SRCS
    "bit_test.cc"
  COPTS
    ${BYTE_TEST_COPTS}
  DEPS
    byte::bit
    gmock_main
)

byte_cc_library(
  NAME
    combina
  SRCS
    "combina.h"
  COPTS
    ${BYTE_DEFAULT_COPTS}
  PUBLIC
)

byte_cc_test(NAME
    combina_test
  SRCS
    "combina_test.cc"
  COPTS
    ${BYTE_TEST_COPTS}
  DEPS
    byte::combina
    gmock_main
)

byte_cc_library(
  NAME
    binary_heap
  SRCS
    "binary_heap.h"
  COPTS
    ${BYTE_DEFAULT_COPTS}
  PUBLIC
)

byte_cc_test(NAME
    binary_heap_test
  SRCS
    "binary_heap_test.cc"
  COPTS
    ${BYTE_TEST_COPTS}
  DEPS
    byte::binary_heap
    gmock_main
)
