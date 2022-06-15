# Experiment Summary

Code for validation of the attack on the $\mathsf{IND}\text{-}\mathsf{CPA}^D$ security of Palisade's
implementation of CKKS.
The attack proceeds by homomorphically evaluating the circuit

$$C(x_1, x_2, x_3, x_4) = x_1 x_2 + x_3 x_4$$

on various inputs. These inputs are chosen such that

1. $C(x_1, x_2, x_3, x_4) = 0$ for any such inputs when computed exactly, and
2. the noise growth during homomorphic operations scales with the size of the
   inputs.

As PALISADE's countermeasure chooses noise to add based on an estimate of the
(input-dependent) noise within ciphertexts, we can break $\mathsf{IND}\text{-}\mathsf{CPA}^D$ security via
examining the size of noise the countermeasure adds.

# Building

PALISADE uses `cmake` as a build system.
To run our experiments, you must first have PALISADE installed.
See the [Palisade Wiki](https://gitlab.com/palisade/palisade-release/-/wikis/home) for installation instructions.

After installing PALISADE, one may run our experiments by executing the
following commands in order.

```
mkdir build
cd build
cmake ..
make
```

This should build a binary `experiments`, which can be exected with

```
./experiments
```

One can see directly that the decrypted output of $C(x_1,x_2,x_3,x_4)$ can vary by
several orders of magnitude, violating $\mathsf{IND}\text{-}\mathsf{CPA}^D$ security.
