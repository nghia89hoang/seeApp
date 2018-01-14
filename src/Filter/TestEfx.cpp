//
//  GrayFilter.cpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/8/18.
//

#include "TestEfx.hpp"

using namespace std;
using namespace cinder;
namespace see {
    TestEfxRef TestEfx::create(gl::FboRef fbo) {
        TestEfxRef ref = TestEfxRef(new TestEfx());
        ref->setFbo(fbo);
        ref->setup();
        return ref;
    }
    TestEfx::TestEfx() {
        
    }
    void TestEfx::setup() {
        grayPass = RdPass::create();
        grayPass->createGlslProg("filter/basic.vert", "filter/colorgrad.frag");
        grayPass->setFbo(mFbo);
        
        sobelPass = RdPass::create();
        sobelPass->createGlslProg("filter/basic.vert", "filter/sobel.frag");
        
        grayPass->chainNext(sobelPass);
        setFinalPass(sobelPass);
    }
    void TestEfx::update() {
        grayPass->setInputTexture(mInputTexture, 0);
        
    }
    TestEfx::~TestEfx(){
        
    }        
    void TestEfx::setTexSize(const vec2 &texSize){
        uTexSize = texSize;
        sobelPass->prog()->uniform("uTexSize", vec2(uTexSize.x, uTexSize.y));
    }
    
}
