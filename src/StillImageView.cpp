//
//  StillImageView.cpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/31/18.
//

#include "StillImageView.h"
//#include <cinder/Rand.h>
//#include <cinder/Perlin.h>

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
        ImageSourceRef imgSource = loadImage(loadAsset("img/cat_head.jpg"));
        mImage = gl::Texture::create(imgSource);
    }
    void StillImageView::update() {
        
    }
    void StillImageView::draw() {
        gl::clearColor(ColorA(0, 0, 0, 0));
        gl::clear();
        gl::draw(mImage, getWindowBounds());
    }
}
