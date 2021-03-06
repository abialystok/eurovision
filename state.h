#ifndef STATE_H_
#define STATE_H_

#include "mapForEurovision.h" 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/**
* state struct
*
* Implements a state struct type for a eurovision contest.
*
* The following functions are available:
*   stateCreate			- Creates a new empty state
*   stateDestroy		- Deletes an existing state and frees all resources
*	getStateId			- returns the states ID as an int
*	getStateName		- returns the states name as a char*
*	getSongName			- returns the states song name as a char*
*	getTotalScore		- returns the total score that a state got at the end 
*						  of the contest
*						  as a double
*	setTotalScore		- allows the user to insert to the state struct its 
*						  current total score
*	setFriendlied		- allows the user to flag the states as a part of a
*						  frienly states pair
*	isFriendlied		- returns the status of the friendlied flag as bool
*	stateCopy			- copies an existing state struct
*	addVoteFromState	- add 1 to the taker states vote counter of the giver
*						  state 
*	removeVoteFromState - removes 1 from the taker states vote counter of the 
*						  giver state
*	sumResultsFromState	- sums up the entire raw votes the the state gave into
*						  a reachble 10 size array 
*						  of final results given from this state
*	getAllResultsFromState 
*						- returns the final results given from said state size 
*						  10 int array
*	getResultFromStateToState
*						- returns the final result given from the giver state
*						  to the taker
*	getVoteFromStateToState
*						- returns the raw votes given from the giver state to 
*						  the taker
*	removeAllVotesFromStateToState
*						- removes all raw votes given from the giver state to 
*						  the taker
	
*/
typedef struct State_t* State;

typedef enum stateResult_t {
	STATE_NULL_ARGUMENT,
	STATE_OUT_OF_MEMORY,
	STATE_INVALID_NAME,
	STATE_NOT_EXIST,
	STATE_SUCCESS
} StateResult;

//==========================test function==================
void checkSumResultsAux(State state);

Map getVotesFromState(State state);
//======================end of test function================

/**
Creates a new state element
@param stateId - unique state ID for the new state
@param judgeName - string representing the states name (not unique)
@param songName - string representing the states song name (not unique)
@return
	NULL - if malloc failed
	else returns the new state
*/
State stateCreate(int stateId, const char* stateName, const char* songName);

/**
Destroys given state.
@param state - state to destroy
@return
	STATE_NOT_EXIST - if given state is NULL
	STATE_SUCCESS - elsewise
*/
StateResult stateDestroy(State state);

/**
Returns state ID
@param state - state element whose ID you want
@return -
	-1 -  if NULL was given as state
	stateId of state otherwise
*/
int getStateId(State state);

/**
Returns state name
@param state - state element whose name you want
@return -
	NULL if NULL was given as judge
	stateName of state otherwise
*/
const char* getStateName(State state);


/**
Returns states song name
@param state - state element whose song name you want
@return -
	NULL if NULL was given as state
	songName of state otherwise
*/
const char* getSongName(State state);

/**
returns the total score a state got
@param state - state you want to check
@return - 
	-1 if state is NULL.
	otherwise returns the value.
*/
double getTotalScore(State state);

/**
sets the total score given to a state
@param state - state to set score to
@param totalScore - score to give
@return - 
	STATE_NULL_ARGUMENT if state is null
	STATE_SUCCESS otherwise
*/
StateResult setTotalScore(State state, double totalScore);

/*
sets boolean value for field "friendlied", that describes if a state was 
already counted as another state's friend.
@param state - the state to set value to.
@param value - true/false if the state was/wasn't counted.
@return - 
	STATE_NULL_ARGUMENT if state is NULL
	MAP_SUCCESS otherwise.
*/
StateResult setFriendlied(State state, bool value);

/*
returns boolean value for field "friendlied", that describes if a state was
already counted as another state's friend.
@param state - the state to check.
@return -
	false if state is NULL
	apropriate value otherwise.
*/
bool isFriendlied(State state);

/**
copies a given state to an entirely differen state element
@param state - state to copy
@return -
	NULL if NULL was given as state or if a memory error occured
	the new State element otherwise
*/
State stateCopy(State state);

/**
adds 1 to the vote count for stateTaker in the map of votes of stateGiver
@param stateGiver - state element from whom you want to give a vote
@param stateTakerId - id of the state to whom you want to give a vote
*/
StateResult addVoteFromState(State stateGiver, int stateTakerId);


/**
deducts 1 from the vote count for stateTaker in the map of votes of stateGiver
@param stateGiver - state element from whom you want to deduct a vote
@param stateTakerId - id of the state to whom you want to deduct a vote
*/
StateResult removeVoteFromState(State stateGiver, int stateTakerId);

/**
sums all the raw votes of state into an arrrey of the first 10 hightest scored
states this array can be found in getAllResultsFromState.
@param state - state element for whom you want to sum votes into results
*/
void sumResultsFromState(State state);

/**
Returns state results array
@param state - state element whose results you want
@return -
	NULL if NULL was given as state
	stateResults of state otherwise
*/
int* getAllResultsFromState(State state);

/**
returns the spesific final result given from stateGiver to StateTaker
@param stateGiver - state element from whom the result was given
@param stateTakerId - id of the state to whom the result was given
@return -
	0 - if no result was given
	1-7,8,10,12 - the result given 
*/
int getResultFromStateToState(State stateGiver, int stateTakerId);

/**
returns the number of raw votes given from stateGiver to StateTaker
@param stateGiver - state element from whom the result was given
@param stateTakerId - id of the state to whom the result was given
@return -
	NO_VOTES - defined as 0, will be returned if no vote was given to 
			   stateTaker
	returns the number of votes otherwise
*/
int getVoteFromStateToState(State stateGiver, int stateTakerId);

/**
removes all votes from stateGiver to stateTakerId
@param stateGiver - state element  whose votes you want to remove 
@param stateTakerId - id of the state to whom you want to remove votes
@return -
	STATE_NULL_ARGUMENT - will be returned if NULL was given as stateGiver or 
						  stateTaker
	STATE_NOT_EXIST - will be returned if no votes were given in the first 
					  place
	returns STATE_SUCCESS otherwise
*/
StateResult removeAllVotesFromStateToState(State stateGiver, int stateTakerId);


#endif /* STATE_H_ */