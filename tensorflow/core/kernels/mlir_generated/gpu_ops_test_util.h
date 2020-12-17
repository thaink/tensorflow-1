/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_CORE_KERNELS_MLIR_GENERATED_GPU_OPS_TEST_UTIL_H_
#define TENSORFLOW_CORE_KERNELS_MLIR_GENERATED_GPU_OPS_TEST_UTIL_H_

#include "absl/container/inlined_vector.h"
#include "llvm/ADT/STLExtras.h"
#include "tensorflow/core/framework/tensor_shape.h"

namespace tensorflow {
namespace test {

/// Helper functions to create or derive inputs of the right type and size.

template <typename T, typename LiteralT>
absl::InlinedVector<T, 10> InputAsVector(
    std::initializer_list<LiteralT> input) {
  absl::InlinedVector<T, 10> result;
  result.reserve(input.size());
  for (const LiteralT& value : input) {
    result.push_back(static_cast<T>(value));
  }
  return result;
}

template <typename T>
absl::InlinedVector<T, 10> RepeatInputToMatchShape(
    absl::InlinedVector<T, 10> input, int size) {
  absl::InlinedVector<T, 10> result;
  for (int i = 0; i < size; i++) {
    auto value = input[i % input.size()];
    result.push_back(value);
  }
  return result;
}

/// Helper functions to get default input values.

TensorShape DefaultInputShape();

template <typename T,
          std::enable_if_t<llvm::is_one_of<T, int8, int16, int32, int64>::value,
                           bool> = true>
T DefaultScalarInput() {
  return static_cast<T>(3);
}

template <typename T, std::enable_if_t<
                          llvm::is_one_of<T, Eigen::half, float, double>::value,
                          bool> = true>
T DefaultScalarInput() {
  return static_cast<T>(2.0);
}

template <typename T,
          std::enable_if_t<llvm::is_one_of<T, bool>::value, bool> = true>
T DefaultScalarInput() {
  return static_cast<T>(true);
}

template <typename T>
absl::InlinedVector<T, 10> InfZeroInput() {
  return InputAsVector<T, double>({-std::numeric_limits<double>::infinity(),
                                   -0.1, -0.0, 0.0, 0.1,
                                   std::numeric_limits<float>::infinity()});
}

template <typename T,
          std::enable_if_t<llvm::is_one_of<T, int8, int16, int32, int64>::value,
                           bool> = true>
absl::InlinedVector<T, 10> DefaultInput() {
  return InputAsVector<T, int>({-18, -9, -1, 0, 0, 1, 1, 2, 3, 5, 7, 9, 9, 18});
}

template <typename T, std::enable_if_t<
                          llvm::is_one_of<T, Eigen::half, float, double>::value,
                          bool> = true>
absl::InlinedVector<T, 10> DefaultInput() {
  return InputAsVector<T, double>({-18.0, -9.0, -1e-6, -0.0, 0.0, 1e-6, 0.1,
                                   0.2, 0.3, 0.5, 0.7, 0.9, 9.0, 18.0});
}

template <typename T,
          std::enable_if_t<llvm::is_one_of<T, bool>::value, bool> = true>
absl::InlinedVector<T, 10> DefaultInput() {
  return InputAsVector<T, bool>({true, false, true, true, false});
}
}  // namespace test
}  // namespace tensorflow

#endif  // TENSORFLOW_CORE_KERNELS_MLIR_GENERATED_GPU_OPS_TEST_UTIL_H_
