//
//  GrayFilter.hpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/8/18.
//

#ifndef GrayFilter_hpp
#define GrayFilter_hpp

#include <stdio.h>
#include "Efxbase.hpp"

using namespace std;
using namespace cinder;
namespace see {
    class TestEfx;
    typedef shared_ptr<TestEfx> TestEfxRef;
    
    class TestEfx : public Efxbase {
    public:
        static TestEfxRef create(gl::FboRef fbo = nullptr);
        ~TestEfx();
        virtual void start();
        virtual void setup();
        virtual void update();
//        virtual void draw();
        void setTexSize(const vec2 &textSize);
    protected:
        TestEfx();
        vec2 uTexSize;
        RdPassRef grayPass;
        RdPassRef sobelPass;
    };
}

#endif /* GrayFilter_hpp */
