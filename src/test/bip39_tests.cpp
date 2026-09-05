// Copyright (c) 2014-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "base58.h"
#include "hash.h"
#include "data/bip39_vectors.json.h"
#include "key.h"
#include "util.h"
#include "utilstrencodings.h"
#include "test/test_thought.h"
#include "bip39.h"

#include <boost/test/unit_test.hpp>

#include <cstring>

#include <univalue.h>

// In script_tests.cpp
extern UniValue read_json(const std::string& jsondata);

BOOST_FIXTURE_TEST_SUITE(bip39_tests, BasicTestingSetup)

static std::vector<unsigned char> DecodeCheckedBase58(const std::string& encoded)
{
    std::vector<unsigned char> decoded;
    BOOST_REQUIRE_MESSAGE(DecodeBase58(encoded, decoded), "invalid Base58 reference vector: " << encoded);
    BOOST_REQUIRE_MESSAGE(decoded.size() >= 4, "Base58Check reference vector too short: " << encoded);
    uint256 checksum = Hash(decoded.begin(), decoded.end() - 4);
    BOOST_REQUIRE_MESSAGE(std::memcmp(&checksum, &decoded.end()[-4], 4) == 0,
                          "Base58Check checksum mismatch: " << encoded);
    decoded.resize(decoded.size() - 4);
    return decoded;
}

static void CheckBip39ExtendedPrivateKey(const std::string& reference, const CExtKey& key)
{
    static const std::vector<unsigned char> bitcoinExtSecret = {0x04, 0x88, 0xAD, 0xE4};
    const std::vector<unsigned char>& thoughtExtSecret = Params().Base58Prefix(CChainParams::EXT_SECRET_KEY);
    unsigned char encoded[BIP32_EXTKEY_SIZE];
    key.Encode(encoded);

    std::vector<unsigned char> referenceDecoded;
    referenceDecoded = DecodeCheckedBase58(reference);
    BOOST_REQUIRE_EQUAL(bitcoinExtSecret.size(), 4U);
    BOOST_REQUIRE_EQUAL(thoughtExtSecret.size(), 4U);
    BOOST_REQUIRE_EQUAL(referenceDecoded.size(), bitcoinExtSecret.size() + BIP32_EXTKEY_SIZE);
    BOOST_CHECK_EQUAL_COLLECTIONS(referenceDecoded.begin(), referenceDecoded.begin() + bitcoinExtSecret.size(),
                                  bitcoinExtSecret.begin(), bitcoinExtSecret.end());
    BOOST_CHECK_EQUAL_COLLECTIONS(referenceDecoded.begin() + bitcoinExtSecret.size(), referenceDecoded.end(),
                                  encoded, encoded + BIP32_EXTKEY_SIZE);

    CThoughtExtKey thoughtKey;
    thoughtKey.SetKey(key);
    std::vector<unsigned char> thoughtDecoded;
    thoughtDecoded = DecodeCheckedBase58(thoughtKey.ToString());
    BOOST_REQUIRE_EQUAL(thoughtDecoded.size(), thoughtExtSecret.size() + BIP32_EXTKEY_SIZE);
    BOOST_CHECK_EQUAL_COLLECTIONS(thoughtDecoded.begin(), thoughtDecoded.begin() + thoughtExtSecret.size(),
                                  thoughtExtSecret.begin(), thoughtExtSecret.end());
    BOOST_CHECK_EQUAL_COLLECTIONS(thoughtDecoded.begin() + thoughtExtSecret.size(), thoughtDecoded.end(),
                                  encoded, encoded + BIP32_EXTKEY_SIZE);

    CThoughtExtKey roundTrip(thoughtKey.ToString());
    BOOST_CHECK(roundTrip.GetKey() == key);
}

// https://github.com/trezor/python-mnemonic/blob/b502451a33a440783926e04428115e0bed87d01f/vectors.json
BOOST_AUTO_TEST_CASE(bip39_vectors)
{
    UniValue tests = read_json(std::string(json_tests::bip39_vectors, json_tests::bip39_vectors + sizeof(json_tests::bip39_vectors)));

    for (unsigned int i = 0; i < tests.size(); i++) {
        // printf("%d\n", i);
        UniValue test = tests[i];
        std::string strTest = test.write();
        if (test.size() < 4) // Allow for extra stuff (useful for comments)
        {
            BOOST_ERROR("Bad test: " << strTest);
            continue;
        }

        std::vector<uint8_t> vData = ParseHex(test[0].get_str());
        SecureVector data(vData.begin(), vData.end());

        SecureString m = CMnemonic::FromData(data, data.size());
        std::string strMnemonic = test[1].get_str();
        SecureString mnemonic(strMnemonic.begin(), strMnemonic.end());

        // printf("%s\n%s\n", m.c_str(), mnemonic.c_str());
        BOOST_CHECK(m == mnemonic);
        BOOST_CHECK(CMnemonic::Check(mnemonic));

        SecureVector seed;
        SecureString passphrase("TREZOR");
        CMnemonic::ToSeed(mnemonic, passphrase, seed);
        // printf("seed: %s\n", HexStr(seed).c_str());
        BOOST_CHECK(HexStr(seed) == test[2].get_str());

        CExtKey key;
        key.SetMaster(&seed[0], 64);

        // Keep the Trezor/Bitcoin xprv as a reference for the 74-byte master-key payload,
        // and validate Thought's network-specific extended-secret presentation separately.
        CheckBip39ExtendedPrivateKey(test[3].get_str(), key);
    }
}

BOOST_AUTO_TEST_SUITE_END()
