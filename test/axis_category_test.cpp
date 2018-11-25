// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/core/lightweight_test.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <boost/histogram/axis/category.hpp>
#include <boost/histogram/axis/ostream_operators.hpp>
#include <limits>
#include <sstream>
#include <string>
#include <type_traits>
#include "utility_axis.hpp"

using namespace boost::histogram;

int main() {
  // bad_ctors
  {
    auto empty = std::vector<double>(0);
    BOOST_TEST_THROWS((axis::category<>(empty)), std::invalid_argument);
  }

  // axis::category
  {
    std::string A("A"), B("B"), C("C"), other;
    axis::category<std::string> a({A, B, C});
    axis::category<std::string> b;
    BOOST_TEST_NE(a, b);
    b = a;
    BOOST_TEST_EQ(a, b);
    b = axis::category<std::string>{{B, A, C}};
    BOOST_TEST_NE(a, b);
    b = a;
    b = b;
    BOOST_TEST_EQ(a, b);
    axis::category<std::string> c = std::move(b);
    BOOST_TEST_EQ(c, a);
    BOOST_TEST_NE(b, a);
    axis::category<std::string> d;
    BOOST_TEST_NE(c, d);
    d = std::move(c);
    BOOST_TEST_EQ(d, a);
    BOOST_TEST_EQ(a.size(), 3);
    BOOST_TEST_EQ(a(A), 0);
    BOOST_TEST_EQ(a(B), 1);
    BOOST_TEST_EQ(a(C), 2);
    BOOST_TEST_EQ(a(other), 3);
    BOOST_TEST_EQ(a.value(0), A);
    BOOST_TEST_EQ(a.value(1), B);
    BOOST_TEST_EQ(a.value(2), C);
    BOOST_TEST_THROWS(a.value(3), std::out_of_range);
  }

  // iterators
  {
    test_axis_iterator(axis::category<>({3, 1, 2}, ""), 0, 3);
    test_axis_iterator(axis::category<std::string>({"A", "B"}, ""), 0, 2);
  }

  return boost::report_errors();
}
