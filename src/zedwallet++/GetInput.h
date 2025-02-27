// Copyright (c) 2018-2019, The TurtleCoin Developers
//
// Please see the included LICENSE file for more information.

#pragma once

#include <string>
#include <vector>
#include <walletbackend/WalletBackend.h>

std::string yellowANSIMsg(std::string msg);

std::string getPrompt(std::shared_ptr<WalletBackend> walletBackend);

std::string getAddress(const std::string msg, const bool integratedAddressesAllowed, const bool cancelAllowed);

std::string getPaymentID(const std::string msg, const bool cancelAllowed);

std::tuple<bool, uint64_t> getAmountToAtomic(const std::string msg, const bool cancelAllowed);

std::tuple<bool, uint64_t> getDeadline(const std::string msg, const bool cancelAllowed);

std::tuple<bool, uint64_t> getSize(const std::string msg, const bool cancelAllowed);

template<typename T> std::string getInput(const std::vector<T> &availableCommands, const std::string prompt);

std::tuple<std::string, uint16_t, bool> getDaemonAddress();

uint64_t getHeight(const std::string msg);
uint64_t getHeight();

std::string getHash(const std::string msg, const bool cancelAllowed);
