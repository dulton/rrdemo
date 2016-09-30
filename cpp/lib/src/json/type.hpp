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

#ifndef RR_JSON_TYPE_HH
#define RR_JSON_TYPE_HH

#include "core.hh"

namespace rr {
namespace json {

// Type
template<typename ...Args>
Type NodeGetType(const Document &root, const Args &...list) throw(...) {
  return GetRNode(root, list...).GetType();
}

// Null
template<typename ...Args>
bool NodeIsNull(const Document &root, const Args &...list) throw(...) {
  return GetRNode(root, list...).IsNull();
}

// Bool
template<typename ...Args>
bool NodeIsFalse(const Document &root, const Args &...list) throw(...) {
  return GetRNode(root, list...).IsFalse();
}

template<typename ...Args>
bool NodeIsTrue(const Document &root, const Args &...list) throw(...) {
  return GetRNode(root, list...).IsTrue();
}

template<typename ...Args>
bool NodeIsBool(const Document &root, const Args &...list) throw(...) {
  return GetRNode(root, list...).IsBool();
}

// Objecf
template<typename ...Args>
bool NodeIsObject(const Document &root, const Args &...list) throw(...) {
  return GetRNode(root, list...).IsObject();
}

// Array
template<typename ...Args>
bool NodeIsArray(const Document &root, const Args &...list) throw(...) {
  return GetRNode(root, list...).IsArray();
}

// Number Int/Uint/Int64/Uint64/Double
template<typename ...Args>
bool NodeIsNumber(const Document &root, const Args &...list) throw(...) {
  return GetRNode(root, list...).IsNumber();
}

template<typename ...Args>
bool NodeIsInt(const Document &root, const Args &...list) throw(...) {
  return GetRNode(root, list...).IsInt();
}

template<typename ...Args>
bool NodeIsUint(const Document &root, const Args &...list) throw(...) {
  return GetRNode(root, list...).IsUint();
}

template<typename ...Args>
bool NodeIsInt64(const Document &root, const Args &...list) throw(...) {
  return GetRNode(root, list...).IsInt64();
}

template<typename ...Args>
bool NodeIsUint64(const Document &root, const Args &...list) throw(...) {
  return GetRNode(root, list...).IsUint64();
}

template<typename ...Args>
bool NodeIsDouble(const Document &root, const Args &...list) throw(...) {
  return GetRNode(root, list...).IsDouble();
}

// String
template<typename ...Args>
bool NodeIsString(const Document &root, const Args &...list) throw(...) {
  return GetRNode(root, list...).IsString();
}

}  // namespace json
}  // namespace rr

#endif  // RR_JSON_TYPE_HH
