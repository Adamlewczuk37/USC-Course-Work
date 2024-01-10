#ifndef EVENT_H
#define EVENT_H
#include "wire.h"

struct Event
{
    uint64_t time;
    Wire* wire;
    char state;
};

typedef struct EventLess {
    bool operator()(const Event* x, const Event* y) const {
        return x->time < y->time;
    }
} EventLess;
	
#endif