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

#ifndef RR_JSON_SET_HH
#define RR_JSON_SET_HH

#include "core.hh"

namespace rr {
namespace json {

// Null
template<typename ...Args>
Value &NodeSetNull(Document &root, const Args &...list) throw(...) {
  return GetNode(root, list...).SetNull();
}

// Bool
template<typename ...Args>
Value &NodeSetBool(const bool &b, Document &root, const Args &...list) throw(...) {
  return GetNode(root, list...).SetBool(b);
}

// Object
template<typename ...Args>
Value &NodeSetEmptyObject(Document &root, const Args &...list) throw(...) {
  return GetNode(root, list...).SetObject();
}

template<typename ...Args>
MemberIterator NodeObjectMemberBegin(Document &root, const Args &...list) throw(...) {
  auto &v = GetNode(root, list...);
  if (!v.IsObject()) throw range_error("The value isn't an 'object'.");
  return v.MemberBegin();
}
template<typename ...Args>
MemberIterator NodeObjectMemberEnd(Document &root, const Args &...list) throw(...) {
  auto &v = GetNode(root, list...);
  if (!v.IsObject()) throw range_error("The value isn't an 'object'.");
  return v.MemberEnd();
}

// Array
template<typename ...Args>
Value &NodeSetEmptyArray(Document &root, const Args &...list) throw(...) {
  return GetNode(root, list...).SetArray();
}

template<typename ...Args>
ValueIterator NodeArrayBegin(Document &root, const Args &...list) throw(...) {
  auto &v = GetNode(root, list...);
  if (!v.IsArray()) throw range_error("The value isn't an 'array'.");
  return v.Begin();
}

template<typename ...Args>
ValueIterator NodeArrayEnd(Document &root, const Args &...list) throw(...) {
  auto &v = GetNode(root, list...);
  if (!v.IsArray()) throw range_error("The value isn't an 'array'.");
  return v.End();
}

// Int/Uint/Int64/Uint64/Double
template<typename ...Args>
Value &NodeSetInt(const int &i, Document &root, const Args &...list) throw(...) {
  return GetNode(root, list...).SetInt(i);
}

template<typename ...Args>
Value &NodeSetUint(const unsigned &u, Document &root, const Args &...list) throw(...) {
  return GetNode(root, list...).SetUint(u);
}

template<typename ...Args>
Value &NodeSetInt64(const int64_t &i64, Document &root, const Args &...list) throw(...) {
  return GetNode(root, list...).SetInt64(i64);
}

template<typename ...Args>
Value &NodeSetUint64(const uint64_t &u64, Document &root, const Args &...list) throw(...) {
  return GetNode(root, list...).SetUint64(u64);
}

template<typename ...Args>
Value &NodeSetDouble(const double &d, Document &root, const Args &...list) throw(...) {
  return GetNode(root, list...).SetDouble(d);
}

// String
template<typename ...Args>
Value &NodeSetString(const char *const &s, Document &root, const Args &...list) throw(...) {
  return GetNode(root, list...).SetString(StringRef(s));
}

}  // namespace json
}  // namespace rr

#endif  // RR_JSON_SET_HH
