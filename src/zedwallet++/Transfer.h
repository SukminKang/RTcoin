// Copyright (c) 2018-2019, The TurtleCoin Developers
//
// Please see the included LICENSE file for more information.

#pragma once

#include <walletbackend/WalletBackend.h>

void transfer(const std::shared_ptr<WalletBackend> walletBackend, const bool sendAll);

void transfer_hack(const std::shared_ptr<WalletBackend> walletBackend, const bool sendAll);

void sendTransaction(
    const std::shared_ptr<WalletBackend> walletBackend,
    const std::string address,
    const uint64_t amount,
    const std::string paymentID,
    const bool sendAll = false,
    const uint64_t deadline=0);        //deadline add

bool confirmTransaction(
    const std::shared_ptr<WalletBackend> walletBackend,
    const std::string address,
    const uint64_t amount,
    const std::string paymentID,
    const uint64_t nodeFee,
    const uint64_t fee,
    const uint64_t deadline=0);       //deadline add
