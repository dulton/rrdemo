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

#ifndef RR_JSON_GET_HH
#define RR_JSON_GET_HH

#include "core.hh"

namespace rr {
namespace json {

// Bool
template<typename ...Args>
bool NodeGetBool(const Document &root, const Args &...list) throw(...) {
  const auto &v = GetRNode(root, list...);
  if (!v.IsBool()) throw range_error("The value isn't a 'bool'.");
  return v.GetBool();
}

// Object
template<typename ...Args>
bool NodeObjectIsEmpty(const Document &root, const Args &...list) throw(...) {
  const auto &v = GetRNode(root, list...);
  if (!v.IsObject()) throw range_error("The value isn't an 'object'.");
  return v.ObjectEmpty();
}

template<typename ...Args>
SizeType NodeObjectMemberCount(const Document &root, const Args &...list) throw(...) {
  const auto &v = GetRNode(root, list...);
  if (!v.IsObject()) throw range_error("The value isn't an 'object'.");
  return v.MemberCount();
}

template<typename ...Args>
ConstMemberIterator RNodeObjectMemberBegin(const Document &root, const Args &...list) throw(...) {
  const auto &v = GetRNode(root, list...);
  if (!v.IsObject()) throw range_error("The value isn't an 'object'.");
  return v.MemberBegin();
}

template<typename ...Args>
ConstMemberIterator RNodeObjectMemberEnd(const Document &root, const Args &...list) throw(...) {
  const auto &v = GetRNode(root, list...);
  if (!v.IsObject()) throw range_error("The value isn't an 'object'.");
  return v.MemberEnd();
}

// Array
template<typename ...Args>
bool NodeArrayIsEmpty(const Document &root, const Args &...list) throw(...) {
  const auto &v = GetRNode(root, list...);
  if (!v.IsArray()) throw range_error("The value isn't an 'array'.");
  return v.Empty();
}

template<typename ...Args>
SizeType NodeArraySize(const Document &root, const Args &...list) throw(...) {
  const auto &v = GetRNode(root, list...);
  if (!v.IsArray()) throw range_error("The value isn't an 'array'.");
  return v.Size();
}

template<typename ...Args>
ConstValueIterator RNodeArrayBegin(const Document &root, const Args &...list) throw(...) {
  const auto &v = GetRNode(root, list...);
  if (!v.IsArray()) throw range_error("The value isn't an 'array'.");
  return v.Begin();
}

template<typename ...Args>
ConstValueIterator RNodeArrayEnd(const Document &root, const Args &...list) throw(...) {
  const auto &v = GetRNode(root, list...);
  if (!v.IsArray()) throw range_error("The value isn't an 'array'.");
  return v.End();
}

// Int/Uint/Int64/Uint64/Double
template<typename ...Args>
int NodeGetInt(const Document &root, const Args &...list) throw(...) {
  const auto &v = GetRNode(root, list...);
  if (!v.IsInt()) throw range_error("The value isn't an 'int'.");
  return v.GetInt();
}

template<typename ...Args>
unsigned NodeGetUint(const Document &root, const Args &...list) throw(...) {
  const auto &v = GetRNode(root, list...);
  if (!v.IsUint) throw range_error("The value isn't a 'unsigned'.");
  return v.GetUint();
}

template<typename ...Args>
int64_t NodeGetInt64(const Document &root, const Args &...list) throw(...) {
  const auto &v = GetRNode(root, list...);
  if (!key.IsInt64) throw range_error("The value isn't an 'int64_t'.");
  return v.GetInt64();
}

template<typename ...Args>
uint64_t NodeGetUint64(const Document &root, const Args &...list) throw(...) {
  const auto &v = GetRNode(root, list...);
  if (!v.IsUint64) throw range_error("The value isn't a 'uint64_t'.");
  return v.GetUint64();
}

template<typename ...Args>
double NodeGetDouble(const Document &root, const Args &...list) throw(...) {
  const auto &v = GetRNode(root, list...);
  if (!v.IsDouble()) throw range_error("The value isn't a 'double'.");
  return v.GetDouble();
}

// String
template<typename ...Args>
SizeType NodeStringLength(const Document &root, const Args &...list) throw(...) {
  const auto &v = GetRNode(root, list...);
  if (!v.IsString()) throw range_error("The value isn't a 'string'.");
  return v.GetStringLength();
}

template<typename ...Args>
const char *NodeGetString(const Document &root, const Args &...list) throw(...) {
  const auto &v = GetRNode(root, list...);
  if (!v.IsString()) throw range_error("The value isn't a 'string'.");
  return v.GetString();
}

}  // namespace json
}  // namespace rr

#endif  // RR_JSON_GET_HH
