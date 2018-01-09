//
//  FaceScene.cpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/5/18.
//

#include "ViewController.hpp"
#include "cinder/app/App.h"
#include "poScene/TextView.h"

using namespace po::scene;
namespace see {
    
    ViewControllerRef ViewController::create(){
        return ViewControllerRef(new ViewController());
    }

    ViewController::ViewController() {
        
    }

    void ViewController::viewDidLoad() {
        mRoot = View::create();
//        mRoot->setPosition(ci::app::getWindowWidth()/2, ci::app::getWindowHeight()/2);
        getView()->addSubview(mRoot);
        
//        mTestView = TestView::create();
//        mRoot->addSubview(mTestView);
        Area a(ci::app::getWindowBounds());
        ivec2 s(ci::app::getWindowSize());
        float scale = ci::app::getWindowContentScale();
        ivec2 screenSize(float(s.x) * scale, float(s.y) * scale);
        mCaptureView = CaptureView::create(screenSize.x, screenSize.y);
        mRoot->addSubview(mCaptureView);
        
    }

}
