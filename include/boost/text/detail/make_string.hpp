// Copyright (C) 2020 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_TEXT_DETAIL_MAKE_STRING_HPP
#define BOOST_TEXT_DETAIL_MAKE_STRING_HPP

#include <boost/text/detail/sentinel_tag.hpp>


namespace boost { namespace text { inline namespace v1 { namespace detail {

    template<typename CharIter>
    auto make_string(CharIter first, CharIter last)
    {
        return std::string(first, last);
    }
    template<typename CharIter>
    auto make_string(CharIter first, boost::text::null_sentinel)
    {
        return std::string(first);
    }
    template<typename CharIter, typename Sentinel>
    auto make_string(CharIter first, Sentinel last)
    {
        return std::string(
            first, std::next(first, boost::text::distance(first, last)));
    }

}}}}

#endif
