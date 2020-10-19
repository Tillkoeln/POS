// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX Developers, The EREX Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"


static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{

    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x0000208b66f47e581ed227f1288feb09f0ba276921892f92ff3fec86de671632"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1517542208,
    0,  
       
    0 
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x0000688dbb914b9926a13eb862e517aa47d186606f7b8c91b1704adaf8464493"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1596043184,
    0,
    0};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    0,
    0,
    0};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        pchMessageStart[0] = 0x3c;
        pchMessageStart[1] = 0xe1;
        pchMessageStart[2] = 0xd1;
        pchMessageStart[3] = 0xc1;
        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort = 26100;
        bnProofOfWorkLimit = ~uint256(0) >> 20; 
        nSubsidyHalvingInterval = 5000000000000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 30; 
        nTargetSpacing = 1 * 30; 
        nLastPOWBlock = 100;
        nMaturity = 20;
        nMasternodeCountDrift = 20;
        nModifierUpdateBlock = 510;
        nMaxMoneyOut = 20000000 * COIN;
        nNewMasternodeCollateral_StartBlock = 20;
	nNewMasternodeCollateral_GPBlock = 20; 
        nNewMasternode_Collateral = 10000;
        nOriginalMasternode_Collateral = 10000;
        nBudget_Fee_Confirmations = 15; 


        const char* pszTimestamp = "Erexcoin POS 16 october 2020";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1517542208;
        genesis.nBits = 0x1e0fffff;
        genesis.nNonce = 23726;
        
 /**

         printf("Generating genesis block...\n");
        uint32_t nounce = 1;
             while(1) {
          printf("Nounce: %d\n", nounce);
                 genesis.nNonce = nounce;
                 hashGenesisBlock = genesis.GetHash();
               if(hashGenesisBlock.GetHex() < std::string("0000ffffff000000000000000000000000000000000000000000000000000000")) {
                   //if(hashGenesisBlock.GetHex() < bnProofOfWorkLimit.GetHex()) {
                   //if(consensus.hashGenesisBlock.GetHex() < std::string("0000082da923a04678394f873852c7f08b777af30224b6e23296f586370e80ae")) {
                       break;
                   } else {
                       if( nounce % 10000 == 0)
                           printf("NONCE : %x, GENESIS HASH : %s, MERKLE HASH :%s\n",nounce, hashGenesisBlock.GetHex().c_str(),genesis.hashMerkleRoot.ToString().c_str());
                       ++nounce;
                   }
             }
        printf("genesis: %s\n",hashGenesisBlock.GetHex().c_str());
        printf("merklehash: %s\n",genesis.hashMerkleRoot.ToString().c_str());

 */
 
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x0000208b66f47e581ed227f1288feb09f0ba276921892f92ff3fec86de671632"));
        assert(genesis.hashMerkleRoot == uint256("0x0abc39f87c398c746e2050e36fcd8f53cc7487de332102ab0da46ec0d04f235e"));

        vSeeds.push_back(CDNSSeedData("node1.erex.io", "node1.erex.io"));
        vSeeds.push_back(CDNSSeedData("node2.erex.io", "node2.erex.io"));       

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 5);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 33);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 128);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 5;
        strSporkKey = "0422616720e256cc000d73768e2f401344f3cae4c66994ce362de9a6e66fc92fc599614d6bc7255fcbbae63cdcd36afbc176ec6bd95c58273845c327f27d4c72fd";
        strObfuscationPoolDummyAddress = "38GqTVcgPLjQdGSnuh9FDtCUrXe8HY8k7M";
        nStartMasternodePayments = 1602975335;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;






/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x15;
        pchMessageStart[1] = 0x12;
        pchMessageStart[2] = 0xa1;
        pchMessageStart[3] = 0xa2;
        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort = 26101;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60;
        nTargetSpacing = 1 * 60;
        nLastPOWBlock = 1000;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 360;
        nMaxMoneyOut = 20000000 * COIN;

        genesis.nTime = 1517542215;
        genesis.nNonce = 7884;
        

 /**

         printf("Generating genesis block...\n");
        uint32_t nounce = 1;
             while(1) {
          printf("Nounce: %d\n", nounce);
                 genesis.nNonce = nounce;
                 hashGenesisBlock = genesis.GetHash();
               if(hashGenesisBlock.GetHex() < std::string("0000ffffff000000000000000000000000000000000000000000000000000000")) {
                   //if(hashGenesisBlock.GetHex() < bnProofOfWorkLimit.GetHex()) {
                   //if(consensus.hashGenesisBlock.GetHex() < std::string("0000082da923a04678394f873852c7f08b777af30224b6e23296f586370e80ae")) {
                       printf("nounce: %x\n",nounce);
                       break;
                   } else {
                       if( nounce % 10000 == 0)
                           printf("nounce: %x, hash: %s, merklehash:%s\n",nounce, hashGenesisBlock.GetHex().c_str(),genesis.hashMerkleRoot.ToString().c_str());
                       ++nounce;
                   }
             }
        printf("genesis: %s\n",hashGenesisBlock.GetHex().c_str());
        printf("merklehash: %s\n",genesis.hashMerkleRoot.ToString().c_str()); 
      
      
 */
        

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000688dbb914b9926a13eb862e517aa47d186606f7b8c91b1704adaf8464493"));
        assert(genesis.hashMerkleRoot == uint256("0x0abc39f87c398c746e2050e36fcd8f53cc7487de332102ab0da46ec0d04f235e"));

        vFixedSeeds.clear();
        vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData());
        //vSeeds.push_back(CDNSSeedData());

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 33);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 154);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 124);     
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3B)(0x88)(0xAD)(0x01).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3B)(0x88)(0xAE)(0x05).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x02).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "0448199e1da7091549e12459b437a71cba42003442c02f0e25508378906e0671fb80e6d7d82d02635e121964668e933e20f09ff483b011105a68e2e167cc4c9dee";
        strObfuscationPoolDummyAddress = "3LKMn5TUh44RiopQbRiY4BNyFUBcwyRaZh";
        
        nStartMasternodePayments = 1602975335; 
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;








/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xef;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0xc4;
        pchMessageStart[3] = 0xa4;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // EREX: 1 day
        nTargetSpacing = 1 * 60;        // EREX: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1454124731;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12345;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 26102;
        //assert(hashGenesisBlock == uint256("0x"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 37263;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
