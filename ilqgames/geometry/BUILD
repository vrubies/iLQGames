cc_library(
    name = "line_segment",
    hdrs = ["line_segment.h"],
    srcs = ["line_segment.cc"],
    deps = ["//ilqgames/utils:defs",
            "@com_google_googletest//:gtest_main"],
)

cc_test(
    name = "line_segment_test",
    srcs = ["line_segment_test.cc"],
    deps = ["//ilqgames/geometry:line_segment",
            "@com_google_googletest//:gtest_main"],
)

cc_library(
    name = "polyline",
    hdrs = ["polyline.h"],
    srcs = ["polyline.cc"],
    deps = ["//ilqgames/geometry:line_segment",
            "@com_google_googletest//:gtest_main",
            "@com_github_google_glog//:glog"],
)

cc_test(
    name = "polyline_test",
    srcs = ["polyline_test.cc"],
    deps = ["//ilqgames/geometry:line_segment",
            "//ilqgames/geometry:polyline",
            "@com_google_googletest//:gtest_main"],
)

# cc_binary(
#     name = "hello-world",
#     srcs = ["hello-world.cc"],
#     deps = [
#         ":hello-greet",
#         "//lib:hello-time",
#     ],
# )