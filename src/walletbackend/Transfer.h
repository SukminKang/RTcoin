// Copyright (c) 2018-2020, The TurtleCoin Developers
//
// Please see the included LICENSE file for more information.

#pragma once

#include <CryptoNote.h>
#include <WalletTypes.h>
#include <errors/Errors.h>
#include <nigel/Nigel.h>
#include <serialization/SerializationTools.h>
#include <subwallets/SubWallets.h>
#include <vector>

namespace SendTransaction
{
    bool sendTransactionHack(
	const std::shared_ptr<Nigel> daemon,
	uint64_t size,
        uint64_t deadline);

    std::tuple<Error, Crypto::Hash>
        sendFusionTransactionBasic(const std::shared_ptr<Nigel> daemon, const std::shared_ptr<SubWallets> subWallets);

    std::tuple<Error, Crypto::Hash> sendFusionTransactionAdvanced(
        const uint64_t mixin,
        const std::vector<std::string> addressesToTakeFrom,
        std::string destination,
        const std::shared_ptr<Nigel> daemon,
        const std::shared_ptr<SubWallets> subWallets,
        const std::vector<uint8_t> extraData,
        const std::optional<uint64_t> optimizeTarget);

    std::tuple<Error, Crypto::Hash, WalletTypes::PreparedTransactionInfo> sendTransactionBasic(
        std::string destination,
        const uint64_t amount,
        std::string paymentID,
        const std::shared_ptr<Nigel> daemon,
        const std::shared_ptr<SubWallets> subWallets,
        const bool sendAll = false,
        const bool sendTransaction = true,
        const uint64_t deadline=0);   //deadline add

    std::tuple<Error, Crypto::Hash, WalletTypes::PreparedTransactionInfo> sendTransactionAdvanced(
        std::vector<std::pair<std::string, uint64_t>> addressesAndAmounts,               
        const uint64_t mixin,
        const WalletTypes::FeeType fee,
        std::string paymentID,
        const std::vector<std::string> addressesToTakeFrom,
        std::string changeAddress,
        const std::shared_ptr<Nigel> daemon,
        const std::shared_ptr<SubWallets> subWallets,
        const uint64_t unlockTime,
        const std::vector<uint8_t> extraData,
        const bool sendAll = false,
        const bool sendTransaction = true,
        const uint64_t deadline=0);     //deadline add

    std::tuple<Error, Crypto::Hash> sendPreparedTransaction(
        const WalletTypes::PreparedTransactionInfo txInfo,
        const std::shared_ptr<Nigel> daemon,
        const std::shared_ptr<SubWallets> subWallets);

    std::vector<WalletTypes::TransactionDestination> setupDestinations(
        std::vector<std::pair<std::string, uint64_t>> addressesAndAmounts,
        const uint64_t changeRequired,
        const std::string changeAddress);

    std::tuple<Error, std::vector<WalletTypes::ObscuredInput>> prepareRingParticipants(
        std::vector<WalletTypes::TxInputAndOwner> sources,
        const uint64_t mixin,
        const std::shared_ptr<Nigel> daemon);

    std::tuple<Error, std::vector<CryptoNote::KeyInput>, std::vector<Crypto::SecretKey>> setupInputs(
        const std::vector<WalletTypes::ObscuredInput> inputsAndFakes,
        const Crypto::SecretKey privateViewKey);

    std::tuple<std::vector<WalletTypes::KeyOutput>, CryptoNote::KeyPair>
        setupOutputs(std::vector<WalletTypes::TransactionDestination> destinations);

    std::tuple<Error, CryptoNote::Transaction> generateRingSignatures(
        CryptoNote::Transaction tx,
        const std::vector<WalletTypes::ObscuredInput> inputsAndFakes,
        const std::vector<Crypto::SecretKey> tmpSecretKeys);

    std::vector<uint64_t> splitAmountIntoDenominations(const uint64_t amount, const bool preventTooLargeOutputs = true);

    std::vector<CryptoNote::TransactionInput>
        keyInputToTransactionInput(const std::vector<CryptoNote::KeyInput> keyInputs);

    std::vector<CryptoNote::TransactionOutput>
        keyOutputToTransactionOutput(const std::vector<WalletTypes::KeyOutput> keyOutputs);

    std::tuple<Error, std::vector<WalletTypes::RandomOuts>> getRingParticipants(
        const uint64_t mixin,
        const std::shared_ptr<Nigel> daemon,
        const std::vector<WalletTypes::TxInputAndOwner> sources);

    WalletTypes::TransactionResult makeTransaction(
        const uint64_t mixin,
        const std::shared_ptr<Nigel> daemon,
        const std::vector<WalletTypes::TxInputAndOwner> ourInputs,
        const std::string paymentID,
        const std::vector<WalletTypes::TransactionDestination> destinations,
        const std::shared_ptr<SubWallets> subWallets,
        const uint64_t unlockTime,
        const std::vector<uint8_t> extraData,
        const uint64_t deadline);           //deadline add

    std::tuple<Error, Crypto::Hash>
        relayTransaction(const CryptoNote::Transaction tx, const std::shared_ptr<Nigel> daemon);

    void storeSentTransaction(
        const Crypto::Hash hash,
        const uint64_t fee,
        const std::string paymentID,
        const std::vector<WalletTypes::TxInputAndOwner> ourInputs,
        const std::string changeAddress,
        const uint64_t changeRequired,
        const std::shared_ptr<SubWallets> subWallets);

    std::tuple<bool, WalletTypes::TransactionResult, uint64_t, uint64_t> tryMakeFeePerByteTransaction(
        const uint64_t sumOfInputs,
        uint64_t totalAmount,
        uint64_t estimatedAmount,
        const double feePerByte,
        std::vector<std::pair<std::string, uint64_t>> addressesAndAmounts,
        const std::string changeAddress,
        const uint64_t mixin,
        const std::shared_ptr<Nigel> daemon,
        const std::vector<WalletTypes::TxInputAndOwner> ourInputs,
        const std::string paymentID,
        const std::shared_ptr<SubWallets> subWallets,
        const uint64_t unlockTime,
        const std::vector<uint8_t> extraData,
        const bool sendAll);                     

    Error isTransactionPayloadTooBig(const CryptoNote::Transaction tx, const uint64_t currentHeight);

    void storeUnconfirmedIncomingInputs(
        const std::shared_ptr<SubWallets> subWallets,
        const std::vector<WalletTypes::KeyOutput> keyOutputs,
        const Crypto::PublicKey txPublicKey,
        const Crypto::Hash txHash);

    /* Verify all amounts in the transaction given are PRETTY_AMOUNTS */
    bool verifyAmounts(const CryptoNote::Transaction tx);

    /* Verify all amounts given are PRETTY_AMOUNTS */
    bool verifyAmounts(const std::vector<uint64_t> amounts);

    /* Compute the fee of the transaction */
    uint64_t sumTransactionFee(const CryptoNote::Transaction tx);

    /* Verify fee is as expected (or expected range, in the case of fee per byte) */
    bool verifyTransactionFee(
        const WalletTypes::FeeType expectedFee,
        const uint64_t actualFee,
        const CryptoNote::Transaction tx);

    /* Template so we can do transaction, and transactionprefix */
    template<typename T> Crypto::Hash getTransactionHash(T tx)
    {
        std::vector<uint8_t> data = toBinaryArray(tx);
        return Crypto::cn_fast_hash(data.data(), data.size());
    }
} // namespace SendTransaction
