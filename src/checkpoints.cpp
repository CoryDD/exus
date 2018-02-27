/**
Copyright (c) 2009-2012 The Bitcoin developers
Copyright (c) 2018 Exus developers
Distributed under the MIT/X11 software license, see the accompanying
file COPYING or http://www.opensource.org/licenses/mit-license.php.
*/
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>
#include "checkpoints.h"
#include "txdb.h"
#include "main.h"
#include "uint256.h"

static const int nCheckpointSpan = 5000;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
    (     0, uint256("0x0000088e39f7f205701afd80597d455da6c775463bf8d72d6a45bab2160ea929") )
    (  5000, uint256("0x2205d4b5d9536117b564682e6c93783c8d69296de7ce6b0b13278994e431263a") )
    ( 10000, uint256("0x9facf454cfedddb0263b4444c00393662882d8d1350d3f44c18b4b6102b9ba96") )
    ( 15000, uint256("0x0a91b5106b97f85adf0127b3c8f5dfbc989289a14e64527c0e168a6168c2744e") )
    ( 20000, uint256("0xd437eba908f9201627e88fbd84b1777918be1d8f6f9b878e4663f4d74c7dc938") )
    ( 25000, uint256("0x06a7b88cfb6f2710a4fe3e4f7faab965b577a9c732dbcac366f6977a7ce1140f") )
    ( 30000, uint256("0x5cf3fe0c9592cc3812133a312811acf9b2b8751c18f698eb1b1779519f529bdb") )
    ( 35000, uint256("0xa15656069ca4a3a55e72bec7dc12fde8bacaed1a401552dee1b46ed444b7a4bc") )
    ( 40000, uint256("0xcbca22f79f9b053a831a5205ba8c1ca36f3df80d47cdf96f9e2e26dac632c1ab") )
    ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
        if (nHeight <= pindexSync->nHeight){
            return false;
        }
        return true;
    }
}
