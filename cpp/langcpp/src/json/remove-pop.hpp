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

#ifndef RR_JSON_REMOVEPOP_HH
#define RR_JSON_REMOVEPOP_HH

#include "core.hh"

namespace rr {
namespace json {

// Object
template<typename ...Args>
bool NodeObjectRemoveMember(const char *const &name, Document &root, const Args &...list) throw(...) {
  auto &v = GetNode(root, list...);
  if (!v.IsObject()) throw range_error("The value isn't an 'object'.");
  return v.RemoveMember(name);
}

template<typename ...Args>
void NodeObjectRemoveAllMembers(Document &root, const Args &...list) throw(...) {
  auto &v = GetNode(root, list...);
  if (!v.IsObject()) throw range_error("The value isn't an 'object'.");
  return v.RemoveAllMembers();
}

// Array
template<typename ...Args>
Value &NodeArrayPopBack(Document &root, const Args &...list) throw(...) {
  auto &v = GetNode(root, list...);
  if (!v.IsArray()) throw range_error("The value isn't an 'array'.");
  return v.PopBack();
}

template<typename ...Args>
void NodeArrayClear(Document &root, const Args &...list) throw(...) {
  auto &v = GetNode(root, list...);
  if (!v.IsArray()) throw range_error("The value isn't an 'array'.");
  return v.Clear();
}

}  // namespace json
}  // namespace rr

#endif  // RR_JSON_REMOVEPOP_HH
