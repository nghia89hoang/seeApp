//
//  Efxbase.cpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/8/18.
//

#include "Efxbase.hpp"
#include "cinder/gl/gl.h"
#include <map>
//#include "cinder/app/App.h"

using namespace ci;
using namespace cinder;
using namespace cinder::app;
using namespace std;
namespace see {
    
    void Efxbase::setup() {
    }
    
    void Efxbase::start() {
        
    }
    
    void Efxbase::draw() {
        for(RdPass* pass : mRenderQueue) {
            if(pass == nullptr) {
                continue;
            }
            pass->draw();
        }
    }
    void Efxbase::update() {
        for(RdPass* pass : mRenderQueue) {
            if(pass == nullptr) {
                continue;
            }
            pass->update();
        }
    }
    void Efxbase::buildRenderList() {
        mFinalPass->buildRenderQueue(mRenderQueue);
    }
    void Efxbase::setFinalPass(RdPassRef finalPass) {
        mFinalPass = finalPass;
        buildRenderList();
    }
    void Efxbase::setFbo(gl::FboRef fbo) {
        mFbo = fbo;
    }
    void Efxbase::setInputTexture(gl::TextureRef inputTexture) {
        mInputTexture = inputTexture;
    }
//    void Efxbase::blitScreen() {
//        gl::drawSolidRect(getWindowBounds());
//    }
    Efxbase::Efxbase() {
    }
    Efxbase::~Efxbase() {
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
//        createGlslProg("shader/basic.vert", "shader/copy.frag");
    }
    void RdPass::update() {
        
    }

    void RdPass::applyToBatch(gl::BatchRef batchRef) {
        mBatch = batchRef;
    }
    RdPass* RdPass::createGlslProg(const fs::path &vertPath, const fs::path &fragPath) {
        mProg = gl::GlslProg::create(gl::GlslProg::Format()
                                     .vertex(loadAsset(vertPath))
                                     .fragment(loadAsset(fragPath)));
        return this;
    }
    RdPass* RdPass::setInputTexture(gl::TextureRef tex, int slot) {
        CI_ASSERT(slot >= 0);
        mInputTexture[slot] = tex;
        return this;
    }
    RdPass* RdPass::setFbo(gl::FboRef fbo) {
        mFboTarget = fbo;
        return this;
    }
    
    void RdPass::chainNext(RdPassRef next, int textureUnit, GLenum attachment) {
        next->mPrevRdPass.push_back(this);
        if(!mFboTarget) {
            gl::Fbo::Format format;
            mFboTarget = gl::Fbo::create(1024, 1024, format.depthTexture());
        }
        if(attachment == GL_COLOR_ATTACHMENT0) {
            next->setInputTexture(mFboTarget->getColorTexture(), textureUnit);
        } else {
            next->setInputTexture(mFboTarget->getDepthTexture(), textureUnit);
        }
    }
    void RdPass::buildRenderQueue(list<RdPass*> &renderQueue) {
        renderQueue.push_front(this);
        for(RdPass* r : mPrevRdPass) {
            r->buildRenderQueue(renderQueue);
        }
    }
    void RdPass::setRenderBound(Rectf rect) {
        mRenderBound = rect;
    }
    
    void RdPass::draw() {
        for(map<int, gl::TextureRef>::iterator it = mInputTexture.begin();
            it != mInputTexture.end(); ++it) {
            it->second->bind(it->first);
        }
        gl::ScopedGlslProg grayProg(mProg);
        if(mBatch) {
            gl::ScopedFramebuffer s(mFboTarget);
            mBatch->draw();
        } else {
            console() << "Window Bound: " << getWindowBounds() << "\n";
            console() << "Window Bound(pxl): " << toPixels(getWindowBounds()) << "\n";
            console() << "Window Size: " << getWindowBounds() << "\n";
            Rectf flippedBounds( 0, 0, getWindowHeight(), getWindowWidth() );
            Rectf doubleBound( 0, 0, getWindowWidth() * 2.0f, getWindowHeight() * 2.0f );
            ivec2 flippedSize(getWindowHeight(), getWindowWidth());
            if(mFboTarget) {
                console() << "Fbo Size: " << mFboTarget->getSize() << "\n";
                Rectf flippedFbo( 0, 0, mFboTarget->getHeight(), mFboTarget->getWidth() );
                gl::ScopedFramebuffer s(mFboTarget);
                gl::ScopedViewport vp(ivec2(0), mFboTarget->getSize());
                gl::setMatricesWindow( (mFboTarget->getSize()), false );
                gl::drawSolidRect(mFboTarget->getBounds());
            } else {
#if defined CINDER_COCOA_TOUCH
                gl::rotate( M_PI / 2 );
                gl::scale(mRenderBound.getHeight() / toPixels(getWindowWidth()), mRenderBound.getHeight() / toPixels(getWindowWidth()));
                gl::translate( 0, -toPixels(getWindowHeight()) );
#else
                gl::scale(mRenderBound.getWidth() / toPixels(getWindowWidth()), mRenderBound.getHeight() / toPixels(getWindowHeight()));
#endif
                gl::ScopedViewport vp(vec2(0,0), toPixels(getWindowSize()));
                gl::drawSolidRect(toPixels(getWindowBounds()), vec2(1,0), vec2(0,1));
            }
        }
        for(map<int, gl::TextureRef>::iterator it = mInputTexture.begin();
            it != mInputTexture.end(); ++it) {
            it->second->unbind();
        }
    }
    
}
//    RdPass* RdPass::createBatch(const gl::VboMeshRef &vboMesh, const fs::path &vertPath, const fs::path &fragPath, const gl::Batch::AttributeMapping &attributeMapping) {
//        createGlslProg(vertPath, fragPath);
//        mBatch = gl::Batch::create(vboMesh, mProg, attributeMapping);
//        return this;
//    }
//    RdPass* RdPass::createBatch(const geom::Source &source, const fs::path &vertPath, const fs::path &fragPath, const gl::Batch::AttributeMapping &attributeMapping) {
//        createGlslProg(vertPath, fragPath);
//        mBatch = gl::Batch::create(source, mProg, attributeMapping);
//        return this;
//    }
