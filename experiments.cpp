#include "palisade.h"
using namespace lbcrypto;

void run_game(double B) {

  uint32_t multDepth = 1;
  uint32_t scaleFactorBits = 40;
  uint32_t batchSize = 1;
  SecurityLevel securityLevel = HEStd_128_classic;
  CryptoContext<DCRTPoly> cc =
      CryptoContextFactory<DCRTPoly>::genCryptoContextCKKS(
          multDepth, scaleFactorBits, batchSize, securityLevel);

  cc->Enable(ENCRYPTION);
  cc->Enable(SHE);
  auto keys = cc->KeyGen();
  cc->EvalMultKeyGen(keys.secretKey);

  vector<double> x1(batchSize);
  vector<double> x2(batchSize);
  
  x1[0] = B;
  x2[0] = -B*B;

  std::cout << "B: " << B << std::endl;

  Plaintext ptxt1 = cc->MakeCKKSPackedPlaintext(x1);
  Plaintext ptxt2 = cc->MakeCKKSPackedPlaintext(x2);

  auto c1 = cc->Encrypt(keys.publicKey, ptxt1);
  auto c2 = cc->Encrypt(keys.publicKey, ptxt2);

  auto cMul = cc->EvalMult(c1, c1);  // cMul = B^2
  auto cAdd = cc->EvalAdd(cMul, c2); // cAdd = B^2 - B^2 = 0

  Plaintext result;
  std::cout.precision(8);

  cc->Decrypt(keys.secretKey, cAdd, &result);
  result->SetLength(batchSize);
  std::cout << "C(x,y) = x^2-y on (B, -B^2) " << result;
  std::cout << result->GetLogPrecision()
            << std::endl;

}

int main() {
  run_game(0.0);
  run_game(100);

  return 0;
};
