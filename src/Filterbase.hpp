//
//  Filterbase.hpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/8/18.
//

#ifndef Filterbase_hpp
#define Filterbase_hpp

#include <stdio.h>
#include <list>
#include <map>
using namespace cinder;
using namespace ci;
using namespace std;

namespace see {
    class RdPass;
    class Filterbase;
    
    typedef std::shared_ptr<Filterbase> FilterbaseRef;
    typedef std::shared_ptr<RdPass> RdPassRef;
    
    class Filterbase {
    public:
        virtual ~Filterbase();
        static FilterbaseRef create() {
            FilterbaseRef ref = FilterbaseRef(new Filterbase());
            ref->setup();            
            return ref;
        }
        void setFinalPass(RdPassRef finalPass);
        
        virtual void setup();
        virtual void update();
        virtual void draw();
        void buildRenderList();
        
    protected:
        Filterbase();
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
        void setBatch(gl::BatchRef batchRef);
//        RdPass* createBatch(const gl::VboMeshRef &vboMesh, const fs::path &vertPath, const fs::path &fragPath, const gl::Batch::AttributeMapping &attributeMapping = gl::Batch::AttributeMapping());
//        RdPass* createBatch(const geom::Source &source, const fs::path &vertPath, const fs::path &fragPath, const gl::Batch::AttributeMapping &attributeMapping = gl::Batch::AttributeMapping());
        RdPass* createGlslProg(const fs::path &vertPath, const fs::path &fragPath);
        RdPass* setInputTexture(int slot, gl::TextureRef tex);
        RdPass* setFbo(gl::FboRef fbo);
        void chainNext(RdPassRef nextPass, int textureUnit = 0, GLenum attachment = GL_COLOR_ATTACHMENT0);
        void buildRenderQueue(list<RdPass*> &renderQueue);
    protected:
        // TODO: Handle VBO, Batching
        gl::BatchRef mBatch;
        RdPass();
        list<RdPass*> mPrevRdPass;
        gl::GlslProgRef mProg;
        map<int, gl::TextureRef> mInputTexture;
        gl::FboRef mFboTarget;
    };
}

#endif /* Filterbase_hpp */
