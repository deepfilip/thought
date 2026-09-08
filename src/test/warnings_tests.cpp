// Copyright (c) 2013-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "warnings.h"

#include "test/test_thought.h"
#include "test/testutil.h"
#include "util.h"

#include <boost/filesystem/operations.hpp>
#include <boost/test/unit_test.hpp>

#include <fstream>
#include <string>
#include <vector>

static std::vector<std::string> read_lines(boost::filesystem::path filepath)
{
    std::vector<std::string> result;

    std::ifstream f(filepath.string().c_str());
    std::string line;
    while (std::getline(f, line))
        result.push_back(line);

    return result;
}

BOOST_FIXTURE_TEST_SUITE(warnings_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(warning_notify)
{
    boost::filesystem::path temp = GetTempPath() /
        boost::filesystem::unique_path("alertnotify-%%%%.txt");

    ForceSetArg("-alertnotify", std::string("echo %s >> ") + temp.string());

    NotifyWarning("Warning 1", false);
    NotifyWarning("Evil Warning; /bin/ls; echo ", false);

    std::vector<std::string> r = read_lines(temp);
    BOOST_CHECK_EQUAL(r.size(), 2u);

// Windows built-in echo semantics are different than posixy shells. Quotes and
// whitespace are printed literally.

#ifndef WIN32
    BOOST_CHECK_EQUAL(r[0], "Warning 1");
    BOOST_CHECK_EQUAL(r[1], "Evil Warning; /bin/ls; echo "); // single-quotes should be removed
#else
    BOOST_CHECK_EQUAL(r[0], "'Warning 1' ");
    BOOST_CHECK_EQUAL(r[1], "'Evil Warning; /bin/ls; echo ' ");
#endif
    boost::filesystem::remove(temp);
    ForceRemoveArg("-alertnotify");
}

BOOST_AUTO_TEST_SUITE_END()
