#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool isValid(DailySchedule& currentSched, const size_t maxShifts, int row, int col, vector<int>& workersShifts);
bool buildScheduleByRow(std::vector<int> todaysWorkers, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, int rowNumber, int colNumber);


// Add your implementation of schedule() and other helper functions here
bool buildScheduleByRow(std::vector<int> todaysWorkers, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, int rowNumber, int colNumber) {
	if (colNumber == dailyNeed) {
		std::vector<int> workersShifts(sched[0].size());
		if (isValid(sched, maxShifts, 0, 0, workersShifts, rowNumber)) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		for (int i = 0; i < todaysWorkers.size(); i++) {
			sched[rowNumber][colNumber] = todaysWorkers[i];
			std::vector<int> workersShifts(sched[0].size());
			if (isValid(sched, maxShifts, 0, 0, workersShifts, rowNumber)) {
				if (colNumber + 1 <= dailyNeed) {
					buildScheduleByRow(todaysWorkers, dailyNeed, maxShifts, sched, rowNumber, colNumber + 1);
				}
			}
			else {
				sched[rowNumber][colNumber] = INVALID_ID;
			}
		}
	}
}

//recursively checks if currentSched is a valid schedule
bool isValid(DailySchedule& currentSched, const size_t maxShifts, int row, int col, vector<int>& workersShifts, int maxRow) {
	if (row > maxRow) {
		return true;
	}
	int workerID = currentSched[row][col];
	workersShifts[workerID]++;
	if (workersShifts[workerID] > maxShifts) {
		return false;
	}
	else {
		if (col + 1 < currentSched[0].size()) {
			return isValid(currentSched, maxShifts, row, col + 1, workersShifts);
		}
		else {
			if (row + 1 < currentSched.size()) {
				return isValid(currentSched, maxShifts, row + 1, 0, workersShifts);
			}
			return true;
		}
	}
}

bool schedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched) {
    if(avail.size() == 0){
        return false;
    }
    sched.clear();
    // Add your code below

	int kValue = avail[0].size();
	int nValue = avail.size();
	sched.resize(nValue);
	for (int i = 0; i < nValue; i++) {
		std::vector<int> todaysWorkers;
		sched[i].resize(dailyNeed, 0);
		for (int j = 0; j < kValue; j++) {
			todaysWorkers.push_back(avail[i][j]);
		}
		buildScheduleByRow(todaysWorkers, dailyNeed, maxShifts, sched, i, 0);
	}
}

