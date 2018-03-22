
#include <ctype.h>
#include <stdio.h>
#include <iostream.h>

//既知のTokenならば対応する値を返す
//未知のTokenならば0以上255以下のトークンを返す
//字句解析器によって返される各トークンは、Token列挙型の値のどれか、もしくは”+”のような不明な文字の場合にはそのASCIIコード値を返す。
enum Token{
    tok_eof = -1,
    tok_def = -2,
    tok_extern = -3,
    tok_identifier = -4,
    rok_number = -5,
};

static std::string identifierStr;
static double NumVal;

static int gettok(){

    static int LastChar = '';

    //空白を無視して1文字づつ取得
    while(isspace(LastChar)){
        LastChar = getchar();
        if (isalpha(LastChar)){


        }
    }
}

int main (){



}