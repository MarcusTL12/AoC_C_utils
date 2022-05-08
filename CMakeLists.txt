cmake_minimum_required(VERSION 3.10)

project(AoC_C_Utils)

include_directories(include hashmap.c)

add_library(
    aoc_util STATIC
    hashmap.c/hashmap.c
    src/array_util.c
    src/bitfield.c
    src/combinatorics.c
    src/deque.c
    src/file_util.c
    src/md5_util.c
    src/number_theory.c
    src/priority_queue.c
    src/regex_util.c
    src/str_split_iter.c
    src/vector.c
)

set_target_properties(
    aoc_util PROPERTIES PUBLIC_HEADER
    "\
hashmap.c/hashmap.h;\
include/array_util.h;\
include/bitfield.h;\
include/combinatorics.h;\
include/deque.h;\
include/file_util.h;\
include/iterator.h;\
include/md5_util.h;\
include/number_theory.h;\
include/priority_queue.h;\
include/regex_util.h;\
include/show.h;\
include/string_util.h;\
include/vector.h;\
"
)

install(TARGETS aoc_util PUBLIC_HEADER DESTINATION include/aoc_util)
