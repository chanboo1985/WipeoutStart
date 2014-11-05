#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__
class GameData
{
public:
	static GameData* getInstance();
	/*��ǰ�ȼ�*/
	void setCurLevel(int curlv);
	
	inline int getCurLevel(){return cur_levle;}
	/*��һ�ȼ�*/
	inline int getNextLevel(){return next_level;}
	/*��߷�*/
	inline void setHistoryScore(int score){history_score = score;}

	inline int getHistoryScore(){return history_score;}
	/*��ǰ����*/
	inline void setCurScore(int score){cur_score = score;}

	inline int getCurScore(){return cur_score;}
	/*ͨ�ط���*/
	inline int getNextScore(){return next_score;}

	inline int getScoreByLevel(int lv);

	/*��������*/
	int getAwardScore(int size);
	/*���������ʷ����*/
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