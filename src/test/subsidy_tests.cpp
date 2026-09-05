// Copyright (c) 2014-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "validation.h"

#include "test/test_thought.h"

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(subsidy_tests, TestingSetup)

BOOST_AUTO_TEST_CASE(block_subsidy_test)
{
    const Consensus::Params& consensusParams = Params(CBaseChainParams::MAIN).GetConsensus();
    const uint32_t nPrevBits = 0x1d00ffff; // Current Thought subsidy logic is height-based.
    const int interval = consensusParams.nSubsidyHalvingInterval;

    // Block 1 is the explicit Thought premine.
    BOOST_CHECK_EQUAL(GetBlockSubsidy(nPrevBits, 0, consensusParams, false), 809016994 * COIN);

    // Ordinary issuance is 314 THT until the first halving boundary.
    BOOST_CHECK_EQUAL(GetBlockSubsidy(nPrevBits, 1, consensusParams, false), 314 * COIN);
    BOOST_CHECK_EQUAL(GetBlockSubsidy(nPrevBits, interval - 2, consensusParams, false), 314 * COIN);

    // nPrevHeight is the previous block height, so interval-1 produces block `interval`.
    BOOST_CHECK_EQUAL(GetBlockSubsidy(nPrevBits, interval - 1, consensusParams, false), 157 * COIN);
    BOOST_CHECK_EQUAL(GetBlockSubsidy(nPrevBits, 2 * interval - 1, consensusParams, false), (314 * COIN) >> 2);

    // The implementation explicitly terminates once a 64-bit shift would be undefined.
    BOOST_CHECK_EQUAL(GetBlockSubsidy(nPrevBits, 64 * interval - 1, consensusParams, false), 0);
}

BOOST_AUTO_TEST_SUITE_END()
