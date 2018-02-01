//
//  StillImageView.cpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/31/18.
//

#include "StillImageView.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace cinder;

namespace see {
    StillImageView::StillImageView() {
        
    }
    StillImageView::~StillImageView() {
        
    }
    
    StillImageViewRef StillImageView::create() {
        StillImageViewRef ref = StillImageViewRef(new StillImageView());
        ref->setup();
        return ref;
    }
    
    void StillImageView::setup() {
        
    }
    void StillImageView::onViewInit() {
        ImageSourceRef imgSource = loadImage(loadAsset("img/cat_head.jpg"));
        mImage = gl::Texture::create(imgSource);
        mFbo = gl::Fbo::create(getWindowWidth(), getWindowHeight());
        mPass = RdPass::create();
        mPass->createGlslProg("shader/basic.vert", "shader/copy.frag");
        mPass->setInputTexture(mImage, 0);
        mPass->setFbo(nullptr);
        mPass->setRenderBound(getWindowBounds());
    }
    void StillImageView::onViewDeInit() {
        
    }
    void StillImageView::update() {
        if(!mIsInit) return;
        mPass->update();
    }
    void StillImageView::draw() {
        if(!mIsInit) return;
        gl::clearColor(ColorA(0.5, 0.5, 0.5, 0.5));
        gl::clear();
//        gl::draw(mImage, getWindowBounds());
        mPass->draw();
    }
}
