// Copyright 2023 TikTok Pte. Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <memory>
#include <vector>

#include "network/network.h"
#include "solo/prng.h"

#include "duet/beaver_triple/arithmetic_triple.h"
#include "duet/oblivious_transfer/oblivious_transfer.h"
#include "duet/util/prng.h"

namespace petace {
namespace duet {

/**
 * @brief Implementation of Beaver's arithmetic triple generation protocol.
 *
 * This class implements the arithmetic triple generation protocol based on OT.
 */
class ArithmeticTripleOT : public ArithmeticTriple {
public:
    /**
     * @brief Constructor of the class.
     *
     * @param[in] net The network instance (e.g., from PETAce-Network)
     * @param[in] party The party id
     * @param[in] prng The PRNG instance
     * @param[in] ot The OT instance
     */
    ArithmeticTripleOT(const std::shared_ptr<network::Network>& net, std::size_t party_id, std::shared_ptr<PRNG> prng,
            const std::shared_ptr<ObliviousTransfer>& ot);

    ~ArithmeticTripleOT() = default;

    std::vector<std::int64_t> get_rand_triple(const std::shared_ptr<network::Network>& net);

private:
    void refill_rand_triple_buffer(const std::shared_ptr<network::Network>& net);

    void gen_rand_triple(const std::shared_ptr<network::Network>& net);

    std::size_t rand_triple_idx_ = 0;
    std::vector<std::vector<std::int64_t>> rand_triple_buff_{};
    std::size_t party_id_ = 0;
    std::shared_ptr<ObliviousTransfer> ot_ = nullptr;
    std::shared_ptr<PRNG> prng_ = nullptr;
};

inline std::shared_ptr<ArithmeticTriple> create_triple_engine_ot(const std::shared_ptr<network::Network>& net,
        std::size_t party_id, std::shared_ptr<PRNG> prng, const std::shared_ptr<ObliviousTransfer>& ot) {
    return std::make_shared<ArithmeticTripleOT>(net, party_id, prng, ot);
}

}  // namespace duet
}  // namespace petace
