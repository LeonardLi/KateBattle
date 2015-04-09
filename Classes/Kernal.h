//
//  Kernal.h
//  KateBattle
//
//  Created by Leonard on 15/3/19.
//
//

#ifndef __KateBattle__Kernal__
#define __KateBattle__Kernal__

#include <stdio.h>

class Kernal {
    
public:

	static Kernal* create();
	
	void startGame();

	bool playCG();
    

    
private:
	Kernal();
	~Kernal();
	
	bool _initFromFile();
};

class GameController{
    
};

#endif /* defined(__KateBattle__Kernal__) */
