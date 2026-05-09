
/*
Syntactical validity:

data.csv LINE: DATE COMMA PRICE
input.txt LINE: DATE SPACE '|' SPACE PRICE
DATE: YEAR '-' MONTH '-' DAY
YEAR: [2009,2022]
MONTH: [1,12]
DAY: if MONTH in {1,3,5,7,8,10,12}: 32
     if MONTH in {2}: if YEAR % 400 == 0 or (YEAR % 100 != 0 and YEAR % 4 == 0) : 29 else: 28
     if MONTH in {4,6,9,11}: 30
PRICE: [0,1000]
*/

#include "BitcoinExchange.hpp"

