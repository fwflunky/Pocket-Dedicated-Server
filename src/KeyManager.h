#pragma once

#include <iostream>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/ec.h>
#include <openssl/pem.h>
#include "Network.h"

namespace KeyManager {
    //_ZN8WebToken11DERToBinaryERKSsi

    class PrivateKeyManager {
    public:
        /*static inline void *instance = nullptr;

        static inline void (*original_PrivateKeyManagerCtor)(void *, int) = nullptr;

        static void PrivateKeyManagerCtor(void *self, int sys) { //1 0
            (*original_PrivateKeyManagerCtor)(self, sys);
            //std::cout << "privatekeymanagerctor\n";
            instance = self;
        };*/
        //static inline (*PrivateKeyManager_)


        static std::string base64_encode(const std::string &in) {

            std::string out;

            int val = 0, valb = -6;
            for (unsigned char c: in) {
                val = (val << 8) + c;
                valb += 8;
                while (valb >= 0) {
                    out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val >> valb) & 0x3F]);
                    valb -= 6;
                }
            }
            if (valb > -6) out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val << 8) >> (valb + 8)) & 0x3F]);
            while (out.size() % 4) out.push_back('=');
            return out;
        }

        static inline std::string (*original_sign)(void *, const std::string &, int) = nullptr;

        static std::string sign(void *self, const std::string &data, int hash) { //1 0
            //std::cout << data << " is data\n";
            auto dataa = (*original_sign)(self, data, hash);
            //std::cout << "\n" << dataa << " is sign\n";
            //std::cout << base64_encode(data.c_str(), data.size()) << " is based sign\n";
            return dataa;
        };

        static std::string EVP_PKEY_to_PEM(EVP_PKEY *pkey) {
            BIO *bio = nullptr;
            char *pem = nullptr;

            if (nullptr == pkey)
                return "1";

            if ((bio = BIO_new(BIO_s_mem())) == nullptr)
                return "2";
            if (0 == PEM_write_bio_PrivateKey(bio, pkey, nullptr, nullptr, 0, nullptr, nullptr)) {
                BIO_free(bio);
                return "3";
            }

            auto size = BIO_number_written(bio);
            pem = (char *) malloc(size);
            BIO_read(bio, pem, (int) BIO_number_written(bio));
            BIO_free(bio);

            std::string out(pem, size);
            // std::cout << out << "\n";
            free(pem);
            return out;
        }

    };

    class CryptoHash {
    public:
        static inline std::string privateKeyNotTrimmed;
        static inline std::string publicKeyTrimmed;
        static inline std::string publicKeyNotTrimmed;

        static inline std::string (*original_getPublicKey)(void *inst) = nullptr;

        static std::string getPublicKey(void *inst) {
            auto key = (*original_getPublicKey)(inst);
            //std::cout << "getpubkey " << key << "\n";
            publicKeyTrimmed = key;
            publicKeyNotTrimmed = "-----BEGIN PUBLIC KEY-----\n" + key + "\n-----END PUBLIC KEY-----";
            return key;
        }


        static inline EVP_PKEY *(*original_d2i_AutoPrivateKey)(EVP_PKEY **a, unsigned char **pp, long length) = nullptr;

        static inline EVP_PKEY *d2i_AutoPrivateKey(EVP_PKEY **a, unsigned char **pp, long length) {
            //std::cout << "d2i_AutoPrivateKey\n";
            auto ret = (*original_d2i_AutoPrivateKey)(a, pp, length);
            if (ret == (EVP_PKEY *) 0x0) {
                std::cout << PrivateKeyManager::EVP_PKEY_to_PEM(ret) << "\n";
            }
            return ret;
        }

    };

    class ExtendedCertificate {
    public:
        /* ExtendedCertificate::createIdentityCertificate(PrivateKeyManager&, long long, long long,
   mce::UUID const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&,
   std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, Json::Value
   const*) */
        static inline void* (*ExtendedCertificate_createIdentityCertificate)(void* self, void*, long long, long long, Network::mceUUID&, std::string&, std::string&, void* const jval) = nullptr;
        void* createIdentityCertificate(void* p1, long long p2, long long p3, Network::mceUUID& p4, std::string& p5, std::string& p6, void* const jval) {
            std::cout << "createIdentityCertificate\n";
           // std::cout << PrivateKeyManager::base64_encode(std::string(p4.filler, 256))
            std::cout << Network::mceUUID::asString(p4) << "\n";
           //std::cout << p4.p1 << " - " << p4.p2 << " - " << p4.p3 << " - " << p4.p4 << "\n";
           // auto ret = ExtendedCertificate_createIdentityCertificate(this, p1, p2, p3, p4, p5, p6, jval);
          //  std::cout << ret << "\n";
            return ExtendedCertificate_createIdentityCertificate(this, p1, p2, p3, p4, p5, p6, jval);
        }
    };
}
