# Copyright 2023 The Pigweed Authors
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.

# There's a lot going on in this WORKSPACE, but all we're doing is grabbing
# some hermetic toolchains from upstream Pigweed.
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Pigweed's dependencies we'll need.
http_archive(
    name = "bazel_skylib",  # 2022-09-01
    sha256 = "4756ab3ec46d94d99e5ed685d2d24aece484015e45af303eb3a11cab3cdc2e71",
    strip_prefix = "bazel-skylib-1.3.0",
    urls = ["https://github.com/bazelbuild/bazel-skylib/archive/refs/tags/1.3.0.zip"],
)

# Add Pigweed itself, as a submodule.
#
# TODO: b/300695111 - Support depending on Pigweed as a git_repository, even if
# you use pw_toolchain.
local_repository(
    name = "pigweed",
    path = "third_party/pigweed",
)

local_repository(
    name = "pw_toolchain",
    path = "third_party/pigweed/pw_toolchain_bazel",
)

# Get ready to grab CIPD dependencies. For this minimal example, the only dependencies will be the toolchains.
load(
    "@pigweed//pw_env_setup/bazel/cipd_setup:cipd_rules.bzl",
    "cipd_client_repository",
    "cipd_repository",
    "pigweed_deps",
)

pigweed_deps()

load("@cipd_deps//:cipd_init.bzl", "cipd_init")

cipd_init()

cipd_client_repository()

# Setup xcode on mac.
load("@pw_toolchain//features/macos:generate_xcode_repository.bzl", "pw_xcode_command_line_tools_repository")

pw_xcode_command_line_tools_repository()

# Fetch llvm toolchain.
cipd_repository(
    name = "llvm_toolchain",
    path = "fuchsia/third_party/clang/${os}-${arch}",
    tag = "git_revision:8475d0a2b853f6184948b428ec679edf84ed2688",
)

# Fetch linux sysroot for host builds.
cipd_repository(
    name = "linux_sysroot",
    path = "fuchsia/third_party/sysroot/linux",
    tag = "git_revision:d342388843734b6c5c50fb7e18cd3a76476b93aa",
)

# Fetch gcc-arm-none-eabi toolchain.
cipd_repository(
    name = "gcc_arm_none_eabi_toolchain",
    path = "fuchsia/third_party/armgcc/${os}-${arch}",
    tag = "version:2@12.2.mpacbti-rel1.1",
)

# Use upstream Pigweed toolchain configurations.
register_toolchains(
    "@pigweed//pw_toolchain/host_clang:host_cc_toolchain_linux",
    "@pigweed//pw_toolchain/host_clang:host_cc_toolchain_macos",
    "@pigweed//pw_toolchain/arm_gcc:arm_gcc_cc_toolchain_cortex-m4",
)
