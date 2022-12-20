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
        }   // ������ vector ����

        for (int i = 0; i < col; i++) {
            data_columns.push_back(data_table.front());
            data_table.erase(data_table.begin());
        }   // �÷��̸� �и�

        cout << --row << " rows X " << col << " columns" << endl;
        // ������ ���� ��� ���

        this->col = col;
        this->row = row;
        // �÷���, Ʃ�ü� ����
    }

    void print_col() {
        for (int i = 0; i < col; i++) {
            cout << data_columns[i] << " | ";
        }
        cout << endl;
    }   // �÷� ��� �޼ҵ�

public:
    ERROR_CODE open_csv(const char* str, static std::ios_base::openmode _Mode) {
        __super::open(str, _Mode);
        if (__super::fail()) {
            cout << "�߸��� ���� ����Դϴ�." << endl;
            return ERROR;
        }   // csv���� �ҷ����� Error Path
        else {
            cout << "������ ���������� �ҷ��Խ��ϴ�!" << endl;
            load_csv();
            return PASS;
        }
    }   // csv ���� ���� �޼ҵ�

    void print_csv() {
        cout << endl;
        print_col();
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cout << data_table[i*col+j] << " | ";
            }
            cout << endl;
        }
    }   // ������ csv ���� ���� ���
};

int main(int argc, char** argv) {

    
    myFstream fs;

    if (fs.open_csv("Economy_Indicators.csv", ios::in) == ERROR) return 0;

    fs.print_csv();
    
    fs.close();

    return 0;
}