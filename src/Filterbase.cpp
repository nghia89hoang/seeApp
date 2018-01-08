//
//  Filterbase.cpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/8/18.
//

#include "Filterbase.hpp"
#include <map>
//#include "cinder/app/App.h"
using namespace ci;
using namespace cinder;
using namespace cinder::app;
using namespace std;
namespace see {
    
    void Filterbase::setup() {
        
    }
    void Filterbase::draw() {
        for(RdPass* pass : mRenderQueue) {
            if(pass == nullptr) {
                continue;
            }
            pass->draw();
        }
    }
    void Filterbase::buildRenderList(RdPassRef finalPass) {
        finalPass->buildRenderQueue(mRenderQueue);
    }
    
    Filterbase::~Filterbase() {
        mRenderQueue.clear();
    }
    //
    // Render pass
    //
    RdPass::RdPass() {
    }
    RdPass::~RdPass() {
        mInputTexture.clear();
        mPrevRdPass.clear();
    }
    RdPassRef RdPass::create() {
        RdPassRef ref = RdPassRef(new RdPass());
        ref->setup();
        return ref;
    }
    void RdPass::setup() {        
    }
    RdPass* RdPass::createGlslProg(const fs::path &vertPath, const fs::path &fragPath) {
        mProg = gl::GlslProg::create(gl::GlslProg::Format()
                                     .vertex(loadAsset(vertPath))
                                     .fragment(loadAsset(fragPath)));
        return this;
    }
    RdPass* RdPass::setInputTexture(int slot, gl::TextureRef tex) {
        if(mInputTexture[slot] )
        mInputTexture[slot] = tex;
        return this;
    }
    RdPass* RdPass::setFbo(gl::FboRef fbo) {
        mFboTarget = fbo;
        return this;
    }
    void RdPass::chainNext(RdPassRef next, int textureUnit, GLenum attachment) {
        next->mPrevRdPass.push_back(this);
        if(attachment == GL_COLOR_ATTACHMENT0) {
            next->setInputTexture(textureUnit, mFboTarget->getColorTexture());
        } else {
            next->setInputTexture(textureUnit, mFboTarget->getDepthTexture());
        }
    }
    void RdPass::buildRenderQueue(list<RdPass*> &renderQueue) {
        renderQueue.push_front(this);
        for(RdPass* r : mPrevRdPass) {
            r->buildRenderQueue(renderQueue);
        }
    }
    void RdPass::draw() {
        for(map<int, gl::TextureRef>::iterator it = mInputTexture.begin();
            it != mInputTexture.end(); ++it) {
            it->second->bind(it->first);
        }
        gl::ScopedGlslProg grayProg(mProg);
        if(mFboTarget != nullptr) {
            gl::ScopedFramebuffer scopedFbo(mFboTarget);
            gl::draw(mFboTarget->getColorTexture());
            
        } else {
//            gl::drawSolidRect(r);
        }
        geom::Rect r;
        for(map<int, gl::TextureRef>::iterator it = mInputTexture.begin();
            it != mInputTexture.end(); ++it) {
            it->second->unbind();
        }
    }
    
}
