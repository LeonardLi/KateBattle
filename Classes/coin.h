#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
enum class ScenarioEnum;
class Coin :public cocos2d::Node{
public:
	Coin();
	~Coin();
	static Coin* create(ScenarioEnum);
private:
	void __loadCSB();
	bool init(ScenarioEnum);
	void onCoinClicked(cocos2d::Ref*);
	void __createCoin();


	CC_SYNTHESIZE(int, m_coin, CoinNumber);
	cocostudio::Armature* m_armature;
	ScenarioEnum m_scenario;
    cocos2d::ui::Button* m_click;
};