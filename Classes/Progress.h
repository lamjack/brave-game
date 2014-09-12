//
//  Progress.h
//  Brave
//
//  Created by jack on 9/12/14.
//
//

#ifndef __Brave__Progress__
#define __Brave__Progress__

#include "cocos2d.h"

USING_NS_CC;

class Progress : public Sprite{
public:
    bool init(const char* background, const char* fillname);
    
    static Progress* create(const char* background, const char* fill);
    
    void setFill(ProgressTimer* fill){ _fill = fill; }
    
    void setProgress(float percentage){ _fill->setPercentage(percentage); }
    
private:
    ProgressTimer* _fill;
};

#endif /* defined(__Brave__Progress__) */
