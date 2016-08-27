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
* @version  0.2.3, 2015-1-9
*/

/*
the tool base on RapidJSON.
*/

#ifndef RR_JSON_JSON_HH
#define RR_JSON_JSON_HH

#include "get.hh"
#include "set.hh"
#include "type.hh"

namespace rr {
namespace json {

class Json {
public:
  explicit Json(void) = delete;
  explicit Json(const char *const &json) throw(...) {
    if (doc.Parse(json).HasParseError())
      throw invalid_argument("RapidJson's parse has error.");
  }
  explicit Json(const Json &) = delete;
  explicit Json(Json &&) = delete;
  void operator=(const Json &) = delete;
  void operator=(Json &&) = delete;
  ~Json(void) = default;

  // core
  template<typename ...Args> bool Has(const Args &...list) throw(...) { return HasNode(doc, list...); }
  template<typename ...Args> Value &Get(const Args &...list) throw(...) { return GetNode(doc, list...); }
  template<typename ...Args> Value &GetR(const Args &...list) throw(...) { return GetRNode(doc, list...); }

  // type
  template<typename ...Args> Type GetType(const Args &...list) throw(...) { return NodeGetType(doc, list...); }
  template<typename ...Args> bool IsNull(const Args &...list) throw(...) { return NodeIsNull(doc, list...); }
  template<typename ...Args> bool IsFalse(const Args &...list) throw(...) { return NodeIsFalse(doc, list...); }
  template<typename ...Args> bool IsTrue(const Args &...list) throw(...) { return NodeIsTrue(doc, list...); }
  template<typename ...Args> bool IsBool(const Args &...list) throw(...) { return NodeIsBool(doc, list...); }
  template<typename ...Args> bool IsObject(const Args &...list) throw(...) { return NodeIsObject(doc, list...); }
  template<typename ...Args> bool IsArray(const Args &...list) throw(...) { return NodeIsArray(doc, list...); }
  template<typename ...Args> bool IsNumber(const Args &...list) throw(...) { return NodeIsNumber(doc, list...); }
  template<typename ...Args> bool IsInt(const Args &...list) throw(...) { return NodeIsInt(doc, list...); }
  template<typename ...Args> bool IsUint(const Args &...list) throw(...) { return NodeIsUint(doc, list...); }
  template<typename ...Args> bool IsInt64(const Args &...list) throw(...) { return NodeIsInt64(doc, list...); }
  template<typename ...Args> bool IsUint64(const Args &...list) throw(...) { return NodeIsUint64(doc, list...); }
  template<typename ...Args> bool IsDouble(const Args &...list) throw(...) { return NodeIsDouble(doc, list...); }
  template<typename ...Args> bool IsString(const Args &...list) throw(...) { return NodeIsString(doc, list...); }

  // get
  template<typename ...Args> bool GetBool(const Args &...list) throw(...) { return NodeGetBool(doc, list...); }
  template<typename ...Args> bool ObjectIsEmpty(const Args &...list) throw(...) { return NodeObjectIsEmpty(doc, list...); }
  template<typename ...Args> SizeType ObjectMemberCount(const Args &...list) throw(...) { return NodeObjectMemberCount(doc, list...); }
  template<typename ...Args> ConstMemberIterator RObjectMemberBegin(const Args &...list) throw(...) { return RNodeObjectMemberBegin(doc, list...); }
  template<typename ...Args> ConstMemberIterator RObjectMemberEnd(const Args &...list) throw(...) { return RNodeObjectMemberEnd(doc, list...); }
  template<typename ...Args> bool ArrayIsEmpty(const Args &...list) throw(...) { return NodeArrayIsEmpty(doc, list...); }
  template<typename ...Args> SizeType ArraySize(const Args &...list) throw(...) { return NodeArraySize(doc, list...); }
  template<typename ...Args> ConstValueIterator RArrayBegin(const Args &...list) throw(...) { return RNodeArrayBegin(doc, list...); }
  template<typename ...Args> ConstValueIterator RArrayEnd(const Args &...list) throw(...) { return RNodeArrayEnd(doc, list...); }
  template<typename ...Args> int GetInt(const Args &...list) throw(...) { return NodeGetInt(doc, list...); }
  template<typename ...Args> unsigned GetUint(const Args &...list) throw(...) { return NodeGetUint(doc, list...); }
  template<typename ...Args> int64_t GetInt64(const Args &...list) throw(...) { return NodeGetInt64(doc, list...); }
  template<typename ...Args> uint64_t GetUint64(const Args &...list) throw(...) { return NodeGetUint64(doc, list...); }
  template<typename ...Args> double GetDouble(const Args &...list) throw(...) { return NodeGetDouble(doc, list...); }
  template<typename ...Args> const char* GetString(const Args &...list) throw(...) { return NodeGetString(doc, list...); }
  template<typename ...Args> SizeType StringLength(const Args &...list) throw(...) { return NodeStringLength(doc, list...); }

  // set
  template<typename ...Args> Value &SetNull(const Args &...list) throw(...) { return NodeSetNull(doc, list...); }
  template<typename ...Args> Value &SetBool(const bool &b, const Args &...list) throw(...) { return NodeSetBool(b, doc, list...); }
  template<typename ...Args> Value &SetEmptyObject(const Args &...list) throw(...) { return NodeSetEmptyObject(doc, list...); }
  template<typename ...Args> MemberIterator ObjectMemberBegin(const Args &...list) throw(...) { return NodeObjectMemberBegin(doc, list...); }
  template<typename ...Args> MemberIterator ObjectMemberEnd(const Args &...list) throw(...) { return NodeObjectMemberEnd(doc, list...); }
  template<typename ...Args> Value &SetEmptyArray(const Args &...list) throw(...) { return NodeSetEmptyArray(doc, list...); }
  template<typename ...Args> ValueIterator ArrayBegin(const Args &...list) throw(...) { return NodeArrayBegin(doc, list...); }
  template<typename ...Args> ValueIterator ArrayEnd(const Args &...list) throw(...) { return NodeArrayEnd(doc, list...); }
  template<typename ...Args> Value &SetInt(const int &i, const Args &...list) throw(...) { return NodeSetInt(i, doc, list...); }
  template<typename ...Args> Value &SetUint(const unsigned &u, const Args &...list) throw(...) { return NodeSetUint(u, doc, list...); }
  template<typename ...Args> Value &SetInt64(const int64_t &i64, const Args &...list) throw(...) { return NodeSetInt64(i64, doc, list...); }
  template<typename ...Args> Value &SetUint64(const uint64_t &u64, const Args &...list) throw(...) { return NodeSetUint64(u64, doc, list...); }
  template<typename ...Args> Value &SetDouble(const double &d, const Args &...list) throw(...) { return NodeSetDouble(d, doc, list...); }
  template<typename ...Args> Value &SetString(const char *const &s, const Args &...list) throw(...) { return NodeSetString(s, doc, list...); }

  // add-push

  // remove-pop

protected:
  Document doc;
};  // class Json

}  // namespace json
}  // namespace rr

#endif  // RR_JSON_JSON_HH
