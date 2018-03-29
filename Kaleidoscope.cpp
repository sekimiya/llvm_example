
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <cctype>
#include <clocale>
#include <vector>

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

//すべての式ノードの基底クラス
class ExprAST{
    public:
        virtual ~ExprAST(){}
};

//数値参照のための式クラス
//コピーコンストラクタ
class NumberExprAST : public ExprAST{
    double Val;
    public:
        NumberExprAST(double val) : Val(Val){}
};

//変数参照のための式クラス
class VariableExprAST : public ExprAST{
    std::string Name;
public:
    VariableExprAST(const std::string &name) : Name(name) {}
};

//演算子参照のための式クラス
//opcodeをキャプチャ
class BinaryExorAST : public ExprAST{
    char Op;
    ExprAST *LHS, *RHS;
public:
    BinaryExorAST(char op, ExprAST *lhs, ExprAST *rhs) : Op(op), LHS(lhs), RHS(rhs){}
};

//関数呼び出しのための式クラス
class CallExprAST : public ExprAST {
    std::string Callee;
    std::vector<ExprAST*> Args;
public:
    CallExprAST(const std::string &callee, std::vector<ExprAST*> &args): Callee(callee), Args(args) {}
};

//引数名と引数をキャプチャする
class PrototypeAST{
    std::string Name;
    std::vector<std::string> Args;
public: 
    PrototypeAST(const std::string &name, const std::vector<std::string> &args): Name(name), Args(args) {}
};

class FunctionAST{
    PrototypeAST *Proto;
    ExprAST *Body;

public:
    FunctionAST(PrototypeAST *proto, ExprAST *body) : Proto(proto) , Body(body){}
};


/*
字句解析器（lexer）
コードを1文字ずつ取得、予約語、数値、コメント、演算子の順番で条件判定を行い、
各Tokenを構造体に返す。
テキスト（コード）をトークン毎にバラす。
*/
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
                    }while(isdigit(LastChar) || LastChar == '.' );
                    
                    NumVal = strtod(NumStr.c_str(), 0);
                    return tok_number;
                }
                //コメントを探す。発見した場合は行末までtokenを無視
                if (LastChar == '#'){
                    do LastChar = gettok();
                    while (LastChar != EOF && LastChar!='\n' && LastChar != '\r');
                    if (LastChar != EOF){
                        return gettok();
                    }
                }
                //ファイルの終了
                if (LastChar == EOF){
                    return tok_eof;
                }
                //それ以外の場合は演算子？
                int ThisChar = LastChar;
                LastChar = getchar();
                //ASCIIコードをそのまま返す
                return ThisChar;
            }
        }
    }
}



int main (){



}