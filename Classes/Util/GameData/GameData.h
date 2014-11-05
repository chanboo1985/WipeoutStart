#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__
class GameData
{
public:
	static GameData* getInstance();
	/*当前等级*/
	void setCurLevel(int curlv);
	
	inline int getCurLevel(){return cur_levle;}
	/*下一等级*/
	inline int getNextLevel(){return next_level;}
	/*最高分*/
	inline void setHistoryScore(int score){history_score = score;}

	inline int getHistoryScore(){return history_score;}
	/*当前分数*/
	inline void setCurScore(int score){cur_score = score;}

	inline int getCurScore(){return cur_score;}
	/*通关分数*/
	inline int getNextScore(){return next_score;}

	inline int getScoreByLevel(int lv);

	/*奖励分数*/
	int getAwardScore(int size);
	/*保存最高历史分数*/
	void saveHistoryScore();
private:
	GameData();

	void init();
private:
	static GameData* _instance;

	int cur_levle;

	int next_level;

	int history_score;

	int cur_score;

	int next_score;

	friend class MenuLayer;
};

#endif