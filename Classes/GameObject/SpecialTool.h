#ifndef _SPECIAL_TOOL_H_
#define _SPECIAL_TOOL_H_

#include "cocos2d.h"

class SpecialTool:	public cocos2d::Sprite
{
public:
	SpecialTool(){}
	enum Type{
		Sun	=	0,
		Thead,
		Water
	};

	static SpecialTool* createTool(Type t);
	void initTool(Type t);

	cocos2d::Rect getEatBox();

	CREATE_FUNC(SpecialTool);
	Type getToolType(){ return toolType; }

private:
	Type toolType;
};

#endif