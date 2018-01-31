//
//  ParticleController.hpp
//  see
//
//  Created by Hoang Ngoc Nghia on 1/20/18.
//

#ifndef ParticleController_hpp
#define ParticleController_hpp
#include <cinder/Perlin.h>
#include <stdio.h>
#include <list>
#include "Particle.h"

using namespace std;
namespace see {
    class ParticleController {
    public:
        ParticleController();
        virtual ~ParticleController() {}
        void update(vec2 target);
        void draw();
        void addParticles(int amt);
        void addParticles(int amt, vec2 loc, vec2 initVel, float size=0.f);
        void removeParticles(int amt);
        ParticleRef addParticlePatternNorm(int xi, int yi, float size=5.0f);
        ParticleRef addParticlePatternCircle(int xi, int yi, float size=5.0f);
        ParticleRef addParticlePatternWierd1(int xi, int yi, float size=5.0f);
        ParticleRef addParticlePatternSpiral(int xi, int yi, float size=5.0f);
        
        std::list<ParticleRef> mParticles;
        
        void setSizeRange(vec2 srange) {
            mSizeRange = srange;
        }
        void setSizeRange(float min, float max) {
            mSizeRange = vec2(min, max);
        }
        void setbackgroundChannel(Channel32fRef c) {
            mBackgroundChannel = c;
        }
    protected:
        Perlin perlin;
        vec2 mSizeRange;
        Channel32fRef mBackgroundChannel;
    };

}

#endif /* ParticleController_hpp */
