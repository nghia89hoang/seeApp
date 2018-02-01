//
//  ExpView.cpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/20/18.
//

#include "ExpView.h"
#include <cinder/Rand.h>
#include <cinder/Perlin.h>

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace cinder;

namespace see {
    ExpView::ExpView() {
        
    }
    ExpView::~ExpView() {
        
    }
    ExpViewRef ExpView::create() {
        ExpViewRef ref = ExpViewRef(new ExpView());
        ref->setup();
        return ref;
    }
    void ExpView::setup() {
        
    }
    void ExpView::onViewInit() {
        ImageSourceRef imgSource = loadImage(loadAsset("img/cat_head.jpg"));
//        mImg = gl::Texture::create(imgSource);
        mChannel = Channel32f::create(imgSource);
        mParticleCtl.setSizeRange(10, 10);
        mParticleCtl.setbackgroundChannel(mChannel);
        
        mIsMousePressed = false;
        getSignal(po::scene::TouchEvent::MOVED).connect(std::bind(&ExpView::onTouchEvent, this, std::placeholders::_1));
        getSignal(po::scene::TouchEvent::BEGAN).connect(std::bind(&ExpView::onTouchEvent, this, std::placeholders::_1));
        getSignal(po::scene::TouchEvent::ENDED).connect(std::bind(&ExpView::onTouchEvent, this, std::placeholders::_1));
        getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&ExpView::onMouseEvent, this, std::placeholders::_1));
        getSignal(po::scene::MouseEvent::DOWN).connect(std::bind(&ExpView::onMouseEvent, this, std::placeholders::_1));
        getSignal(po::scene::MouseEvent::DRAG).connect(std::bind(&ExpView::onMouseEvent, this, std::placeholders::_1));
        getSignal(po::scene::MouseEvent::UP_INSIDE).connect(std::bind(&ExpView::onMouseEvent, this, std::placeholders::_1));
        getSignal(po::scene::MouseEvent::UP).connect(std::bind(&ExpView::onMouseEvent, this, std::placeholders::_1));
        getSignal(po::scene::MouseEvent::MOVE_INSIDE).connect(std::bind(&ExpView::onMouseEvent, this, std::placeholders::_1));
        getSignal(po::scene::MouseEvent::MOVE).connect(std::bind(&ExpView::onMouseEvent, this, std::placeholders::_1));
    }
    void ExpView::onViewDeInit() {
        
    }
    void ExpView::update() {
        if(!mIsInit) return;
        mParticleCtl.update(mMousePos);
    }
    void ExpView::draw() {
        if(!mIsInit) return;
        gl::clear(Color(0.2,0.2,0.2), true);
        {
            mParticleCtl.draw();
        }
    }
    void ExpView::onTouchEvent(po::scene::TouchEvent &event) {
        switch (event.getType()) {
            case po::scene::TouchEvent::BEGAN:
                mIsMousePressed = true;
                mMousePos = event.getLocalPos();
                break;
            case po::scene::TouchEvent::MOVED:
//                if(mIsMousePressed)
                {
                    vec2 curMousePos = event.getLocalPos();
                    vec2 deltaMousePos = (curMousePos - mMousePos);
                    mParticleCtl.addParticles(3, mMousePos, deltaMousePos, 5);
                    mMousePos = curMousePos;
                }
                break;
            case po::scene::TouchEvent::ENDED:
                mIsMousePressed = false;
                break;
            default:
                break;
        }
    }
    void ExpView::onMouseEvent(po::scene::MouseEvent &event) {
        switch(event.getType()) {
            case po::scene::MouseEvent::DOWN:
            case po::scene::MouseEvent::DOWN_INSIDE:
                mIsMousePressed = true;
                mMousePos = event.getLocalPos();
                break;
            case po::scene::MouseEvent::MOVE:
            case po::scene::MouseEvent::MOVE_INSIDE:
                break;
            case po::scene::MouseEvent::DRAG:
//                if(mIsMousePressed)
                {
                    vec2 curMousePos = event.getLocalPos();
                    vec2 deltaMousePos = (curMousePos - mMousePos);
                    mParticleCtl.addParticles(3, mMousePos, deltaMousePos, 5);
                    mMousePos = curMousePos;
                }
                break;
            case po::scene::MouseEvent::UP_INSIDE:
            case po::scene::MouseEvent::UP:
                mIsMousePressed = false;
                break;
            default:
                break;
        }
    }
    
    void ExpView::addParticleGrid(int cellSize) {
//        int cellSize = 10;
        int gridWidth = toPixels(getWindowWidth()) / cellSize;
        int gridHeight = toPixels(getWindowHeight()) / cellSize;
        for(int y=0;y<gridHeight;++y) {
            for(int x=0;x<gridWidth;++x) {
                //                ParticleRef p = mParticleCtl.addParticlePatternNorm(x,y,cellSize);
                //                ParticleRef p = mParticleCtl.addParticlePatternCircle(x,y,cellSize);
                //                ParticleRef p = mParticleCtl.addParticlePatternWierd1(x,y,cellSize);
                //                ParticleRef p = mParticleCtl.addParticlePatternSpiral(x,y,cellSize);
                //                p->mVelocity = 0.0f;
            }
        }
    }
}
