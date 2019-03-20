# BRC simple cipher

<a href="https://github.com/AnyKeyShik/SimpleKernel/blob/master/LICENSE">
<img src ="https://img.shields.io/github/license/AnyKeyShik/BRC.svg" />
</a>
<a href="https://github.com/AnyKeyShik/SimpleKernel/stargazers">
<img src ="https://img.shields.io/github/stars/AnyKeyShik/BRC.svg" />
</a>
<a href="https://github.com/AnyKeyShik/SimpleKernel/network">
<img src ="https://img.shields.io/github/forks/AnyKeyShik/BRC.svg" />
</a>


This is a proof-of-concept of BRC (Bum's Replace Cipher) simple substitution cipher.

# Getting started

#### Requirements

To compile and run this project, you will need:
* the NASM assembler
* the GNU linker
* GRUB bootloader
* a Linux x64 operating system

#### Running the code

Simply use the following commands in a terminal:
```
git clone https://github.com/AnyKeyShik/BRC.git
cd BRC
mkdir build
cd build
cmake ..
make
```

# The main idea
The main idea of this cipher is replace the original letter to random symbols separated by some delimiter. Delimiter is calculated based on numebr of letters in non-encrypted text. It's only a raw idea and maybe we improve this cipher in the future

## Authors
[4n9k3y5h1k](https://github.com/AnyKeyShik)\
[f1u77y](https://github.com/f1u77y)
