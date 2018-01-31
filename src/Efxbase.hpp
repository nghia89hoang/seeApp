//
//  Efxbase.hpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/8/18.
//

#ifndef Efxbase_hpp
#define Efxbase_hpp

#include <stdio.h>
#include <list>
#include <map>
using namespace cinder;
using namespace ci;
using namespace std;

namespace see {
    class RdPass;
    class Efxbase;
    
    typedef std::shared_ptr<Efxbase> EfxbaseRef;
    typedef std::shared_ptr<RdPass> RdPassRef;
    
    class Efxbase {
    public:
        virtual ~Efxbase();
        static EfxbaseRef create(gl::FboRef fbo = nullptr) {
            EfxbaseRef ref = EfxbaseRef(new Efxbase());
            ref->setFbo(fbo);
            ref->setup();            
            return ref;
        }
        void updateInputTexture(gl::TextureRef inputTexture);
        void setFinalPass(RdPassRef finalPass);
        void setFbo(gl::FboRef fbo);
        virtual void setup();
        virtual void update();
        virtual void draw();
        void buildRenderList();
        
    protected:
        Efxbase();
        // TODO: make a list
        gl::TextureRef mInputTexture;
        gl::FboRef mFbo;
        RdPassRef mFinalPass;
        list<RdPass*> mRenderQueue;
    };
    
    class RdPass {
    public:
        virtual ~RdPass();
        static RdPassRef create();
        gl::GlslProgRef prog(){
            return mProg;
        }
        gl::FboRef fbo(){
            return mFboTarget;
        }
        
        virtual void setup();
        virtual void draw();
        virtual void update();
        bool isHeadPass() {
            return (mPrevRdPass.size() == 0);
        }
        void applyToBatch(gl::BatchRef batchRef);
//        RdPass* createBatch(const gl::VboMeshRef &vboMesh, const fs::path &vertPath, const fs::path &fragPath, const gl::Batch::AttributeMapping &attributeMapping = gl::Batch::AttributeMapping());
//        RdPass* createBatch(const geom::Source &source, const fs::path &vertPath, const fs::path &fragPath, const gl::Batch::AttributeMapping &attributeMapping = gl::Batch::AttributeMapping());
        RdPass* createGlslProg(const fs::path &vertPath, const fs::path &fragPath);
        RdPass* setInputTexture(gl::TextureRef tex, int slot = 0);
        RdPass* setFbo(gl::FboRef fbo);
        void chainNext(RdPassRef nextPass, int textureUnit = 0, GLenum attachment = GL_COLOR_ATTACHMENT0);
        void buildRenderQueue(list<RdPass*> &renderQueue);
        void setRenderBound(Rectf rect);
    protected:
        //!!!!: TODO: Handle VBO, Batching
        gl::BatchRef mBatch;
        Rectf mRenderBound;
        RdPass();
        list<RdPass*> mPrevRdPass;
        gl::GlslProgRef mProg;
        map<int, gl::TextureRef> mInputTexture;
        gl::FboRef mFboTarget;
    };
}

#endif /* Efxbase_hpp */
