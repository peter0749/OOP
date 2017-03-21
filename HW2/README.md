---
Date: 2017-03-14 21:05
ID number: 404410030
Name: 鄭光宇
Environment: Mac OSX 10.12.3
Email: jengku@gmail.com
Bonus: Programming Style, Iterator, Inheritance, IO exception handling, Selftest
Simple Guide: just make
---
#### 環境
OS:

Mac OSX 10.12.3

Compiler:
```
g++ GCC 6.3
```

#### 說明

呼叫帕斯卡三角形的 Function 不會重複計算，
因為除了預先處理的階層不用另外計算外，
函式會檢查是否已經算過（存在記憶體中）。

#### 編譯

`make all`
> 注意：本次作業有使用到 C++11 standard。編譯時有加上選項 -std=c++11

#### 執行

`make run`

#### 測試

測試程式是否會 Crash
預設產生測資大小：200000

`make judge`
