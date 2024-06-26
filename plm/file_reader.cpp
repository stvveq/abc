#include "file_reader.h"
#include "tele_cons.h"
#include "const.h"
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
using namespace std;


/*times convert_time(char* str)
{
    times result;
    char* context = NULL;
    char* str_number = strtok_s(str, ":", &context);
    result.hours = atoi(str_number);
    str_number = strtok_s(NULL, ":", &context);
    result.minutes = atoi(str_number);
    str_number = strtok_s(NULL, " ", &context);
    result.seconds = atoi(str_number);
    return result;
}
times convert_time(const string& str) {
    times result;
    stringstream ss(str);
    string part;

    getline(ss, part, ':'); // Get hours
    if (!ss.fail()) {
        result.hours = stoi(part);
    }
    else {
        result.hours = 0; // Or handle as an error
    }

    getline(ss, part, ':'); // Get minutes
    if (!ss.fail()) {
        result.minutes = stoi(part);
    }
    else {
        result.minutes = 0; // Or handle as an error
    }

    getline(ss, part, ':'); // Get seconds
    if (!ss.fail()) {
        result.seconds = stoi(part);
    }
    else {
        result.seconds = 0; // Or handle as an error
    }

    return result;
}*/
times convert_time(char* str) {
    times result;
    int len = strlen(str);
    int i = 0;
    int j = 0;

    // Extract hours
    while (str[i] != ':' && i < len) {
        i++;
    }
    result.hours = atoi(str);
    str += i + 1; // Move to the next part of the string

    // Extract minutes
    i = 0;
    while (str[i] != ':' && i < len) {
        i++;
    }
    result.minutes = atoi(str);
    str += i + 1;

    // Extract seconds
    result.seconds = atoi(str);

    return result;
}


void read(const char* file_name, marafon* runners, int& size)
{
     
    size = 0;
    ifstream file(file_name);
    if (file.is_open())
    {
        
        char tmp_buffer[MAX_STRING_SIZE];
       while (!file.eof())   //��������� ���������� ����� �� ��� ���, ���� �� ����� ��������� ����� 
       {
            file >> runners[size].number;             
            file >> runners[size].name;            
            file >> runners[size].club;          
            file >> tmp_buffer;
            runners[size].start_time = convert_time(tmp_buffer);            
            file >> tmp_buffer;
            runners[size].finish_time = convert_time(tmp_buffer);           
            size++;           
       }
        
        file.close();
    } //��������� ������ �� ����� ,�������� ���������  convert_date � ��������� ��������� �� ������ � ������

    else
    {
        throw "������ �������� �����";
    }
    
}

