#ifndef    _AES_H_
#define    _AES_H_
#include  "stdlib.h"
#include  "string.h"



//AES加密  16字节一个数据块
//IV_IN_OUT:        向量输入  密文输出
//State_IN_OUT：    明文输入  密文输出
//key128bit:        秘钥  128bit  16字节
void Aes_IV_key128bit_Encrypt(unsigned char *IV_IN_OUT, unsigned char *State_IN_OUT, unsigned char *key128bit);


//AES解密  16字节一个数据块
//IV_IN_OUT:        向量输入  原密文输出
//State_IN_OUT：    密文输入  明文输出
//key128bit:        秘钥  128bit  16字节
void Aes_IV_key128bit_Decode(unsigned char *IV_IN_OUT, unsigned char *State_IN_OUT, unsigned char *key128bit);

//AES加密  16字节一个数据块
//IV_IN_OUT:        向量输入  密文输出
//State_IN_OUT：    明文输入  密文输出
//key192bit:        秘钥  192bit  24字节
void Aes_IV_key192bit_Encrypt(unsigned char *IV_IN_OUT, unsigned char *State_IN_OUT, unsigned char *key192bit);

//AES解密  16字节一个数据块
//IV_IN_OUT:        向量输入  原密文输出
//State_IN_OUT：    密文输入  明文输出
//key192bit:        秘钥  192bit  24字节
void Aes_IV_key192bit_Decode(unsigned char *IV_IN_OUT, unsigned char *State_IN_OUT, unsigned char *key192bit);


//AES加密  16字节一个数据块
//IV_IN_OUT:        向量输入  密文输出
//State_IN_OUT：    明文输入  密文输出
//key256bit:        秘钥  256bit  32字节
void Aes_IV_key256bit_Encrypt(unsigned char *IV_IN_OUT, unsigned char *State_IN_OUT, unsigned char *key256bit);


//AES解密  16字节一个数据块
//IV_IN_OUT:        向量输入  原密文输出
//State_IN_OUT：    密文输入  明文输出
//key256bit:        秘钥  256bit  32字节
void Aes_IV_key256bit_Decode(unsigned char *IV_IN_OUT, unsigned char *State_IN_OUT, unsigned char *key256bit);



#endif



