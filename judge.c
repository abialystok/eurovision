#include "judge.h"

struct Judge_t {
	int judgeId;
	const char* judgeName;
	int* judgeResults;
};

Judge judgeCreate(int judgeId, const char* judgeName, int* judgeResults) {
	Judge judge = malloc(sizeof(*judge));
	if (judge == NULL) {
		return NULL;
	}
	judge->judgeId = judgeId;
	judge->judgeName = judgeName;
	judge->judgeResults = judgeResults;
	return judge;
}

void judgeDestroy(Judge judge) {
	if (judge == NULL) return;
	if (judge->judgeResults != NULL) free(judge->judgeResults);
	free(judge);
}

int getJudgeId(Judge judge) {
	if (judge == NULL) return 0;
	return judge->judgeId;
}

const char* getJudgeName(Judge judge) {
	if (judge == NULL) return NULL;
	return judge->judgeName;
}

int* getJudgeResults(Judge judge) {
	if (judge == NULL) return NULL;
	return judge->judgeResults;
}
/*copies the result array of a judge from one array to another*/
static JudgeResult copyJudgeResults(int* destination, int* source) {
	if (source == NULL || destination == NULL) return JUDGE_NULL_ARGUMENT;
	for (int i = 0; i < STATES_TO_SCORE; i++) {
		destination[i] = source[i];
	}
	return JUDGE_SUCCESS;
}

Judge judgeCopy(Judge judge) {
	if (judge == NULL) return NULL;
	int newId = getJudgeId(judge);
	const char* newName = getJudgeName(judge);
	int* newResults = malloc(sizeof(int)*STATES_TO_SCORE);
	if (copyJudgeResults(newResults, getJudgeResults(judge)) != JUDGE_SUCCESS)
		return NULL;
	Judge newJudge = judgeCreate(newId, newName, newResults);
	return newJudge;
}

int getResultFromJudge(Judge judge, int stateId) {
	if (judge == NULL) return -1;
	int* results = judge->judgeResults;
	bool in_array = false;
	int index = 0;
	for (index = 0; index < STATES_TO_SCORE; index++) {
		if (results[index] == stateId) {
			in_array = true;
			break;
		}
	}
	if (!in_array) {
		return 0;
	} else {
		switch (index)
		{
		case 0: return 12;
		case 1:	return 10;
		case 2: return 8;
		case 3: return 7;
		case 4: return 6;
		case 5: return 5;
		case 6: return 4;
		case 7: return 3;
		case 8: return 2;
		case 9: return 1;
		default: break;
		}
	}
	return 0;
}