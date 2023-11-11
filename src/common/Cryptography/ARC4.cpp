/*
* This file is part of the Pandaria 5.4.8 Project. See THANKS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "ARC4.h"
#include "Errors.h"
#include <openssl/sha.h>

ARC4::ARC4(uint8 len) : m_ctx(EVP_CIPHER_CTX_new())
{
#if OPENSSL_VERSION_NUMBER >= 0x30000000L
    _cipher = EVP_CIPHER_fetch(nullptr, "RC4", nullptr);
#else
    EVP_CIPHER const* _cipher = EVP_rc4();
#endif    
    EVP_CIPHER_CTX_init(m_ctx);
    EVP_EncryptInit_ex(m_ctx, EVP_rc4(), nullptr, nullptr, nullptr);
    int result1 = EVP_CIPHER_CTX_set_key_length(m_ctx, len);
    ASSERT(result1 == 1);
}

ARC4::~ARC4()
{
    EVP_CIPHER_CTX_cleanup(m_ctx);
#if OPENSSL_VERSION_NUMBER >= 0x30000000L
    EVP_CIPHER_free(_cipher);
#endif    
}

void ARC4::Init(uint8 const* seed)
{
    int result1 = EVP_EncryptInit_ex(m_ctx, nullptr, nullptr, seed, nullptr);
    ASSERT(result1 == 1);
}

void ARC4::UpdateData(int len, uint8 *data)
{
    int outlen = 0;
    int result1 = EVP_EncryptUpdate(m_ctx, data, &outlen, data, len);
    ASSERT(result1 == 1);
    int result2 = EVP_EncryptFinal_ex(m_ctx, data, &outlen);
    ASSERT(result2 == 1);
}
