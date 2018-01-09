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
    void Filterbase::update() {
        for(RdPass* pass : mRenderQueue) {
            if(pass == nullptr) {
                continue;
            }
            pass->update();
        }
    }
    void Filterbase::buildRenderList() {
        mFinalPass->buildRenderQueue(mRenderQueue);
    }
    void Filterbase::setFinalPass(RdPassRef finalPass) {
        mFinalPass = finalPass;
        buildRenderList();
    }
    Filterbase::Filterbase() {
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
        createGlslProg("filter/basic.vert", "filter/copy.frag");
    }
    void RdPass::update() {
        
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
    void RdPass::setBatch(gl::BatchRef batchRef) {
        mBatch = batchRef;
    }
    RdPass* RdPass::createGlslProg(const fs::path &vertPath, const fs::path &fragPath) {
        mProg = gl::GlslProg::create(gl::GlslProg::Format()
                                     .vertex(loadAsset(vertPath))
                                     .fragment(loadAsset(fragPath)));
        return this;
    }
    RdPass* RdPass::setInputTexture(int slot, gl::TextureRef tex) {
//        if(mInputTexture[slot] )
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
            mFboTarget->bindFramebuffer();
        }
        
        if(mBatch) {
            mBatch->draw();
        } else {
            if(mFboTarget) {
                gl::drawSolidRect(mFboTarget->getBounds());
            } else {
                gl::drawSolidRect(mInputTexture[0]->getBounds());
            }
        }
        
        if(mFboTarget != nullptr) {
            mFboTarget->unbindFramebuffer();
        }
        for(map<int, gl::TextureRef>::iterator it = mInputTexture.begin();
            it != mInputTexture.end(); ++it) {
            it->second->unbind();
        }
    }
    
}
