
byte_cc_library(
  NAME
    logging
  HDRS
    "logging.h"
  SRCS
    "logging.cc"
  COPTS
    ${BYTE_DEFAULT_COPTS}
  PUBLIC
)

byte_cc_library(
  NAME
    benchmark
  HDRS
    "benchmark.h"
  SRCS
    "benchmark.cc"
  COPTS
    ${BYTE_DEFAULT_COPTS}
  DEPS
    byte::logging
  PUBLIC
)

byte_cc_library(
  NAME
    random
  HDRS
    "random.h"
  COPTS
    ${BYTE_DEFAULT_COPTS}
  PUBLIC
)

byte_cc_library(
  NAME
    bit
  HDRS
    "bit.h"
  COPTS
    ${BYTE_DEFAULT_COPTS}
  PUBLIC
)

byte_cc_test(
  NAME
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
  HDRS
    "combina.h"
  COPTS
    ${BYTE_DEFAULT_COPTS}
  PUBLIC
)

byte_cc_test(
  NAME
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
  HDRS
    "binary_heap.h"
  COPTS
    ${BYTE_DEFAULT_COPTS}
  PUBLIC
)

byte_cc_test(
  NAME
    binary_heap_test
  SRCS
    "binary_heap_test.cc"
  COPTS
    ${BYTE_TEST_COPTS}
  DEPS
    byte::binary_heap
    gmock_main
)

byte_cc_library(
  NAME
    dsu
  HDRS
    "dsu.h"
  COPTS
    ${BYTE_DEFAULT_COPTS}
  PUBLIC
)

byte_cc_test(
  NAME
    dsu_test
  SRCS
    "dsu_test.cc"
  COPTS
    ${BYTE_TEST_COPTS}
  DEPS
    byte::binary_heap
    gmock_main
)

byte_cc_library(
  NAME
    ordered_set
  HDRS
    "ordered_set.h"
  COPTS
    ${BYTE_DEFAULT_COPTS}
  PUBLIC
)

byte_cc_test(
  NAME
    ordered_set_test
  SRCS
    "ordered_set_test.cc"
  COPTS
    ${BYTE_TEST_COPTS}
  DEPS
    byte::ordered_set
    gmock_main
)

byte_cc_library(
  NAME
    graph
  HDRS
    "graph.h"
  COPTS
    ${BYTE_DEFAULT_COPTS}
  PUBLIC
)

byte_cc_test(
  NAME
    graph_test
  SRCS
    "graph_test.cc"
  COPTS
    ${BYTE_TEST_COPTS}
  DEPS
    byte::graph
    gmock_main
)

byte_cc_library(
  NAME
    segtree
  HDRS
    "segtree.h"
  COPTS
    ${BYTE_DEFAULT_COPTS}
  PUBLIC
)

byte_cc_test(
  NAME
    segtree_test
  SRCS
    "segtree_test.cc"
  COPTS
    ${BYTE_TEST_COPTS}
  DEPS
    byte::segtree
    byte::random
    byte::benchmark
    gmock_main
)

# Run all benchmarks
byte_cc_test(
  NAME
    run_benchmark
  COPTS
    ${BYTE_DEFAULT_COPTS}
  SRCS
    "segtree_test.cc"
    "run_benchmark.cc"
  DEPS
    byte::segtree
    byte::benchmark
    gmock_main
)

