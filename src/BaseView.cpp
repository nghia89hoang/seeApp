//
//  BaseView.cpp
//  see
//
//  Created by Hoang Ngoc Nghia on 2/1/18.
//

#include "BaseView.h"

namespace see {
    BaseView::BaseView() {
        mIsActive = false;
        mIsInit = false;
    }
    BaseView::~BaseView() {
        
    }
    void BaseView::initialize() {
        if(mIsInit) return;
        mIsInit = true;
        onViewInit();
    }
    void BaseView::deInitialize() {
        mIsInit = false;
        onViewDeInit();
    }
    void BaseView::setup() {
        
    }
    void BaseView::update() {
        
    }
    void BaseView::draw() {
        
    }
}
