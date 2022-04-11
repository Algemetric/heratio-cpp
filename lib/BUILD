load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "heratio",
    srcs = glob(["*.cc"]),
    hdrs = glob(["include/*.h"]),
    deps = ["@ntl//:ntl_", "@gmp//:gmp_"],
    visibility = ["//main:__pkg__"],
)