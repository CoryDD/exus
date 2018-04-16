/**
Copyright (c) 2009-2012 The Bitcoin developers
Copyright (c) 2018 Exus developers
Distributed under the MIT/X11 software license, see the accompanying
file COPYING or http://www.opensource.org/licenses/mit-license.php.
*/
#include "checkpoints.h"
#include "main.h"
#include "txdb.h"
#include "uint256.h"
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

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
    ( 45000, uint256("0xc7474dd2efc98404a25a071d7d0105fa9155a0a2579162a19dfd03556852872a") )
    ( 50000, uint256("0xd9b7d6c1789769cb00ef6f3ddd9b8965dc8f012a94edf5e4fbf5ec2e0fedb33f") )
    ( 60000, uint256("0x39a1da57e1f8679a89b3a7dbb4fccd7ff975bb2fc901257a6b688ff8a98d4ed0") )
    ( 70000, uint256("0xd7c474f7e9e39fbeca1104a9c207df6d91bc215f8a71c4cec5777382765992fd") )
    ( 75000, uint256("0xb5a2a7d83209290c1f35c00c43e780ced5cb2e6f3da9f7bd496731e7365e4191") )
    ( 80000, uint256("0x2ac01b24bcd0af1bc6b16f748cb88a792e23c550f0bb11ade4929ed5ef13febe") )
    ( 85000, uint256("0xaf43a36df9c5f014a02e66a9f39bcbc025f5669b1b10a39b097683815f8f84c1") )
    ( 90000, uint256("0x5721a1602ab6ceed4004f7ad1c137fa5e3bbde254b90f20d9a87e0f8733fb035") )
    ( 100000, uint256("0x05da8b9bb2ec8100d90ce95475efef658147b9ed81712e611294af49ea16954c") )
    ( 105000, uint256("0xff1552e0e5551198cc7846059f7e78a323058e97701e03377928b60a49b624d0") )
    ( 110000, uint256("0x836f366c95535547413d61cdc3367845f2ade370623241c0e4895e28d35de818") )
    ( 115000, uint256("0x84f0bae54b5e75b70f78def3296e37770515d0d8cf26fc1582eb3c26032ac387") )
    ( 120000, uint256("0xec2789b748f37b03df8d69a14e6d47f91480a7e62b0e9b549cfa9d838c032d87") ) // End POW
    ( 125000, uint256("0xf815b128af4bc5d3a89e2cd9c9527c068a74d78a1d44b0e3e8e963602729dd3d") )
    ( 130000, uint256("0x57b7174ce28f84e015d8766d8f7bdc20d34e418c6f0f5c0218edb85b580a442d") )
    ( 135000, uint256("0x3f4858b18760f302ea8f65542b25fefcdb392192884def39472cb61a4a30bf34") )
    ( 140000, uint256("0x91ce9333ef62bc3ff59d581aeb68f3d0fa5787368529c61fcef02fcaabb539ca") )
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

    BOOST_REVERSE_FOREACH (const MapCheckpoints::value_type& i, checkpoints) {
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
    const CBlockIndex* pindex = pindexBest;
    // Search backward for a block within max span and maturity window
    while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
        pindex = pindex->pprev;
    return pindex;
}

// Check against synchronized checkpoint
bool CheckSync(int nHeight)
{
    const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
    if (nHeight <= pindexSync->nHeight) {
        return false;
    }
    return true;
}
} // namespace Checkpoints
