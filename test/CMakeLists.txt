# Copyright Hans Dembinski 2019
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

find_package(Python3 COMPONENTS Interpreter)
if (Python3_FOUND)
  # checks that b2 and cmake are in sync
  add_test(NAME runpy-${PROJECT_NAME}_check_build_system COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/check_build_system.py)

  # checks that all headers are included in odr test
  add_test(NAME runpy-${PROJECT_NAME}_check_odr_test COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/check_odr_test.py)
else()
MESSAGE(WARNING "Python interpreter not found, cannot check for odr violations and build system consistency")
endif()

include(BoostTest OPTIONAL RESULT_VARIABLE HAVE_BOOST_TEST)

if(HAVE_BOOST_TEST)

set(BOOST_TEST_LINK_LIBRARIES Boost::histogram)

# keep in sync with Jamfile, check_build_system test will complain if you don't
boost_test(TYPE compile-fail SOURCES axis_category_fail0.cpp)
boost_test(TYPE compile-fail SOURCES axis_category_fail1.cpp)
boost_test(TYPE compile-fail SOURCES axis_category_fail2.cpp)
boost_test(TYPE compile-fail SOURCES axis_integer_fail0.cpp)
boost_test(TYPE compile-fail SOURCES axis_integer_fail1.cpp)
boost_test(TYPE compile-fail SOURCES axis_integer_fail2.cpp)
boost_test(TYPE compile-fail SOURCES axis_integer_fail3.cpp)
boost_test(TYPE compile-fail SOURCES axis_integer_fail4.cpp)
boost_test(TYPE compile-fail SOURCES axis_regular_fail0.cpp)
boost_test(TYPE compile-fail SOURCES axis_regular_fail1.cpp)
boost_test(TYPE compile-fail SOURCES axis_variable_fail0.cpp)
boost_test(TYPE compile-fail SOURCES axis_variable_fail1.cpp)
boost_test(TYPE compile-fail SOURCES make_histogram_fail0.cpp)
boost_test(TYPE compile-fail SOURCES make_histogram_fail1.cpp)
boost_test(TYPE compile-fail SOURCES histogram_fail0.cpp)
boost_test(TYPE compile-fail SOURCES histogram_fail1.cpp)
boost_test(TYPE compile-fail SOURCES histogram_fail2.cpp)
boost_test(TYPE compile-fail SOURCES histogram_fail3.cpp)
boost_test(TYPE compile-fail SOURCES histogram_fail4.cpp)

set(BOOST_TEST_LINK_LIBRARIES Boost::histogram Boost::core)

boost_test(TYPE run SOURCES quick.cpp)

boost_test(TYPE run SOURCES accumulators_count_test.cpp)
boost_test(TYPE run SOURCES accumulators_mean_test.cpp)
boost_test(TYPE run SOURCES accumulators_sum_test.cpp)
boost_test(TYPE run SOURCES accumulators_weighted_mean_test.cpp)
boost_test(TYPE run SOURCES accumulators_weighted_sum_test.cpp)
boost_test(TYPE run SOURCES accumulators_collector_test.cpp)
boost_test(TYPE run SOURCES algorithm_project_test.cpp)
boost_test(TYPE run SOURCES algorithm_reduce_test.cpp)
boost_test(TYPE run SOURCES algorithm_sum_test.cpp)
boost_test(TYPE run SOURCES algorithm_empty_test.cpp)
boost_test(TYPE run SOURCES axis_boolean_test.cpp)
boost_test(TYPE run SOURCES axis_category_test.cpp)
boost_test(TYPE run SOURCES axis_integer_test.cpp)
boost_test(TYPE run SOURCES axis_option_test.cpp)
boost_test(TYPE run SOURCES axis_regular_test.cpp)
boost_test(TYPE run SOURCES axis_traits_test.cpp)
boost_test(TYPE run SOURCES axis_variable_test.cpp)
boost_test(TYPE run SOURCES axis_variant_test.cpp)
boost_test(TYPE run SOURCES detail_accumulator_traits_test.cpp)
boost_test(TYPE run SOURCES detail_argument_traits_test.cpp)
boost_test(TYPE run SOURCES detail_args_type_test.cpp)
boost_test(TYPE run SOURCES detail_axes_test.cpp)
boost_test(TYPE run SOURCES detail_convert_integer_test.cpp)
boost_test(TYPE run SOURCES detail_detect_test.cpp)
boost_test(TYPE run SOURCES detail_erf_inv_test.cpp)
boost_test(TYPE run SOURCES detail_limits_test.cpp)
boost_test(TYPE run SOURCES detail_make_default_test.cpp)
boost_test(TYPE run SOURCES detail_misc_test.cpp)
boost_test(TYPE run SOURCES detail_large_int_test.cpp)
boost_test(TYPE run SOURCES detail_iterator_adaptor_test.cpp)
boost_test(TYPE run SOURCES detail_operators_test.cpp)
boost_test(TYPE run SOURCES detail_relaxed_equal_test.cpp)
boost_test(TYPE run SOURCES detail_replace_type_test.cpp)
boost_test(TYPE run SOURCES detail_safe_comparison_test.cpp)
boost_test(TYPE run SOURCES detail_static_vector_and_span_test.cpp)
boost_test(TYPE run SOURCES detail_static_if_test.cpp)
boost_test(TYPE run SOURCES detail_tuple_slice_test.cpp)
boost_test(TYPE run SOURCES histogram_custom_axis_test.cpp)
boost_test(TYPE run SOURCES histogram_dynamic_test.cpp)
boost_test(TYPE run SOURCES histogram_fill_test.cpp
  COMPILE_OPTIONS $<$<CXX_COMPILER_ID:MSVC>:/bigobj>)
