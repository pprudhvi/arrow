// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include <string>
#include <unordered_set>

#include "arrow/util/hashing.h"
#include "gandiva/arrow.h"
#include "gandiva/gandiva_aliases.h"

namespace gandiva {

/// Function Holder for IN Expressions
template <typename Type>
class InHolder {
 public:
  explicit InHolder(const std::unordered_set<Type>& values) {
    values_.max_load_factor(0.25f);
    for (auto& value : values) {
      values_.insert(value);
    }
  }

  bool HasValue(Type value) const { return values_.count(value) == 1; }

 private:
  std::unordered_set<Type> values_;
};

template <>
class InHolder<std::string> {
 public:
  explicit InHolder(std::unordered_set<std::string> values) : values_(std::move(values)) {
    values_lookup_.max_load_factor(0.25f);
    for (const std::string& value : values_) {
      values_lookup_.emplace(value);
    }
  }

  bool HasValue(arrow::util::string_view value) const {
    return values_lookup_.count(value) == 1;
  }

 private:
  struct string_view_hash {
   public:
    std::size_t operator()(arrow::util::string_view v) const {
      return arrow::internal::ComputeStringHash<0>(v.data(), v.length());
    }
  };

  std::unordered_set<arrow::util::string_view, string_view_hash> values_lookup_;
  const std::unordered_set<std::string> values_;
};

template <>
class InHolder<int32_t> {
 public:
  explicit InHolder(const std::unordered_set<int32_t>& values) {
    values_.max_load_factor(0.25f);
    for (auto& value : values) {
      values_.insert(value);
    }
  }

  bool HasValue(int32_t value) const { return values_.count(value) == 1; }

 private:
  struct simple_int32_hash {
   public:
    std::size_t operator()(int32_t v) const {
      return arrow::internal::ScalarHelper<int32_t, 0>::ComputeHash(v);
    }
  };
  std::unordered_set<int32_t, simple_int32_hash> values_;
};

template <>
class InHolder<int64_t> {
 public:
  explicit InHolder(const std::unordered_set<int64_t>& values) {
    values_.max_load_factor(0.25f);
    for (auto& value : values) {
      values_.insert(value);
    }
  }

  bool HasValue(int64_t value) const { return values_.count(value) == 1; }

 private:
  struct simple_int64_hash {
   public:
    std::size_t operator()(int64_t v) const {
      return arrow::internal::ScalarHelper<int64_t, 0>::ComputeHash(v);
    }
  };
  std::unordered_set<int64_t, simple_int64_hash> values_;
};

}  // namespace gandiva
