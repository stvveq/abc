#pragma once
#pragma once
#include "const.h"
#ifndef PHONE_CALL_H
#define PHONE_CALL_H

struct times
{
    int hours;
    int minutes;
    int seconds;
};
struct marafon
{
    char number[MAX_STRING_SIZE];
    char name[NAME_SIZE];
    char club[CLUB_SIZE];
    times start_time;
    times finish_time;


};

#endif