boost_test(TYPE run SOURCES histogram_growing_test.cpp)
boost_test(TYPE run SOURCES histogram_mixed_test.cpp)
boost_test(TYPE run SOURCES histogram_operators_test.cpp
  COMPILE_OPTIONS $<$<CXX_COMPILER_ID:MSVC>:/bigobj>)
boost_test(TYPE run SOURCES histogram_ostream_test.cpp)
boost_test(TYPE run SOURCES histogram_ostream_ascii_test.cpp)
set_tests_properties(run-boost_histogram-histogram_ostream_ascii_test
  PROPERTIES ENVIRONMENT "LANG=FOO;COLUMNS=20")
boost_test(TYPE run SOURCES histogram_fraction_test.cpp)
boost_test(TYPE run SOURCES histogram_collector_test.cpp)
boost_test(TYPE run SOURCES histogram_test.cpp)
boost_test(TYPE run SOURCES indexed_test.cpp)
boost_test(TYPE run SOURCES storage_adaptor_test.cpp)
boost_test(TYPE run SOURCES unlimited_storage_test.cpp)
boost_test(TYPE run SOURCES tools_test.cpp)
boost_test(TYPE run SOURCES issue_327_test.cpp)
boost_test(TYPE run SOURCES issue_353_test.cpp)
boost_test(TYPE run SOURCES accumulators_fraction_test.cpp)
boost_test(TYPE run SOURCES utility_binomial_proportion_interval_test.cpp)
boost_test(TYPE run SOURCES utility_wald_interval_test.cpp)
boost_test(TYPE run SOURCES utility_wilson_interval_test.cpp)

set(BOOST_TEST_LINK_LIBRARIES Boost::histogram Boost::core Boost::math)
boost_test(TYPE run SOURCES detail_normal_test.cpp)
boost_test(TYPE run SOURCES utility_clopper_pearson_interval_test.cpp)
boost_test(TYPE run SOURCES utility_jeffreys_interval_test.cpp)

find_package(Threads)
if (Threads_FOUND)

  boost_test(TYPE run SOURCES histogram_threaded_test.cpp
    LINK_LIBRARIES Threads::Threads)
  boost_test(TYPE run SOURCES storage_adaptor_threaded_test.cpp
    LINK_LIBRARIES Threads::Threads)
  boost_test(TYPE run SOURCES accumulators_count_thread_safe_test.cpp
    LINK_LIBRARIES Threads::Threads)

endif()

## serialization, range, units, accumulators pull in too many dependencies
# boost_test(TYPE run SOURCES boost_range_support_test.cpp
#     LINK_LIBRARIES Boost::range)
# boost_test(TYPE run SOURCES boost_accumulators_support_test.cpp
#     LINK_LIBRARIES Boost::accumulators)
# boost_test(TYPE run SOURCES boost_units_support_test.cpp
#     LINK_LIBRARIES Boost::units)
# boost_test(TYPE link SOURCES odr_main_test.cpp odr_test.cpp
#     LINK_LIBRARIES Boost::serialization)
# boost_test(TYPE run SOURCES detail_array_wrapper_serialization_test.cpp
#     LINK_LIBRARIES Boost::serialization)
# boost_test(TYPE run SOURCES unlimited_storage_serialization_test.cpp
#     LINK_LIBRARIES Boost::serialization)
# boost_test(TYPE run SOURCES storage_adaptor_serialization_test.cpp
#     LINK_LIBRARIES Boost::serialization)
# boost_test(TYPE run SOURCES histogram_serialization_test.cpp
#     LINK_LIBRARIES Boost::serialization)
# boost_test(TYPE run SOURCES axis_variant_serialization_test.cpp
#     LINK_LIBRARIES Boost::serialization)
# boost_test(TYPE run SOURCES accumulators_serialization_test.cpp
#     LINK_LIBRARIES Boost::serialization)

# Workaround for gcc-5
if (NOT(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6))

  boost_test(TYPE run SOURCES deduction_guides_test.cpp
    COMPILE_FEATURES cxx_std_17
  )
  boost_test(TYPE run SOURCES issue_290_test.cpp
    COMPILE_FEATURES cxx_std_17
  )

endif()

endif()
