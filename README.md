# EXUS Coin Specifications:
- POW + POS + MasterNodes
- Algo:                   Scrypt
- Symbol:                 EXUS
- Block time:             60 seconds
- Last POW block:            120,000
- POW generated coins:     1,587,039
- POS generated coins:    40,218,539
- Total coins supply:     41,805,578
- Instamine protection:    1,440 blocks
- Masternode requirement:  5,000 EXUS
- Masternode reward:       92% of POS (until block 120,000)
- Masternode reward:       75% of POS (after block 120,000)
- Stake min age:           24 hours
- Mining maturity:         20 blocks
- Min TX Fee:              0.0002 EXUS
- Recalculated difficulty: Every block
- RPC Port:                15877
- P2P Port:                15876
- RPC Testnet Port:        14877
- P2P Testnet Port:        14876


# EXUS Rewards:
- POW Block Rewards:
    - Block 1:                        400,000          EXUS (0.95% premined)
    - Block 2         -      1,440:         1          EXUS
    - Block 1,441     -    120,000:        10          EXUS


- POS Block Rewards:
    - Block 1:                              0          EXUS
    - Block 2         -      1,440:         1          EXUS
    - Block 1,441     -    120,000:        10          EXUS
    - Block 120,001   -  1,036,800:        20          EXUS
    - Block 1,036,801 -  2,073,600:        10          EXUS
    - Block 2,073,601 -  3,110,400:         5          EXUS
    - Block 3,110,401 -  4,147,200:         2.5        EXUS
    - Block 4,147,201 -  5,184,000:         1.25       EXUS
    - Block 5,184,001 -  6,220,800:         0.625      EXUS
    - Block 6,220,801 -  7,257,600:         0.3125     EXUS
    - Block 7,257,601 -  8,294,400:         0.15625    EXUS
    - Block 8,294,401 -  9,331,200:         0.078125   EXUS
    - Block 9,331,200 - 10,368,000:         0.0390625  EXUS


 - Masternode Rewards (92% of POS Block, 75% of POS block after block 120,000):
    - Block 1:                              0          EXUS
    - Block 2         -      1,440:         0.92       EXUS
    - Block 1,441     -    120,000:         9.20       EXUS
    - Block 120,000   -  1,036,800:        15.00       EXUS
    - Block 1,036,801 -  2,073,600:         7.50       EXUS
    - Block 2,073,601 -  3,110,400:         3.75       EXUS
    - Block 3,110,401 -  4,147,200:         1.875      EXUS
    - Block 4,147,201 -  5,184,000:         0.9375     EXUS
    - Block 5,184,001 -  6,220,800:         0.46875    EXUS
    - Block 6,220,801 -  7,257,600:         0.234375   EXUS
    - Block 7,257,601 -  8,294,400:         0.1171875  EXUS
    - Block 8,294,401 -  9,331,200:         0.05859375 EXUS
    - Block 9,331,200 - 10,368,000:         0.02929688 EXUS
