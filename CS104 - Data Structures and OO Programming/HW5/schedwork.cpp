#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, int row, int col, std::map<int, int>& map);
bool check(const size_t maxShifts, const int& workers, std::map<int, int>& map);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();

    unsigned int numDays = avail.size();
    std::vector<unsigned int> newvec(dailyNeed, INVALID_ID);
    int row = 0;
    int col = 0;


    std::map<int, int> wToS;
    for (unsigned int i = 0; i < avail[0].size(); i++){
        wToS.insert(std::make_pair(i, 0));
    }
    
    
    for (unsigned int i = 0; i < numDays; i++){
        sched.push_back(newvec);
    }

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, row, col, wToS);
}


bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, int row, int col, std::map<int, int>& map){
		int days = sched.size();
		
		if (row >= days){
			return true;
    } else if (col >= (int)dailyNeed){
        col = 0;
        row++;
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, row, col, map);
    }

		if (sched[row][col] != INVALID_ID){
			col++;
			return scheduleHelper(avail, dailyNeed, maxShifts, sched, row, col, map);
		} else {
			unsigned int workers = avail[0].size();
			int temp = 0;
			for (unsigned int i = 0; i < workers; i++){
				sched[row][col] = i;
				if ((avail[row][i] != 0) && (check(maxShifts, i, map))){
					std::map<int, int>::iterator it = map.find(i);
					temp = it->second + 1;
					it->second = temp;

					col++;
					if (scheduleHelper(avail, dailyNeed, maxShifts, sched, row, col, map)) {
						return true;
					}
				}
				sched[row][col] = INVALID_ID;
			}
		}

    return false;
}


bool check(const size_t maxShifts, const int& workers, std::map<int, int>& map){
    std::map<int, int>::iterator it = map.find(workers);
		unsigned int temp = it->second + 1;

    return temp <= maxShifts;
}