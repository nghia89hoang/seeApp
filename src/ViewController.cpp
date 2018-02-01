//
//  FaceScene.cpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/5/18.
//

#include "ViewController.hpp"
#include "cinder/app/App.h"
#include "poScene/TextView.h"
#include "StillImageView.h"
#include "TestView.h"
#include "CaptureView.h"
#include "ExpView.h"

using namespace po::scene;
using namespace cinder;
namespace see {
    
    ViewControllerRef ViewController::create(){
        return ViewControllerRef(new ViewController());
    }

    ViewController::ViewController() {
        mCurView = 0;
        ivec2 size(ci::app::getWindowSize());
        float scale = ci::app::getWindowContentScale();
        sScreenSize = ivec2(float(size.x) * scale, float(size.y) * scale);
        //
        StillImageViewRef stillImageView = StillImageView::create();
        mListView.push_back(stillImageView);
        //
        ExpViewRef expView = ExpView::create();
        mListView.push_back(expView);        
        //
#if !defined(CINDER_COCOA_TOUCH)
        CaptureViewRef capView = CaptureView::create(1280, 720);
        mListView.push_back(capView);
#endif
        //
        TestViewRef testView = TestView::create();
        mListView.push_back(testView);
        
        
    }

    void ViewController::viewDidLoad() {
        mRoot = View::create();
        getView()->addSubview(mRoot);
        mRoot->addSubview(mListView[mCurView]);
    }
    
    void ViewController::changeView(bool isNext) {
        po::scene::ViewRef v = mListView[mCurView];
        v->removeFromSuperview();
        if(isNext) {
            if(++mCurView >= mListView.size()) {
                mCurView = 0;
            }
        } else {
            if(--mCurView < 0) {
                mCurView = mListView.size() - 1;
            }
        }
        mListView[mCurView]->setup();
        mRoot->addSubview(mListView[mCurView]);
    }
    void ViewController::keyDown(cinder::app::KeyEvent event) {
        
    }
}
