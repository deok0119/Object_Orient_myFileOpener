#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

enum ERROR_CODE
{
    ERROR,
    PASS
};

class myFstream : public fstream {
private:
    int col, row;
    vector<string> data_columns;
    vector<string> data_table;

    void load_csv() {
        string str_buf, char_buf;
        istringstream ss;
        int col, row;
        row = 0;
        col = 0;
        cout << endl;
        while (!__super::eof()) {
            cout << "{" << row << "} ";
            std::getline(*this, str_buf, '\n');
            ss.str(str_buf);
            while (!ss.eof()) {
                std::getline(ss, char_buf, ',');
                data_table.push_back(char_buf);
                cout << char_buf + " | ";
                if (row == 0) col++;
            }
            cout << endl;
            row++;
            ss.clear();
        }   // 데이터 vector 저장

        for (int i = 0; i < col; i++) {
            data_columns.push_back(data_table.front());
            data_table.erase(data_table.begin());
        }   // 컬럼이름 분리

        cout << --row << " rows X " << col << " columns" << endl;
        // 데이터 저장 결과 출력

        this->col = col;
        this->row = row;
        // 컬럼수, 튜플수 저장
    }

    void print_col() {
        for (int i = 0; i < col; i++) {
            cout << data_columns[i] << " | ";
        }
        cout << endl;
    }   // 컬럼 출력 메소드

public:
    ERROR_CODE open_csv(const char* str, static std::ios_base::openmode _Mode) {
        __super::open(str, _Mode);
        if (__super::fail()) {
            cout << "잘못된 파일 경로입니다." << endl;
            return ERROR;
        }   // csv파일 불러오기 Error Path
        else {
            cout << "파일을 성공적으로 불러왔습니다!" << endl;
            load_csv();
            return PASS;
        }
    }   // csv 파일 열기 메소드

    void print_csv() {
        cout << endl;
        print_col();
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cout << data_table[i*col+j] << " | ";
            }
            cout << endl;
        }
    }   // 저장한 csv 파일 내용 출력
};

int main(int argc, char** argv) {

    
    myFstream fs;

    if (fs.open_csv("Economy_Indicators.csv", ios::in) == ERROR) return 0;

    fs.print_csv();
    
    fs.close();

    return 0;
}