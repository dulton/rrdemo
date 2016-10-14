/**************************************************************************//*!
 * \file
 * \author { list of authors }
 * \date { date description }
 * \copyright { copyright description }
 ******************************************************************************/

#ifndef SINGLETON_HPP
#define SINGLETON_HPP

namespace nsp {

/******************************************************//*!
 * \since { text }
 **********************************************************/
class Singleton {
   explicit Singleton(const Singleton &) = delete;
   explicit Singleton(Singleton &&) = delete;
   Singleton &operator=(const Singleton &) = delete;

private:
   explicit Singleton(void) = default;
   //Singleton &operator=(Singleton &&) = default;
   ~Singleton(void) = default;

public:
   inline static Singleton &get_instance(void) { return *instance; }

private:
   static Singleton *const instance;

public:
   /* ... */

};  // class Singleton

}  // namespace nsp

#endif  // SINGLETON_HPP
