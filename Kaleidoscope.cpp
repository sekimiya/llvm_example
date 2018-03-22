
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <cctype>
#include <clocale>

using namespace std;

//既知のTokenならば対応する値を返す
//未知のTokenならば0以上255以下のトークンを返す
//字句解析器によって返される各トークンは、Token列挙型の値のどれか、もしくは”+”のような不明な文字の場合にはそのASCIIコード値を返す。
enum Token{
    tok_eof = -1,
    tok_def = -2,
    tok_extern = -3,
    tok_identifier = -4,
    tok_number = -5,
};

static std::string IdentifierStr;
static double NumVal;

static int gettok(){

    static int LastChar = ' ';

    //空白を無視して1文字づつ取得
    while(isspace(LastChar)){
        LastChar = getchar();
        //特定のキーワードをキャッチ
        if (isalpha(LastChar)){
            IdentifierStr = LastChar;
            //数値かチェック、数値に当たるまでを変数として格納？
            while(isdigit(LastChar = getchar())){
                IdentifierStr += LastChar;
                //予約語（language keyword）を探す。発見した場合はtokenにenumで定義した値を返す
                if (IdentifierStr == "def") {
                    return tok_def;
                }
                if (IdentifierStr == "exten"){
                    return tok_extern;
                }
                //数値を探す。発見した場合は、tokenにenumで定義した値を返す。
                if (isdigit(LastChar) || LastChar == '.'){
                    std::string NumStr;
                    //数値のvolを格納
                    do{
                        NumStr += LastChar; 
                        LastChar = getchar();
                    }
                    while(isdigit(LastChar) || LastChar == '.' );
                    NumVal = strtod(NumStr.c_str(), 0);
                    return tok_number;
                }
            }
        }
    }
}



int main (){



}