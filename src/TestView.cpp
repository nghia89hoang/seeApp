//
//  TestScene.cpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/4/18.
//

#include "TestView.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace cinder;

namespace see {
    TestView::TestView() {
        
    }
    TestView::~TestView() {
        
    }
    TestViewRef TestView::create() {
        TestViewRef ref = TestViewRef(new TestView());
        ref->init();
        return ref;
    }
    void TestView::init() {
        mCam.lookAt(vec3(5,2,5), vec3(0,1,0));
        gl::setMatrices(mCam);
        auto lambert = gl::ShaderDef().lambert().color();
        mShader = gl::getStockShader(lambert);
        mBalls = gl::Batch::create(geom::Sphere(), mShader);
    }
    
    void TestView::setup() {
        
    }
    void TestView::update() {
        
    }
    void TestView::draw() {
        gl::setMatrices(mCam);
        
        gl::enableDepthRead();
        gl::enableDepthWrite();
        gl::clear();
        
        int numSphere = 64;
        float maxAngle = M_PI * 7;
        float spiralRadius = 1;
        float height = 3;
        float anim = getElapsedFrames() / 30.0f;
        float ballSize = 0.05f;
        for(int i = 0; i < numSphere; ++i) {
            float rel = i / (float) numSphere;
            float angle = rel * maxAngle;
            float y = fabs(cos(rel * M_PI + anim)) * height;
            float r = rel * spiralRadius;
            vec3 offset(r * cos(angle), y, r * sin(angle));
            
            gl::pushModelView();
            gl::translate(offset);
            gl::scale( vec3( ballSize, 1, ballSize ) );
            gl::color( Color(CM_HSV, rel, 1, 1) );
            mBalls->draw();
            gl::popModelView();
        }
    }
}
