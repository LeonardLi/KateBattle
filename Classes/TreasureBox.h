#include "cocos2d.h"
#include "ui/CocosGUI.h"
enum class ScenarioEnum;
class Equipment;

class TreasureBox :public cocos2d::ui::Button{
public:
	TreasureBox();
	~TreasureBox();
	static TreasureBox* create(ScenarioEnum);


private:
	void __loadCSB();
	void __createEquipment(ScenarioEnum);
	virtual bool init(ScenarioEnum);
	
	Equipment* m_equ;
};