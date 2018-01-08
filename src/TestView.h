//
//  TestScene.hpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/4/18.
//

#ifndef TestScene_hpp
#define TestScene_hpp

#include <stdio.h>
#include "cinder/gl/gl.h"
#include "poScene/View.h"

using namespace cinder;
using namespace po::scene;

namespace see {
    class TestView;
    typedef std::shared_ptr<class TestView>    TestViewRef;

    class TestView : public po::scene::View {
    public:
        static TestViewRef create();
        virtual ~TestView();
        virtual void init();
        virtual void setup() override;
        virtual void update() override;
        virtual void draw() override;
    protected:
        TestView();
    private:
        gl::GlslProgRef mShader;
        ci::CameraPersp mCam;
        gl::BatchRef mBalls;
    };
}
#endif /* TestScene_hpp */
