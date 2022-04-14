load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "heratio",
    srcs = glob(["*.cc"] + ["*.h"]),
    deps = [
      "//lib:heratio",
      "@ntl//:ntl_",
      "@gmp//:gmp_",
      ],
)