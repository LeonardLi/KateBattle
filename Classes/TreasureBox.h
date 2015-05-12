#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
enum class ScenarioEnum;
class Equipment;

class TreasureBox :public cocos2d::Node{
public:
	TreasureBox();
	~TreasureBox();
	static TreasureBox* create(ScenarioEnum);


private:
	void __loadCSB();
	void __createEquipment(ScenarioEnum);
	void __writeInfo();
	virtual bool init(ScenarioEnum);
	
	void onBoxClicked(cocos2d::Ref*);

	cocostudio::Armature* m_armature;
	Equipment* m_equ;
    cocos2d::ui::Button* m_clickButton;
};