## Terms

- **[Cryptanalysis?](Cryptanalysis)** Breaking ciphers. 
- **Confusion:** Each bit of ciphertext should depend on several parts of the key. 
  - Advantages: Cipher text cannot be found inside the key and increases confusion for Man in Middle.
- [Connected Security](Connected_Security)
- **Difussion:** Used to hide relationship between the ciphertext and the plain text.
  - If we change 1 bit of plaintext, then 1/2 of bits of cipher text should change.
  - Also, If we change 1 bit of ciphertext, then 1/2 of bits of plain text should change.
- **Decryption?** All steps are run in reverse order of encryption.
- **Kerckhoff’s principle?** Whole world should know how crypto algorithm works, All algorithms must be public. Algorithm is parameterized by key only the keys are secret
- **Rounds?** There are more P-boxes at start and end.
- **Whitening?** XORing a random 64-bit key with plaintext before feeding it into Encryptor and then XORing a second 64-bit key with the resulting ciphertext before transmitting it. DES uses it.
