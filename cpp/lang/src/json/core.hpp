/*
The MIT License (MIT)

Copyright (C) 2015 zhengrr<zhengrr0@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
* @author  zhengrr
* @version  2015-12-29
*/

#ifndef RR_JSON_CORE_HH
#define RR_JSON_CORE_HH

#include <stdexcept>
#include <string>

#include "rapidjson/document.h"

namespace rr {
namespace json {

using std::domain_error;
using std::invalid_argument;
using std::range_error;
using std::string;
using std::to_string;

using rapidjson::Document;
using rapidjson::SizeType;
using rapidjson::StringRef;
using rapidjson::Type;
using rapidjson::Value;

using ConstMemberIterator = rapidjson::Value::ConstMemberIterator;
using ConstValueIterator = rapidjson::Value::ConstValueIterator;
using MemberIterator = rapidjson::Value::MemberIterator;
using ValueIterator = rapidjson::Value::ValueIterator;

// Has Node
template<typename ...Args>
inline bool HasNode(const Value &node, const char *const &name, const Args &...list) throw() {
  if (!node.IsObject()) return false;
  if (!node.HasMember(name)) return false;
  return HasNode(node[name], list...);
}

template<typename ...Args>
inline bool HasNode(const Value &node, const int &index, const Args &...list) throw() {
  if (!node.IsArray()) return false;
  if (index < 0 || static_cast<int>(node.Size()) <= index) return false;
  return HasNode(node[index], list...);
}

inline bool HasNode(const Value &) throw() { return true; }

// Get Node
template<typename ...Args>
inline Value &GetNode(Value &node, const char *const &name, const Args &...list) throw(...) {
  if (!node.IsObject()) throw domain_error(string("The name '") + name + "'s parent isn't an object.");
  if (!node.HasMember(name)) throw domain_error(string("The name '") + name + "' not found.");
  return GetNode(node[name], list...);
}

template<typename ...Args>
inline Value &GetNode(Value &node, const int &index, const Args &...list) throw(...) {
  if (!node.IsArray()) throw domain_error(string("The index '") + to_string(index) + "'s parent isn't an array.");
  if (index < 0 || static_cast<int>(node.Size()) <= index) throw domain_error(string("The index '") + to_string(index) + "' out of range.");
  return GetNode(node[index], list...);
}

inline Value &GetNode(Value &node) throw() { return node; }

// Get R(eadonly) Node
template<typename ...Args>
inline const Value &GetRNode(const Value &node, const char *const &name, const Args &...list) throw(...) {
  if (!node.IsObject()) throw domain_error(string("The name '") + name + "'s parent isn't an object.");
  if (!node.HasMember(name)) throw domain_error(string("The name '") + name + "' not found.");
  return GetRNode(node[name], list...);
}

template<typename ...Args>
inline const Value &GetRNode(const Value &node, const int &index, const Args &...list) throw(...) {
  if (!node.IsArray()) throw domain_error(string("The index '") + to_string(index) + "'s parent isn't an array.");
  if (index < 0 || static_cast<int>(node.Size()) <= index) throw domain_error(string("The index '") + to_string(index) + "' out of range.");
  return GetRNode(node[index], list...);
}

inline const Value &GetRNode(const Value &node) throw() { return node; }

}  // namespace json
}  // namespace rr

#endif  // RR_JSON_CORE_HH
