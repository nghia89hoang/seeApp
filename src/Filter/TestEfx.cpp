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
        gl::Fbo::Format format;
        gl::FboRef fbo = gl::Fbo::create(mFbo->getWidth(), mFbo->getHeight(), format.depthTexture());
        
        grayPass = RdPass::create();
        grayPass->createGlslProg("shader/basic.vert", "shader/copy.frag");
        grayPass->setRenderBound(mFbo->getBounds());
        grayPass->setFbo(mFbo);
        
        sobelPass = RdPass::create();
        sobelPass->createGlslProg("shader/basic.vert", "shader/sobel.frag");
        sobelPass->setRenderBound(mFbo->getBounds());
        sobelPass->setFbo(nullptr);
        
        grayPass->chainNext(sobelPass);
        setFinalPass(sobelPass);
//        setFinalPass(grayPass);
    }
    void TestEfx::start() {
        grayPass->setInputTexture(mInputTexture, 0);
    }
    void TestEfx::update() {

    }
//    void TestEfx::draw() {
//        Efxbase::draw();
//    }
    TestEfx::~TestEfx(){
        
    }        
    void TestEfx::setTexSize(const vec2 &texSize){
        uTexSize = texSize;
        sobelPass->prog()->uniform("uTexSize", vec2(uTexSize.x, uTexSize.y));
    }
    
}
